#include "Pre_Qadratik.h"


bool abc_lim_over_print(double a, double b, double c)
{

    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));

    // Определение сообщения о переполнении перед выводом названия переменной, которая переполнена
    char* befor_variable = "Слишком большой (по модулю) коэфициент: ";

    bool overflow = false; // определение выход функции

    // Проверка переполненных значений
    overflow_alarm(a,  befor_variable, "a", "\n", &overflow);
    overflow_alarm(b,  befor_variable, "b", "\n", &overflow);
    overflow_alarm(c,  befor_variable, "c", "\n", &overflow);

    return overflow;
}

void x_lim_over_print(double x_1, double x_2, int root_count)
{

    assert(!isnan(x_1));
    assert(!isnan(x_2));

    char* befor_variable = "Слишком большой (по модулю) корень: ";
    bool overflow = false;

    //проверка x_1 x_2
    overflow_alarm(x_1,  befor_variable, "x_1", "\n", &overflow);
    overflow_alarm(x_2,  befor_variable, "x_2", "\n", &overflow);

    if (overflow)
    {
        return;
    }
    switch (root_count) //Вывод значения в зависимости от root_count
    {
        case ROOTS_2:
            printf("Корни уравнения:\n");
            printf("X_1 = %.*f\n", NUM_AF_POINT, x_1);
            printf("X_2 = %.*f\n", NUM_AF_POINT, x_2);
            break;

        case ROOTS_1:
            printf("Корень уравнения:\n");
            printf("X = %.*f\n", NUM_AF_POINT, x_1);
            break;

        case ROOTS_0:
            printf("Корней нет\n");
            break;

        case ROOTS_INF:
            printf("Корней бесконечность\n");
            break;

        case ERROR:
            printf("Что-то пошло не по плану (Код ошибки %d)\n", ERROR);
            break;

        default:
            printf("Что-то пошло очень не по плану (Не правильный root_count = %d) \n", root_count);
    }
}

int qadrat(double a, double b, double c, double *x_1, double *x_2)
{
    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(!(x_1 == 0));
    assert(!(x_2 == 0));
    assert(!(x_1 == x_2));

    double Dis = 0;   // Дискриминант
    double skDis = 0; // Корень дискриминанта
    char* befor_variable = "Дискриминант слишком большой (по модулю)\n ";
    bool overflow = false;

    // Вычисление дискриминанта
    Dis = ((b * b) - (4 * c * a));

    // Проверка переполнения Dis
    overflow_alarm(Dis,  befor_variable, "Dis", "\n", &overflow);
    if (overflow)
    {
        return OVERFLOW_DIS;
    }

    /* начало ветвления резуультатов в зависимости от дискрииминанта*/
    else if (Dis <= -MIN_DELT)
    {
        return ROOTS_0;
    }
    else if (fabs(Dis) < MIN_DELT)
    {
        // Корень дискриминанта
        skDis = sqrt(Dis);

        // Вычисление x_1 и x_2
        *x_1 = ((-b + skDis) / (2 * a));
        *x_2 = 0;

        // Вывод соответствующего значения
        return ROOTS_1;
    }
    else
    {
        // Корень дискриминанта
        skDis = sqrt(Dis);

        // Вычисление x_1 и x_2
        *x_1 = ((-b + skDis) / (2 * a));
        *x_2 = ((-b - skDis) / (2 * a));;

        // Вывод соответствующего значения
        return ROOTS_2;
    }

    return ERROR;
}

int linerial(double b, double c, double *x)
{

    assert(!isinf(b));
    assert(!isinf(c));
    assert(!(x == 0));

    if ((fabs(b) <= MIN_DELT) && (fabs(c) <= MIN_DELT))        //проверка условий бесконечного количества решений
    {
        return ROOTS_INF;
    }

    else if ((fabs(b) <= MIN_DELT) && (fabs(c) > MIN_DELT))   //проверка отсутствия корней из-за особенности переменных
    {
        return ROOTS_0;
    }
    else if (fabs(b) > MIN_DELT)                           //роверка на выполнимость/необходимость приминения линейности
    {
        *x = ((-c) / b);
        return ROOTS_1;
    }

    return ROOTS_1;
}

int reshalka(double a, double b, double c, double* x_1, double* x_2)
{

    assert(!isinf(a));
    assert(!isinf(b));
    assert(!isinf(c));
    assert(!(x_1 == 0));
    assert(!(x_2 == 0));
    assert(!(x_1 == x_2));

    if (fabs(a) <= MIN_DELT)   //проверка условий бесконечного количества решений
    {
        return linerial(b, c, x_1);
    }
    else
    {
        return qadrat(a, b, c, x_1, x_2);
    }
}

