#include "Pre_Qadratik.h"
#include "Qadratik_funk.c"

int main(void)
{

    setlocale(LC_CTYPE,"Russian"); //��� ������ ������ ����

    double a=0, b=0, c=0;     // ����������� ���������� ��� ������������ ���������
    double x_1=0, x_2=0;    // ����������� ���������� ��� �����
    int reshalka_error = OK; // ����������� ���������� ��� ���������� ������
    int unitest = 1;

    unitest = unitest_reshalka();

    if (unitest == 1)
    {
        start_print();
    }

    while( (abc_scan(&a, &b, &c) == 0) && (unitest == 1)) // ���� ������������
    {

        x_1 = 0;
        x_2 = 0;

        if ( abc_lim_over_print (a, b, c) )         // �������� ������������
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




