#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define MIN_DELT 0.00001              ///< ��������, ������� ���������� ����������� �������� ������ �� �������� �����
#define NUM_AF_POINT 4                ///< ���������� ���� ����� ������� ��� ������
#define NUM_OF_COEF 3                 ///< ���������� ������������

//�������������� �������� reshalka
#define NUM_OF_COEF_RESHALKA 3        ///< ���������� ������������ � reshalka
#define NUM_OF_UNITEST_RESHALKA 6     ///< ���������� ��������� reshalka
#define NUM_OUT_OF_UNITEST_RESHALKA 3 ///< ���������� ������� ������� reshalka

//�������������� �������� qadrat
#define NUM_OF_COEF_QADRAT 3        ///< ���������� ������������ � qadrat
#define NUM_OF_UNITEST_QADRAT 3     ///< ���������� ��������� qadrat
#define NUM_OUT_OF_UNITEST_QADRAT 3 ///< ���������� ������� ������� qadrat

//�������������� �������� linerial
#define NUM_OF_COEF_LINERIAL 2        ///< ���������� ������������ � linerial
#define NUM_OF_UNITEST_LINERIAL 3     ///< ���������� ��������� linerial
#define NUM_OUT_OF_UNITEST_LINERIAL 2 ///< ���������� ������� ������� linerial

const char* NAME_VAR[NUM_OF_COEF] = {"a","b","c"};///< ������ ��� ����������
const char END_SIMVOL = '#'; ///< ������ ��� ����� �������� ����������� ���������

/// �������� ������ ������� reshalka, qadrat
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

//=====================================================================================
/// ���� ��� �������� reshalka
const double UNITEST_IN_RESHALKA[NUM_OF_UNITEST_RESHALKA][NUM_OF_COEF_RESHALKA] =
    {
    {0, 0, 0},     // ������� �� ���������� ������ ������������� ������
    {0, 0, 1},     // �������� �� ���������� ������
    {0, 1, 1},     // �������� �� ������� �������� ���������
    {1, -2, 1},    // �������� �� ���������� ��������� � 1 ������
    {1, -1, -2},   // �������� �� ���������� ��������� � 2 �������
    {1, 1, 1},     // �������� �� ���������� ������
    };

/// ��������� ����� ��� �������� reshalka
const double UNITEST_OUT_RESHALKA[NUM_OF_UNITEST_RESHALKA][NUM_OUT_OF_UNITEST_RESHALKA] =
    {
    {0, 0, ROOTS_INF},
    {0, 0, ROOTS_0},
    {-1, 0, ROOTS_1},
    {1, 0, ROOTS_1},
    {2, -1, ROOTS_2},
    {0, 0, ROOTS_0},
    };

//=====================================================================================
/// ���� ��� �������� qadrat
const double UNITEST_IN_QADRAT[NUM_OF_UNITEST_QADRAT][NUM_OF_COEF_QADRAT] =
    {
    {1, -2, 1},    // �������� �� ���������� ��������� � 1 ������
    {1, -1, -2},   // �������� �� ���������� ��������� � 2 �������
    {1, 1, 1},     // �������� �� ���������� ������
    };

/// ��������� ����� ��� �������� qadrat
const double UNITEST_OUT_QADRAT[NUM_OF_UNITEST_QADRAT][NUM_OUT_OF_UNITEST_QADRAT] =
    {
    {1, 0, ROOTS_1},
    {2, -1, ROOTS_2},
    {0, 0, ROOTS_0},
    };

//=====================================================================================
/// ���� ��� �������� linerial
const double UNITEST_IN_LINERIAL[NUM_OF_UNITEST_LINERIAL][NUM_OF_COEF_LINERIAL] =
    {
    {0, 0},     // ������� �� ���������� ������ ������������� ������
    {0, 1},     // �������� �� ���������� ������
    {1, 1},     // �������� �� ������� �������� ���������
    };

/// ��������� ����� ��� �������� linerial
const double UNITEST_OUT_LINERIAL[NUM_OF_UNITEST_LINERIAL][NUM_OUT_OF_UNITEST_LINERIAL] =
    {
    {0, ROOTS_INF},
    {0, ROOTS_0},
    {-1, ROOTS_1},
    };

//=====================================================================================

/*!
�������� ������������ ������� reshalka
\return ������� � ������������ Error_skan_var
*/
int unitest_reshalka(void);

/*!
�������� ������������ ������� qadrat
\return ������� � ������������ Error_skan_var
*/
int unitest_qadrat(void);

/*!
�������� ������������ ������� linerial
\return ������� � ������������ Error_skan_var
*/
int unitest_linerial(void);

/*!
�������� ��� ������������ � ��������� � ���������
\return ������� � ������������ Error_skan_var
*/
int unitest(void);

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