int abc_scan(double *a, double *b, double *c)
{

    assert(!(a == 0));
    assert(!(b == 0));
    assert(!(c == 0));
    assert(!(a == b));
    assert(!(a == c));
    assert(!(b == c));

    int take_stok = 0;                    // Значение инициирующее подведение итога
    int sc_out = 0;                       // Значение для записи вывода skan_variable
    double coef[NUM_OF_COEF] = {0, 0, 0}; // Массив для записи коэфициентов
                                          // [0]-a
                                          // [1]-b
                                          // [2]-c
    int cell_nom = 0;                     // номер итерируемой ячейки

    printf("==========================================================================\n");
    printf("Введите коэффициенты \n(для завершения программы введите %c): \n", END_SIMVOL);

    //начало проверок ввода числа
    while (cell_nom < NUM_OF_COEF)
    {
        sc_out = skan_variable(NAME_VAR[cell_nom], coef + cell_nom);

        if (sc_out == NEED_TAKE_STOK)
        {
            take_stok = 1;
        }
        if (sc_out == END_PROGRAM)
        {
            break;
        }

        cell_nom++;
    }
    //конец проверок ввода числа

    *a = coef[0];
    *b = coef[1];
    *c = coef[2];

    //подведение итога, если ввод столкнулся с проблемами (повышает удобство чтения ответов т.к. собирает коэфициенты в одном месте)
    if ((take_stok == 1) && (sc_out != END_PROGRAM))
    {
        printf("--------------------------------------------------------------------------\n");
        printf("a = %.*f\n", NUM_AF_POINT, *a);
        printf("b = %.*f\n", NUM_AF_POINT, *b);
        printf("c = %.*f\n", NUM_AF_POINT, *c);
    }

    printf("--------------------------------------------------------------------------\n");

    //вывод значения определяющего завершить программу или продолжить
    if (sc_out == END_PROGRAM)
    {
        return END_PROGRAM;
    }
    return OK;

}

int skan_variable(const char var_name[], double* var)
{

    assert (!(var == 0));
    assert (!(var_name == "\n"));

    int sc_chek = 0;         // Проверка наличия в вводе числа (первым в буфере)
    int sc_error = 0;        // Проверка наличия в воде символа кроме первого # и \n
    int end_simvol_chek = 0; // Проверка на наличие конечного символа первым в буфере ввода (после scanf)
    char ch = '\n';          // Переменная для символа из буфера обмена
    int out = OK;            // Вывод программы

    while(1)
    {
        sc_chek = 0;
        sc_error = 0;
        end_simvol_chek = 0;
        ch = '\n';

        printf("%s = ", var_name);
        sc_chek = scanf("%lf", var);

        ch = getchar();

        if (ch == END_SIMVOL)
        {
            end_simvol_chek = 1;
            ch = getchar();
        }

        while (ch != '\n')
        {
            ch = getchar();
            sc_error = 1;
        }

        if ((sc_chek != 1) && (end_simvol_chek == 1) && (sc_error != 1))
        {
            if(end_question() == END_PROGRAM)
            {
                return END_PROGRAM;
            }
            else
            {
                out = NEED_TAKE_STOK;
            }
        }

        if ((sc_error == 1) || ((sc_chek == 1) && (end_simvol_chek == 1)))
        {
            printf("Вы ошиблись при вводе значения\a\n");
            printf("(При вводе числа или символа завершения присутствуют лишние символы)\n");
            printf("Для завершения программы введите %c \n", END_SIMVOL);
            out = NEED_TAKE_STOK;
        }

        if ((sc_chek == 1) && (end_simvol_chek != 1) && (sc_error != 1))
        {
            break;
        }
    }

    return out;

}

int end_question(void)
{

    char pr_end_Y_N = 'N';

    while(1)
        {
            printf("Вы действительно хотите завершить программу [Y/N]\a: "); //проверка на ошибку пользователя


            pr_end_Y_N = getchar();         //Запись ответа по первому символу


            //очистка буфера ввода
                while (getchar() != '\n')
                {;}

            //Проверка ответа
            if ((pr_end_Y_N == 'Y') || (pr_end_Y_N == 'y'))
            {
                return END_PROGRAM;
            }
            else if ((pr_end_Y_N == 'N') || (pr_end_Y_N == 'n'))
            {
                return OK;
            }
            else
            {
                printf("Я не понял, давй заново\a\n");
            }
        }
}

void start_print(void)
{
    printf("==========================================================================\n");
    printf("                   Решение уравнения a*x^2+b*x+c=0                        \n");
}

void end_print(void)
{
    printf("==========================================================================\n");
    printf("Программа завершена\n");
    printf("для закрытия окна нажмите [Enter] \n");
    printf("==========================================================================\n");

    getchar();

}

void overflow_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overflow)
{

    assert(!(isnan(nom)));
    assert(!(overflow == 0));

    if (isinf(nom))
    {
        printf("%s%s%s", befor_variable, name_variable, after_variable);
        *overflow = true;
    }
}

int unitest(void)
{

    if ((unitest_qadrat() == END_PROGRAM) || (unitest_linerial() == END_PROGRAM) || (unitest_reshalka() == END_PROGRAM))
    {
        return END_PROGRAM;
    }

    return OK;
}
