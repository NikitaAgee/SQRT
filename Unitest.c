
#include "Pre_Unitest.h"


int unitest_reshalka(void)
{

    int nom_of_unitest = 0;
    double a = 0, b = 0, c = 0;
    double x_1 = 0, x_2 = 0;
    int reshalka_error = OK;

    while (nom_of_unitest < NUM_OF_UNITEST_RESHALKA)
    {
        a = 0;
        b = 0;
        c = 0;
        x_1 = 0;
        x_2 = 0;
        a = UNITEST_IN_RESHALKA[nom_of_unitest][0];
        b = UNITEST_IN_RESHALKA[nom_of_unitest][1];
        c = UNITEST_IN_RESHALKA[nom_of_unitest][2];
        reshalka_error = reshalka (a, b, c, &x_1, &x_2);
        if (((fabs(x_1 - UNITEST_OUT_RESHALKA[nom_of_unitest][0])) > U_MIN_DELT) || ((fabs(x_2 - UNITEST_OUT_RESHALKA[nom_of_unitest][1])) > U_MIN_DELT) || ((fabs(reshalka_error - UNITEST_OUT_RESHALKA[nom_of_unitest][2])) > U_MIN_DELT))
        {
            printf("reshalka юнитест %d провален\n", nom_of_unitest);
            printf("Ввод:\n");
            printf("a = %f\n", a);
            printf("b = %f\n", b);
            printf("c = %f\n", c);
            printf("Вывод:  |Реальность|  Ожидание\n");
            printf("x_1     |%10f|%10f\n", x_1, UNITEST_OUT_RESHALKA[nom_of_unitest][0]);
            printf("x_2     |%10f|%10f\n", x_2, UNITEST_OUT_RESHALKA[nom_of_unitest][1]);
            printf("res_err |%10f|%10f\n", reshalka_error, UNITEST_OUT_RESHALKA[nom_of_unitest][2]);
            return END_PROGRAM;
        }
        nom_of_unitest++;
    }
    printf("reshalka прошла юнитесты\n");
    return OK;
}

int unitest_qadrat(void)
{

    int nom_of_unitest = 0;
    double a = 0, b = 0, c = 0;
    double x_1 = 0, x_2 = 0;
    int qadrat_error = OK;

    while (nom_of_unitest < NUM_OF_UNITEST_QADRAT)
    {
        a = 0;
        b = 0;
        c = 0;
        x_1 = 0;
        x_2 = 0;
        a = UNITEST_IN_QADRAT[nom_of_unitest][0];
        b = UNITEST_IN_QADRAT[nom_of_unitest][1];
        c = UNITEST_IN_QADRAT[nom_of_unitest][2];
        qadrat_error = qadrat (a, b, c, &x_1, &x_2);
        if (((fabs(x_1 - UNITEST_OUT_QADRAT[nom_of_unitest][0])) > U_MIN_DELT) || ((fabs(x_2 - UNITEST_OUT_QADRAT[nom_of_unitest][1])) > U_MIN_DELT) || ((fabs(qadrat_error - UNITEST_OUT_QADRAT[nom_of_unitest][2])) > U_MIN_DELT))
        {
            printf("qadrat юнитест %d провален\n", nom_of_unitest);
            printf("Ввод:\n");
            printf("a = %f\n", a);
            printf("b = %f\n", b);
            printf("c = %f\n", c);
            printf("Вывод:  |Реальность|  Ожидание\n");
            printf("x_1     |%10f|%10f\n", x_1, UNITEST_OUT_QADRAT[nom_of_unitest][0]);
            printf("x_2     |%10f|%10f\n", x_2, UNITEST_OUT_QADRAT[nom_of_unitest][1]);
            printf("res_err |%10f|%10f\n", qadrat_error, UNITEST_OUT_QADRAT[nom_of_unitest][2]);
            return END_PROGRAM;
        }
        nom_of_unitest++;
    }
    printf("qadrat прошла юнитесты\n");
    return OK;
}

int unitest_linerial(void)
{

    int nom_of_unitest = 0;
    double b = 0, c = 0;
    double x_1 = 0, x_2 = 0;
    int linerial_error = OK;

    while (nom_of_unitest < NUM_OF_UNITEST_LINERIAL)
    {
        b = 0;
        c = 0;
        x_1 = 0;

        b = UNITEST_IN_LINERIAL[nom_of_unitest][0];
        c = UNITEST_IN_LINERIAL[nom_of_unitest][1];
        linerial_error = linerial (b, c, &x_1);
        if (((fabs(x_1 - UNITEST_OUT_LINERIAL[nom_of_unitest][0])) > U_MIN_DELT) || ((fabs(linerial_error - UNITEST_OUT_LINERIAL[nom_of_unitest][1])) > U_MIN_DELT))
        {
            printf("linerial юнитест %d провален\n", nom_of_unitest);
            printf("Ввод:\n");
            printf("b = %f\n", b);
            printf("c = %f\n", c);
            printf("Вывод:  |Реальность|  Ожидание\n");
            printf("x_1     |%10f|%10f\n", x_1, UNITEST_OUT_LINERIAL[nom_of_unitest][0]);
            printf("res_err |%10f|%10f\n", linerial_error, UNITEST_OUT_LINERIAL[nom_of_unitest][1]);
            return END_PROGRAM;
        }
        nom_of_unitest++;
    }
    printf("qadrat прошла юнитесты\n");
    return OK;
}
