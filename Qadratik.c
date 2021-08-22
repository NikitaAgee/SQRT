#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#define  NUM_AF_POINT 4 ///<����� ����� ������� ��� ������

/// �������� ������ ������� reshalka, qadrat �������
enum Error_reshalka
{
    ROOTS_2 = 2,         ///< ��������� ����� 2 �����
    ROOTS_1 = 1,         ///< ��������� ����� 1 ������
    ROOTS_0 = 0,         ///< � ��������� ��� ������
    ROOTS_INF = -1,      ///< ��������� ����� ������������� �������
    OVERCHARGE_DIS = -2, ///< ������: ������������ ��� ������� ��������� ������������
    ERROR = -3           ///< ������: �������������� ��������� ( �� ������ ����������, �� ���� ��� ����������� �������� ���������, ������� ����� ������� ������� ����� ������� ���������)
};

/// �������� ������ ������� abc_scan skan_variable
enum Error_skan_var
{
    OK = 0,              ///< � ������ �� ������
    END_PROGRAM = 1,     ///< ����� ��������� ���������
    NEED_TAKE_STOK = 2   ///< ����� ���������� ������������ ���������
};

/*!
��������� ���� ������������ � ��������� �� �������� + ����������� ���������� ���������
\param *a,*b,*c double ��������� �� ���������� ��� �������� ������������
\return � ������������ Error_skan_var
*/
int abc_scan(double* a, double* b, double* c);

/*!
��������� ���� ���������� �������� � ��������� ���� �� ������.
��� �� ��� �������������� ���������� ��������� � ����������� �� �����.
\param var_name ������� � ��������� ����������
\param *var ��������� �� ���������� ��� ������ �����
\return � ������������ Error_skan_var
*/
int skan_variable(char var_name[], double* var);

/*!
����� ������������ ������ � ���������� ���������, ����������� ����� � ������� ��������������� ��������
\return � ������������ Error_skan_var
*/
int end_question(void);

/*!
��������� �������� �� ������������ � ������� ����������� ��������� (��� ����� �������� � ����������� �� �������� ����������), ���� ��� ���������
\param nom ����� �� ��������
\param befor_variable ��������� ����� ������� �������� ����������
\param name_variable  �������� ����������
\param after_variable ��������� ����� ������ �������� ����������
\param *overcharge ��������� �� ���������� ��� ������ �������� (true - ���� ����� ����������� folse - �� ������������ ��� ��������� ����������� ������� �������������� ����� ��� ���������� � ������ �����)
*/
void overcharge_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overcharge);

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
\param a,b,c ����������� ���������
\param x_1,x_2 ����� ���������
\return ������������� Error_reshalka
*/
int qadrat ( double a, double b, double c, double* x_1, double* x_2);

/*!
������ �������� ���������
\param b,c ����������� ���������
\param *x ��������� �� ���������� ��� ������ �����
\return ������������� Error_reshalka
*/
int linerial (double b, double c, double *x);

