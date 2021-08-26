#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

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
