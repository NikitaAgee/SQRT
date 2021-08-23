
bool abc_lim_over_print(double a, double b, double c)
{

    // ����������� ��������� � ������������ ����� ������� �������� ����������, ������� �����������
    char befor_variable[50] = "������� ������� (�� ������) ����������: ";

    bool overflow = false; // ����������� ����� �������

    // �������� ������������� ��������
    overflow_alarm (a,  befor_variable, "a", "\n", &overflow);
    overflow_alarm (b,  befor_variable, "b", "\n", &overflow);
    overflow_alarm (c,  befor_variable, "c", "\n", &overflow);

    return overflow;
}

void x_lim_over_print(double x_1, double x_2, int root_count)
{

    char befor_variable[50] = "������� ������� (�� ������) ������: ";
    bool overflow = false;

    //�������� x_1 x_2
    overflow_alarm (x_1,  befor_variable, "x_1", "\n", &overflow);
    overflow_alarm (x_2,  befor_variable, "x_2", "\n", &overflow);

    if (overflow)
    {
        return;
    }
    switch (root_count) //dsdjl rjhytq
    {
        case ROOTS_2:
            printf("����� ���������:\n");
            printf("X_1 = %.*f\n", NUM_AF_POINT, x_1);
            printf("X_2 = %.*f\n", NUM_AF_POINT, x_2);
            break;
        case ROOTS_1:
            printf("������ ���������:\n");
            printf("X = %.*f\n", NUM_AF_POINT, x_1);
            break;
        case ROOTS_0:
            printf("������ ���\n");
            break;
        case ROOTS_INF:
            printf("������ �������������\n");
            break;
        case ERROR:
            printf("���-�� ����� �� �� �����\n");
            break;
        default:
            printf("���-�� ����� ����� �� �� �����\n");
    }
}