/*!
������ ����������/�������� ���������, ���������� ������������� ������
\param a,b,c ����������� ���������
\param *x_1, *x_2 ��������b �� ���������� ��� ������ ������
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


int main(void)
{

    setlocale(LC_CTYPE,"Russian"); //��� ������ ������ ����

    double a, b, c;     // ����������� ���������� ��� ������������ ���������
    double x_1, x_2;    // ����������� ���������� ��� �����
    int reshalka_error; // ����������� ���������� ��� ���������� ������

    start_print();

    while( abc_scan(&a, &b, &c) == 0)                // ���� ������������
    {
        if ( abc_lim_over_print (a, b, c ) )         // �������� ������������
        {
        continue;
        }
        else
        {

            reshalka_error = reshalka (a, b, c, &x_1, &x_2);

            if (reshalka_error == -2)     // ������� ���������
            {
            continue;
            }
            else
            {
                x_lim_over_print(x_1, x_2, reshalka_error);           // ����� ������
            }
        }
    }

    end_print();

}

bool abc_lim_over_print(double a, double b, double c)
{

    // ����������� ��������� � ������������ ����� ������� �������� ����������, ������� �����������
    char befor_variable[50] = "������� ������� (�� ������) ����������: ";

    bool overcharge = false; // ����������� ����� �������

    // �������� ������������� ��������
    overcharge_alarm (a,  befor_variable, "a", "", &overcharge);
    overcharge_alarm (b,  befor_variable, "b", "", &overcharge);
    overcharge_alarm (c,  befor_variable, "c", "", &overcharge);

    return overcharge;
}

void x_lim_over_print(double x_1, double x_2, int root_count)
{

    char befor_variable[50] = "������� ������� (�� ������) ������: ";
    bool overcharge = false;

    if (root_count == 2)
    {
        //�������� x_1 x_2
        overcharge_alarm (x_1,  befor_variable, "x_1", "", &overcharge);
        overcharge_alarm (x_2,  befor_variable, "x_2", "", &overcharge);
    }
    if(root_count == 1)
    {
        //�������� x
        overcharge_alarm (x_1,  befor_variable, "x", "", &overcharge);

    }

    if ( overcharge == false)
    {
        /*����� ������*/
        if (root_count == 2)
        {
            printf("����� ���������:\n");
            printf("X_1 = %.*f\n", NUM_AF_POINT, x_1);
            printf("X_2 = %.*f\n", NUM_AF_POINT, x_2);
        }
        if (root_count == 1)
        {
            printf("������ ���������:\n");
            printf("X = %.*f\n", NUM_AF_POINT, x_1);
        }
        if (root_count == 0)
        {
            printf("������ ���\n");
        }
        if (root_count == -1)
        {
            printf("������ �������������\n");
        }
        if (root_count == -3)
        {
            printf("���-�� ����� �� �� �����\n");
        }
    }
}

int qadrat(double a, double b, double c, double *x_1, double *x_2)
{
    double Dis;   /*������������ (�������� ��� double ����� �������)*/
    double skDis; /*������ �������������*/
    char befor_variable[50] = "������������ ������� ������� (�� ������)\n ";
    bool overcharge = false;

    /*���������� �������������*/
    Dis = ((b * b) - (4 * c * a));

    /*�������� ������������ Dis*/
    overcharge_alarm (Dis,  befor_variable, "Dis", "", &overcharge);
    if (overcharge)
    {
        return OVERCHARGE_DIS;
    }

    /* ������ ��������� ������������ � ����������� �� ��������������*/
    else if (Dis<0)
    {
        return ROOTS_0;
    }
    else
    {
        /*������ �������������*/
        skDis = sqrt(Dis);

        /*���������� x_1 � x_2*/
        *x_1 = ((-b + skDis) / (2 * a));
        *x_2 = ((-b - skDis) / (2 * a));

        /*������ *n, ���������������� ������������� */

        if (fabs (Dis) < 0.00001)
        {
            return ROOTS_1;
        }
        else
        {
            return ROOTS_2;
        }
    }

    return ERROR;
}

int linerial (double b, double c, double *x)
{
    *x=((-c) / b);
    return ROOTS_1;
}

int reshalka (double a, double b, double c, double* x_1, double* x_2)
{
    if((fabs (a) < 0.00001) && (fabs (c) < 0.00001))        //�������� �������������
    {
        return ROOTS_INF;
    }
    else if (fabs (a) < 0.00001)
    {
        return linerial (b, c, x_1);
    }
    else
    {
        return qadrat(a, b, c, x_1, x_2);
    }
}

