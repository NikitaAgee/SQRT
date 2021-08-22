#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#define  NUM_AF_POINT 4 ///<цифры после запятой при выводе

/// Варианты вывода функций reshalka, qadrat решалка
enum Error_reshalka
{
    ROOTS_2 = 2,         ///< Уравнение имеет 2 корня
    ROOTS_1 = 1,         ///< Уравнение имеет 1 корень
    ROOTS_0 = 0,         ///< У уравнения нет корней
    ROOTS_INF = -1,      ///< Уравнение имеет бесконечность решений
    OVERCHARGE_DIS = -2, ///< Ошибка: Дискриминант при решении уравнения переполнелся
    ERROR = -3           ///< Ошибка: Непредвиденное состояние ( не должно выводиться, но есть для диагностики неутённых состояний, которые может вывести функция после будущих изменений)
};

/// Варианты вывода функций abc_scan skan_variable
enum Error_skan_var
{
    OK = 0,              ///< С вводом всё хорошо
    END_PROGRAM = 1,     ///< Нужно завершить программу
    NEED_TAKE_STOK = 2   ///< Нужно подытожить коэфициенрты уравнения
};

/*!
Оформляет ввод коефициентов и принимает их значение + отслеживает завершение программы
\param *a,*b,*c double Указатели на переменные для хранения коэфициентов
\return в соответствии Error_skan_var
*/
int abc_scan(double* a, double* b, double* c);

/*!
Оформляет ввод некоторого значения и проверяет ввод на ошибки.
Так же она инициализирует завершение программы в зависимости от ввода.
\param var_name строчка с названием переменной
\param *var указатель на переменную для записи ввода
\return в соответствии Error_skan_var
*/
int skan_variable(char var_name[], double* var);

/*!
Задаёт пользователю вопрос о завершении программы, анализирует ответ и выводит соответствующее значение
\return в соответствии Error_skan_var
*/
int end_question(void);

/*!
Проверяет значение на переполнение и выводит оповещающее сообщение (оно может меняться в зависимости от введённых параметров), если это произошло
\param nom число на проверку
\param befor_variable сообщение перед выводом названия переменной
\param name_variable  название переменной
\param after_variable сообщение после вывода названия переменной
\param *overcharge указатель на переменную для записи значения (true - если число переполнено folse - не записывается для удобности определения наличия переполненного числа при применении к группе чисел)
*/
void overcharge_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overcharge);

/*!
Проверяет коэфициенты уравнения на переполнение и выводит соответсвующее опровещение
\param a,b,c параметры уравнения
\return возвращает true если есть переполненое значение folse если - нет
*/
bool abc_lim_over_print(double a, double b, double c);

/*!
Проверяет корни уравнения на переполнение, выводит оповещение об этом или печатает сами корни.
\param x_1,x_2 корни уравнения
\param root_count количество корней (принимаемые значения соответствуют Error_reshalka)
*/
void x_lim_over_print(double x_1, double x_2, int root_count);

/*!
Решает квадратное уравнение
\param a,b,c коэфициенты уравнения
\param x_1,x_2 корни уравнения
\return соответствует Error_reshalka
*/
int qadrat ( double a, double b, double c, double* x_1, double* x_2);

/*!
Решает линейное уравнение
\param b,c коэфициенты уравнения
\param *x указатель на переменную для записи корня
\return соответствует Error_reshalka
*/
int linerial (double b, double c, double *x);

/*!
Решает квадратное/линейное уравнение, определяет бесконечность корней
\param a,b,c коэфициенты уравнения
\param *x_1, *x_2 указателb на переменную для записй корней
\return соответствует Error_reshalka
*/
int reshalka (double a, double b, double c, double* x_1, double* x_2);

/*!
Печатает шапку оформления программы
*/
void start_print();

/*!
Печатает печатает оповещение о завершении программы и задерживает закрытие
окна до нажатия [Enter]
*/
void end_print();


