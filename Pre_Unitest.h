#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define U_MIN_DELT 0.00001              ///< Значение, которое обозначает минимальное значение модуля не нулевого числа


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

//Характеристики юнитеста reshalka
#define NUM_OF_COEF_RESHALKA 3        ///< Количество коэфициентов в reshalka
#define NUM_OF_UNITEST_RESHALKA 6     ///< Количество юнитестов reshalka
#define NUM_OUT_OF_UNITEST_RESHALKA 3 ///< Количество выводов функции reshalka

//Характеристики юнитеста qadrat
#define NUM_OF_COEF_QADRAT 3        ///< Количество коэфициентов в qadrat
#define NUM_OF_UNITEST_QADRAT 3     ///< Количество юнитестов qadrat
#define NUM_OUT_OF_UNITEST_QADRAT 3 ///< Количество выводов функции qadrat

//Характеристики юнитеста linerial
#define NUM_OF_COEF_LINERIAL 2        ///< Количество коэфициентов в linerial
#define NUM_OF_UNITEST_LINERIAL 3     ///< Количество юнитестов linerial
#define NUM_OUT_OF_UNITEST_LINERIAL 2 ///< Количество выводов функции linerial

/*!
Проводит тестирование функции reshalka
\return выводит в соответствии Error_skan_var
*/
int unitest_reshalka(void);

/*!
Проводит тестирование функции qadrat
\return выводит в соответствии Error_skan_var
*/
int unitest_qadrat(void);

/*!
Проводит тестирование функции linerial
\return выводит в соответствии Error_skan_var
*/
int unitest_linerial(void);

/*!
Вызывает все тестирования и оповещает о проблемах
\return выводит в соответствии Error_skan_var
*/
int unitest(void);

//=====================================================================================
/// Ввод для юнитеста reshalka
const double UNITEST_IN_RESHALKA[NUM_OF_UNITEST_RESHALKA][NUM_OF_COEF_RESHALKA] =
    {
    {0, 0, 0},     // Поверка на уникальный случай бесконечности корней
    {0, 0, 1},     // Проверка на отсутствие корней
    {0, 1, 1},     // Проверка на решение линейных уравнений
    {1, -2, 1},    // Проверка на квадратное уравнение с 1 корнем
    {1, -1, -2},   // Проверка на квадратное уравнение с 2 корнями
    {1, 1, 1},     // проверка на отсутствие корней
    };

/// Ожидаемый вывод для юнитеста reshalka
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
/// Ввод для юнитеста qadrat
const double UNITEST_IN_QADRAT[NUM_OF_UNITEST_QADRAT][NUM_OF_COEF_QADRAT] =
    {
    {1, -2, 1},    // Проверка на квадратное уравнение с 1 корнем
    {1, -1, -2},   // Проверка на квадратное уравнение с 2 корнями
    {1, 1, 1},     // проверка на отсутствие корней
    };

/// Ожидаемый вывод для юнитеста qadrat
const double UNITEST_OUT_QADRAT[NUM_OF_UNITEST_QADRAT][NUM_OUT_OF_UNITEST_QADRAT] =
    {
    {1, 0, ROOTS_1},
    {2, -1, ROOTS_2},
    {0, 0, ROOTS_0},
    };

//=====================================================================================
/// Ввод для юнитеста linerial
const double UNITEST_IN_LINERIAL[NUM_OF_UNITEST_LINERIAL][NUM_OF_COEF_LINERIAL] =
    {
    {0, 0},     // Поверка на уникальный случай бесконечности корней
    {0, 1},     // Проверка на отсутствие корней
    {1, 1},     // Проверка на решение линейных уравнений
    };

/// Ожидаемый вывод для юнитеста linerial
const double UNITEST_OUT_LINERIAL[NUM_OF_UNITEST_LINERIAL][NUM_OUT_OF_UNITEST_LINERIAL] =
    {
    {0, ROOTS_INF},
    {0, ROOTS_0},
    {-1, ROOTS_1},
    };

//=====================================================================================
