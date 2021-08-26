#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define MIN_DELT 0.00001              ///< Значение, которое обозначает минимальное значение модуля не нулевого числа
#define NUM_AF_POINT 4                ///< Количество цифр после запятой при выводе
#define NUM_OF_COEF 3                 ///< Количество коэфициентов


const char* NAME_VAR[NUM_OF_COEF] = {"a","b","c"};///< Список имён переменных
const char END_SIMVOL = '#'; ///< Символ при вводе которого завершается программа

/// Варианты вывода функций reshalka, qadrat
enum Error_reshalka
{
    ROOTS_2 = 2,         ///< Уравнение имеет 2 корня
    ROOTS_1 = 1,         ///< Уравнение имеет 1 корень
    ROOTS_0 = 0,         ///< У уравнения нет корней
    ROOTS_INF = -1,      ///< Уравнение имеет бесконечность решений
    OVERFLOW_DIS = -2,   ///< Ошибка: Дискриминант при решении уравнения переполнелся
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
\param[out] *a,*b,*c double Указатели на переменные для хранения коэфициентов
\return в соответствии Error_skan_var
*/
int abc_scan(double* a, double* b, double* c);

/*!
Оформляет ввод некоторого значения и проверяет ввод на ошибки.
Так же она инициализирует завершение программы в зависимости от ввода.
\param[in] var_name строчка с названием переменной
\param[out] *var указатель на переменную для записи ввода
\return в соответствии Error_skan_var
*/
int skan_variable(const char var_name[], double* var);

/*!
Задаёт пользователю вопрос о завершении программы, анализирует ответ и выводит соответствующее значение
\return в соответствии Error_skan_var
*/
int end_question(void);

/*!
Проверяет значение на переполнение и выводит оповещающее сообщение (оно может меняться в зависимости от введённых параметров), если это произошло
\param[in] nom число на проверку
\param[in] befor_variable сообщение перед выводом названия переменной
\param[in] name_variable  название переменной
\param[in] after_variable сообщение после вывода названия переменной
\param[out] *overflow указатель на переменную для записи значения (true - если число переполнено folse - не записывается для удобности определения наличия переполненного числа при применении к группе чисел)
*/
void overflow_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overflow);

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
\param[in] a,b,c коэфициенты уравнения
\param[out] x_1,x_2 корни уравнения
\return соответствует Error_reshalka
*/
int qadrat ( double a, double b, double c, double* x_1, double* x_2);

/*!
Решает линейное уравнение
\param[in] b,c коэфициенты уравнения
\param[out] *x указатель на переменную для записи корня
\return соответствует Error_reshalka
*/
int linerial (double b, double c, double *x);

/*!
Решает квадратное/линейное уравнение, определяет бесконечность корней
\param[in] a,b,c коэфициенты уравнения
\param[out] *x_1, *x_2 указателb на переменную для записй корней
\return соответствует Error_reshalka
*/
int reshalka (double a, double b, double c, double* x_1, double* x_2);

/*!
Печатает шапку оформления программы
*/
void start_print(void);

/*!
Печатает печатает оповещение о завершении программы и задерживает закрытие
окна до нажатия [Enter]
*/
void end_print(void);