int abc_scan(double *a, double *b, double *c)
{

    int take_stok = 0;
    int err_out = 0;

    printf("==========================================================================\n");

    printf("������� ������������ \n(��� ���������� ��������� ������� ����� ������� ������������ � �������): \n");

    //������ �������� ����� �����
    if (err_out != 1)
    {
        err_out = skan_variable("a", a);
    }

    if(err_out == 2)
    {
        take_stok = 1;
    }

    if (err_out != 1)
    {
        err_out = skan_variable("b", b);
    }

    if(err_out == 2)
    {
        take_stok = 1;
    }

    if (err_out != 1)
    {
        err_out = skan_variable("c", c);
    }

    if(err_out == 2)
    {
        take_stok = 1;
    }
    //����� �������� ����� �����

    //���������� �����, ���� ���� ���������� � ���������� (�������� �������� ������ ������� �.�. �������� ����������� � ����� �����)
    if ((take_stok == 1) && (err_out == 0))
    {

        printf("--------------------------------------------------------------------------\n");
        printf("a = %.*f\n", NUM_AF_POINT, *a);
        printf("b = %.*f\n", NUM_AF_POINT, *b);
        printf("c = %.*f\n", NUM_AF_POINT, *c);
    }

    printf("--------------------------------------------------------------------------\n");

    //����� �������� ������������� ��������� ��������� ��� ����������
    if (err_out == 1)
    {
        return END_PROGRAM;
    }
    return OK;

}

int skan_variable(char var_name[], double* var)
{

    int sk_chek = 0;  //�������� ������� � ����� �����
    int sk_error = 0; //�������� ����� �� ���������� ����
    char ch;          //����� ��� �������
    int out = OK;     //����� ���������

    while(1)
    {
        printf("%s = ", var_name);
        sk_chek = scanf("%lf", var);  //���� �����

        ch = getchar();       // �������� ����� �� ���������� ��������
        sk_error = 0;         // (������� �������� � �������� �����)
                              //
        while(ch != '\n')     //
        {                     //
            if (ch !='\n')    //
            {                 //
                sk_error = 1; //
            }                 //
            ch = getchar();   //
        }                     //

        if (sk_chek == 0)                // ������� �� �������� ����������� ������� ������
        {                                // (������ ������������)
            if(end_question())           //
            {                            //
            return END_PROGRAM;          //
            }                            //
            else                         //
            {                            //
                out = NEED_TAKE_STOK;    //
                                         //
                //������� ������ �����   //
                while (getchar()!='\n')  //
                {;}                      //
                                         //
                continue;                //
            }                            //
        }
        else if (sk_error == 1) //���������� � �������� ��� ����� �����
        {
            printf("��� ����� ������������ �� �������� (����� � ����� ������ ��� ������)\n��� ���������� ��������� ������� ����� ������ ������ � �������\n��������� ����:\n");
            out = NEED_TAKE_STOK;
        }
        else
        {
        break;
        }
    }

    return out;
}

int end_question(void)
{

    char pr_end_Y_N;

    while(1)
        {
            printf("�� ������������� ������ ��������� ��������� [Y/N]: "); //�������� �� ������ ������������


            pr_end_Y_N = getchar();                         //������ ������ �� ������� �������

            //�������� ������
            if ((pr_end_Y_N=='Y') || (pr_end_Y_N=='y'))
            {
                return END_PROGRAM;
                break;
            }
            else if((pr_end_Y_N=='N') || (pr_end_Y_N=='n'))
            {
                return OK;
                break;
            }
            else
            {
                printf("� �� �����, ���� ������\n");

                //������� ������ �����
                while (getchar()!='\n')
                {;}
            }
        }
}


void start_print()
{
    printf("==========================================================================\n");
    printf("                   ������� ��������� a*x^2+b*x+c=0                        \n");
}

void end_print()
{
    printf("==========================================================================\n");
    printf("��������� ���������\n");
    printf("��� �������� ���� ������� [Enter] \n");
    printf("==========================================================================\n");

    getchar();
    getchar();

}

void overcharge_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overcharge)
{
    if(isinf (nom))
    {
        printf("%s%s%s", befor_variable, name_variable, after_variable );
        *overcharge = true;
    }
}