int main(void)
{

    setlocale(LC_CTYPE,"Russian"); //Для вывода руских букв

    double a, b, c;     // Определение переменных для коэфициентов уравнения
    double x_1, x_2;    // Определение переменных для коней
    int reshalka_error; // Определение переменной для количества корней

    start_print();

    while( abc_scan(&a, &b, &c) == 0)                // Ввод коэфициентов
    {
        if ( abc_lim_over_print (a, b, c ) )         // Проверка коэфициентов
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

}

bool abc_lim_over_print(double a, double b, double c)
{

    // Определение сообщения о переполнении перед выводом названия переменной, которая переполнена
    char befor_variable[50] = "Слишком большой (по модулю) коэфициент: ";

    bool overcharge = false; // определение выход функции

    // Проверка переполненных значений
    overcharge_alarm (a,  befor_variable, "a", "", &overcharge);
    overcharge_alarm (b,  befor_variable, "b", "", &overcharge);
    overcharge_alarm (c,  befor_variable, "c", "", &overcharge);

    return overcharge;
}

void x_lim_over_print(double x_1, double x_2, int root_count)
{

    char befor_variable[50] = "Слишком большой (по модулю) корень: ";
    bool overcharge = false;

    if (root_count == 2)
    {
        //проверка x_1 x_2
        overcharge_alarm (x_1,  befor_variable, "x_1", "", &overcharge);
        overcharge_alarm (x_2,  befor_variable, "x_2", "", &overcharge);
    }
    if(root_count == 1)
    {
        //проверка x
        overcharge_alarm (x_1,  befor_variable, "x", "", &overcharge);

    }

    if ( overcharge == false)
    {
        /*вывод корней*/
        if (root_count == 2)
        {
            printf("Корни уравнения:\n");
            printf("X_1 = %.*f\n", NUM_AF_POINT, x_1);
            printf("X_2 = %.*f\n", NUM_AF_POINT, x_2);
        }
        if (root_count == 1)
        {
            printf("Корень уравнения:\n");
            printf("X = %.*f\n", NUM_AF_POINT, x_1);
        }
        if (root_count == 0)
        {
            printf("Корней нет\n");
        }
        if (root_count == -1)
        {
            printf("Корней бесконечность\n");
        }
        if (root_count == -3)
        {
            printf("Что-то пошло не по плану\n");
        }
    }
}

int qadrat(double a, double b, double c, double *x_1, double *x_2)
{
    double Dis;   /*Дискриминант (определён как double чтобы хватало)*/
    double skDis; /*Корень дискриминанта*/
    char befor_variable[50] = "Дискриминант слишком большой (по модулю)\n ";
    bool overcharge = false;

    /*Вычисление дискриминанта*/
    Dis = ((b * b) - (4 * c * a));

    /*Проверка переполнения Dis*/
    overcharge_alarm (Dis,  befor_variable, "Dis", "", &overcharge);
    if (overcharge)
    {
        return OVERCHARGE_DIS;
    }

    /* начало ветвления резуультатов в зависимости от дискрииминанта*/
    else if (Dis<0)
    {
        return ROOTS_0;
    }
    else
    {
        /*Корень дискриминанта*/
        skDis = sqrt(Dis);

        /*вычисление x_1 и x_2*/
        *x_1 = ((-b + skDis) / (2 * a));
        *x_2 = ((-b - skDis) / (2 * a));

        /*звпись *n, соответствующего дискриминанту */

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
    if((fabs (a) < 0.00001) && (fabs (c) < 0.00001))        //проверка бесконечности
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

    printf("Введите коэффициенты \n(для завершения программы введите любую строчку начинающуюся с символа): \n");

    //начало проверок ввода числа
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
    //конец проверок ввода числа

    //подведение итога, если ввод столкнулся с проблемами (повышает удобство чтения ответов т.к. собирает коэфициенты в одном месте)
    if ((take_stok == 1) && (err_out == 0))
    {

        printf("--------------------------------------------------------------------------\n");
        printf("a = %.*f\n", NUM_AF_POINT, *a);
        printf("b = %.*f\n", NUM_AF_POINT, *b);
        printf("c = %.*f\n", NUM_AF_POINT, *c);
    }

    printf("--------------------------------------------------------------------------\n");

    //вывод значения определяющего завершить программу или продолжить
    if (err_out == 1)
    {
        return END_PROGRAM;
    }
    return OK;

}

int skan_variable(char var_name[], double* var)
{

    int sk_chek = 0;  //проверка наличия в вводе числа
    int sk_error = 0; //проверка ввода на отсутствие букв
    char ch;          //буфер для символа
    int out = OK;     //вывод программы

    while(1)
    {
        printf("%s = ", var_name);
        sk_chek = scanf("%lf", var);  //ввод числа

        ch = getchar();       // проверка ввода на отсутствие опечаток
        sk_error = 0;         // (наличие символов в числовом вводе)
                              //
        while(ch != '\n')     //
        {                     //
            if (ch !='\n')    //
            {                 //
                sk_error = 1; //
            }                 //
            ch = getchar();   //
        }                     //

        if (sk_chek == 0)                // переход на проверку случайности попытки выхода
        {                                // (вопрос пользователю)
            if(end_question())           //
            {                            //
            return END_PROGRAM;          //
            }                            //
            else                         //
            {                            //
                out = NEED_TAKE_STOK;    //
                                         //
                //очистка буфера ввода   //
                while (getchar()!='\n')  //
                {;}                      //
                                         //
                continue;                //
            }                            //
        }
        else if (sk_error == 1) //оповещение о опечатке при вводе числа
        {
            printf("При вводе коэфициентов вы ошиблись (ввели в числе символ или пробел)\nдля завершения программы введите любой символ первым в строчке\nПовторите ввод:\n");
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
            printf("Вы действительно хотите завершить программу [Y/N]: "); //проверка на ошибку пользователя


            pr_end_Y_N = getchar();                         //Запись ответа по первому символу

            //Проверка ответа
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
                printf("Я не понял, давй заново\n");

                //очистка буфера ввода
                while (getchar()!='\n')
                {;}
            }
        }
}


void start_print()
{
    printf("==========================================================================\n");
    printf("                   Решение уравнения a*x^2+b*x+c=0                        \n");
}

void end_print()
{
    printf("==========================================================================\n");
    printf("Программа завершена\n");
    printf("для закрытия окна нажмите [Enter] \n");
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



