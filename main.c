#include "Pre_main.h"
//#include "Qadratik_const_fails.h"
//#include "Qadratik_funk.c"
//#include "Unitest.c"

int main(void)
{

    setlocale(LC_CTYPE,"Russian"); //Для вывода руских букв

    double a=0, b=0, c=0;    // Определение переменных для коэфициентов уравнения
    double x_1=0, x_2=0;     // Определение переменных для коней
    int reshalka_error = OK; // Определение переменной для количества корней
    int sc_chek = OK;        // Проверка ввода значений

    if (unitest() == END_PROGRAM)
    {
        return 202;
    }

    start_print();

    while(1) // Ввод коэфициентов
    {

        sc_chek = abc_scan(&a, &b, &c);

        if (sc_chek == END_PROGRAM)
        {
            break;
        }

        x_1 = 0;
        x_2 = 0;

        if ( abc_lim_over_print (a, b, c) )         // Проверка коэфициентов
        {
        continue;
        }
        else
        {

            reshalka_error = reshalka (a, b, c, &x_1, &x_2);

            if (reshalka_error == -2)     // Решение уравнения
            {
            continue;
            }
            else
            {
                x_lim_over_print(x_1, x_2, reshalka_error);           // Вывод корней
            }
        }
    }

    end_print();

    return 0;
}

