#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

/// �������� ������ ������� reshalka, qadrat
enum Error_reshalka
{
    ROOTS_2 = 2,         ///< ��������� ����� 2 �����
    ROOTS_1 = 1,         ///< ��������� ����� 1 ������
    ROOTS_0 = 0,         ///< � ��������� ��� ������
    ROOTS_INF = -1,      ///< ��������� ����� ������������� �������
    OVERFLOW_DIS = -2,   ///< ������: ������������ ��� ������� ��������� ������������
    ERROR = -3           ///< ������: �������������� ��������� ( �� ������ ����������, �� ���� ��� ����������� �������� ���������, ������� ����� ������� ������� ����� ������� ���������)
};

/// �������� ������ ������� abc_scan skan_variable
enum Error_skan_var
{
    OK = 0,              ///< � ������ �� ������
    END_PROGRAM = 1,     ///< ����� ��������� ���������
    NEED_TAKE_STOK = 2   ///< ����� ���������� ������������ ���������
};