int qadrat(double a, double b, double c, double *x_1, double *x_2)
{
    double Dis;   /*������������ (�������� ��� double ����� �������)*/
    double skDis; /*������ �������������*/
    char befor_variable[50] = "������������ ������� ������� (�� ������)\n ";
    bool overflow = false;

    /*���������� �������������*/
    Dis = ((b * b) - (4 * c * a));

    /*�������� ������������ Dis*/
    overflow_alarm (Dis,  befor_variable, "Dis", "\n", &overflow);
    if (overflow)
    {
        return OVERFLOW_DIS;
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

        if (fabs(Dis) < MIN_DELT)
        {
            *x_2 = 0;
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
    *x = ((-c) / b);
    return ROOTS_1;
}

int reshalka (double a, double b, double c, double* x_1, double* x_2)
{
    if ((fabs(a) < MIN_DELT) && (fabs(b) < MIN_DELT) && (fabs(c) < MIN_DELT))        //�������� ������� ������������ ���������� �������
    {
        return ROOTS_INF;
    }
    else if ((fabs(a) < MIN_DELT) && (fabs(b) > MIN_DELT))                           //������� �� ������������/������������� ���������� ����������
    {
        return linerial (b, c, x_1);
    }
    else if ((fabs(a) < MIN_DELT) && (fabs(b) < MIN_DELT) && (fabs(c) > MIN_DELT))   //�������� ���������� ������ ��-�� ����������� ����������
    {
        return ROOTS_0;
    }
    else
    {
        return qadrat(a, b, c, x_1, x_2);
    }
}

int abc_scan(double *a, double *b, double *c)
{

    int take_stok = 0;          // �������� ������������ ���������� �����
    int sk_out = 0;             // �������� ��� ������ ������ �� �������
    double coef[NUM_OF_COEF] = {0, 0, 0}; // ������ ��� ������ ������������
                                // [0]-a
                                // [1]-b
                                // [2]-c
    int cell_nom = 0;           // ����� ����������� ������

    printf("==========================================================================\n");
    printf("������� ������������ \n(��� ���������� ��������� ������� %c): \n", END_SIMVOL);

    //������ �������� ����� �����
    while (cell_nom < NUM_OF_COEF)
    {
        sk_out = skan_variable(NAME_VAR[cell_nom], &coef[cell_nom]);

        if (sk_out == NEED_TAKE_STOK)
        {
            take_stok = 1;
        }
        if (sk_out == END_PROGRAM)
        {
            break;
        }

        cell_nom++;
    }
    //����� �������� ����� �����

    *a = coef[0];
    *b = coef[1];
    *c = coef[2];

    //���������� �����, ���� ���� ���������� � ���������� (�������� �������� ������ ������� �.�. �������� ����������� � ����� �����)
    if ((take_stok == 1) && (sk_out != END_PROGRAM))
    {
        printf("--------------------------------------------------------------------------\n");
        printf("a = %.*f\n", NUM_AF_POINT, *a);
        printf("b = %.*f\n", NUM_AF_POINT, *b);
        printf("c = %.*f\n", NUM_AF_POINT, *c);
    }

    printf("--------------------------------------------------------------------------\n");

    //����� �������� ������������� ��������� ��������� ��� ����������
    if (sk_out == END_PROGRAM)
    {
        return END_PROGRAM;
    }
    return OK;

}

int skan_variable(const char var_name[], double* var)
{

    int sc_chek = 0;         // �������� ������� � ����� ����� (������ � ������)
    int sc_error = 0;        // �������� ������� � ���� ������� ����� ������� # � \n
    int end_simvol_chek = 0; // �������� �� ������� ��������� ������� ������ � ������ ����� (����� scanf)
    char ch = '\n';          // ���������� ��� ������� �� ������ ������
    int out = OK;            // ����� ���������

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

        if ((sc_chek != 1) && (end_simvol_chek ==1) && (sc_error != 1))
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

        if ((sc_error == 1) || ((sc_chek == 1) && (end_simvol_chek ==1)))
        {
            printf("�� �������� ��� ����� ��������\a\n");
            printf("(��� ����� ����� ��� ������� ���������� ������������ ������ �������)\n");
            printf("��� ���������� ��������� ������� %c \n", END_SIMVOL);
            out = NEED_TAKE_STOK;
        }

        if ((sc_chek == 1) && (end_simvol_chek !=1) && (sc_error != 1))
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
            printf("�� ������������� ������ ��������� ��������� [Y/N]\a: "); //�������� �� ������ ������������


            pr_end_Y_N = getchar();         //������ ������ �� ������� �������


            //������� ������ �����
                while (getchar() != '\n')
                {;}

            //�������� ������
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
                printf("� �� �����, ���� ������\a\n");

                //������� ������ �����
                while (getchar() != '\n')
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

}

void overflow_alarm (double nom, char befor_variable[], char name_variable[], char after_variable[], bool* overflow)
{
    if(isinf(nom))
    {
        printf("%s%s%s", befor_variable, name_variable, after_variable);
        *overflow = true;
    }
}

int unitest_reshalka(void)
{

    int nom_of_unitest = 0;
    double a=0, b=0, c=0;
    double x_1=0, x_2=0;
    int reshalka_error = OK;

    while(nom_of_unitest < NUM_OF_UNITEST)
    {
        a = 0;
        b = 0;
        c = 0;
        x_1 = 0;
        x_2 = 0;
        a = UNITEST_IN[nom_of_unitest][0];
        b = UNITEST_IN[nom_of_unitest][1];
        c = UNITEST_IN[nom_of_unitest][2];
        reshalka_error = reshalka (a, b, c, &x_1, &x_2);
        if(((fabs(x_1 - UNITEST_OUT[nom_of_unitest][0])) > MIN_DELT) || ((fabs(x_2 - UNITEST_OUT[nom_of_unitest][1])) > MIN_DELT) || ((fabs(reshalka_error - UNITEST_OUT[nom_of_unitest][2])) > MIN_DELT))
        {
            printf("������� %d ��������\n", nom_of_unitest);
            printf("����:\n");
            printf("a = %f\n", a);
            printf("b = %f\n", b);
            printf("c = %f\n", c);
            printf("����:   ��������   ����������\n");
            printf("x_1     %10f %10f\n", x_1, UNITEST_OUT[nom_of_unitest][0]);
            printf("x_2     %10f %10f\n", x_2, UNITEST_OUT[nom_of_unitest][1]);
            printf("res_err %10f %10f\n", reshalka_error, UNITEST_OUT[nom_of_unitest][2]);
            return 0;
        }
        nom_of_unitest++;
    }
    printf("������� �������\n");
    return 1;
}
