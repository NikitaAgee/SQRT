#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#define MIN_DELT 0.00001     ///< ��������, ������� ���������� ����������� �������� ������ �� �������� �����
#define NUM_AF_POINT 4       ///< ���������� ���� ����� ������� ��� ������
#define NUM_OF_COEF 3        ///< ���������� ������������
#define NUM_OF_UNITEST 6     ///< ���������� ���������
#define NUM_OUT_OF_UNITEST 3 ///< ���������� ������� �������

const char* NAME_VAR[NUM_OF_COEF] = {"a","b","c"};///< ������ ��� ����������
const char END_SIMVOL = '#'; ///< ������ ��� ����� �������� ����������� ���������

/// �������� ������ ������� reshalka, qadrat �������
enum Error_reshalka
{
    ROOTS_2 = 2,         ///< ��������� ����� 2 �����
    ROOTS_1 = 1,         ///< ��������� ����� 1 ������
    ROOTS_0 = 0,         ///< � ��������� ��� ������
    ROOTS_INF = -1,      ///< ��������� ����� ������������� �������
    OVERFLOW_DIS = -2,   ///< ������: ������������ ��� ������� ��������� ������������
    ERROR = -3           ///< ������: �������������� ��������� ( �� ������ ����������, �� ���� ��� ����������� �������� ���������, ������� ����� ������� ������� ����� ������� ���������)
};

/// �������� ������ ������� abc_scan skan_variable
enum Error_skan_var
{
    OK = 0,              ///< � ������ �� ������
    END_PROGRAM = 1,     ///< ����� ��������� ���������
    NEED_TAKE_STOK = 2   ///< ����� ���������� ������������ ���������
};

const double UNITEST_IN[NUM_OF_UNITEST][NUM_OF_COEF] =
    {
    {0, 0, 0},     // ������� �� ���������� ������ ������������� ������
    {0, 0, 1},     // �������� �� ���������� ������
    {0, 1, 1},     // �������� �� ������� �������� ���������
    {1, -2, 1},    // �������� �� ���������� ��������� � 1 ������
    {1, -1, -2},   // �������� �� ���������� ��������� � 2 �������
    {1, 1, 1},     // �������� �� ���������� ������
    };

const double UNITEST_OUT[NUM_OF_UNITEST][NUM_OUT_OF_UNITEST] =
    {
    {0, 0, ROOTS_INF},
    {0, 0, ROOTS_0},
    {-1, 0, ROOTS_1},
    {1, 0, ROOTS_1},
    {2, -1, ROOTS_2},
    {0, 0, ROOTS_0},
    };


/*!
�������� ������������ ������� reshalka
\return ������� � ������������ Error_skan_var
*/
int unitest_reshalka(void);

/*!
��������� ���� ������������ � ��������� �� �������� + ����������� ���������� ���������
\param[out] *a,*b,*c double ��������� �� ���������� ��� �������� ������������
\return � ������������ Error_skan_var
*/
int abc_scan(double* a, double* b, double* c);

/*!
��������� ���� ���������� �������� � ��������� ���� �� ������.
��� �� ��� �������������� ���������� ��������� � ����������� �� �����.
\param[in] var_name ������� � ��������� ����������
\param[out] *var ��������� �� ���������� ��� ������ �����
\return � ������������ Error_skan_var
*/
int skan_variable(const char var_name[], double* var);

/*!
����� ������������ ������ � ���������� ���������, ����������� ����� � ������� ��������������� ��������
\return � ������������ Error_skan_var
*/
int end_question(void);

/*!
��������� �������� �� ������������ � ������� ����������� ��������� (��� ����� �������� � ����������� �� �������� ����������), ���� ��� ���������
\param[in] nom ����� �� ��������
\param[in] befor_variable ��������� ����� ������� �������� ����������
\param[in] name_variable  �������� ����������
\param[in] after_variable ��������� ����� ������ �������� ����������
\param[out] *overflow ��������� �� ���������� ��� ������ �������� (true - ���� ����� ����������� folse - �� ������������ ��� ��������� ����������� ������� �������������� ����� ��� ���������� � ������ �����)
*/
void overflow_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overflow);

/*!
��������� ����������� ��������� �� ������������ � ������� �������������� �����������
\param a,b,c ��������� ���������
\return ���������� true ���� ���� ������������ �������� folse ���� - ���
*/
bool abc_lim_over_print(double a, double b, double c);

/*!
��������� ����� ��������� �� ������������, ������� ���������� �� ���� ��� �������� ���� �����.
\param x_1,x_2 ����� ���������
\param root_count ���������� ������ (����������� �������� ������������� Error_reshalka)
*/
void x_lim_over_print(double x_1, double x_2, int root_count);

/*!
������ ���������� ���������
\param[in] a,b,c ����������� ���������
\param[out] x_1,x_2 ����� ���������
\return ������������� Error_reshalka
*/
int qadrat ( double a, double b, double c, double* x_1, double* x_2);

/*!
������ �������� ���������
\param[in] b,c ����������� ���������
\param[out] *x ��������� �� ���������� ��� ������ �����
\return ������������� Error_reshalka
*/
int linerial (double b, double c, double *x);

/*!
������ ����������/�������� ���������, ���������� ������������� ������
\param[in] a,b,c ����������� ���������
\param[out] *x_1, *x_2 ��������b �� ���������� ��� ������ ������
\return ������������� Error_reshalka
*/
int reshalka (double a, double b, double c, double* x_1, double* x_2);

/*!
�������� ����� ���������� ���������
*/
void start_print();

/*!
�������� �������� ���������� � ���������� ��������� � ����������� ��������
���� �� ������� [Enter]
*/
void end_print();
