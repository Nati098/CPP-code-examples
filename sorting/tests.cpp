#ifndef TESTS_CPP
#define TESTS_CPP

#include "sorting.h"

using namespace std;

/*������ �� �����*/
void ReadFile (Sequence <int> &seq)
{
    ifstream file ("OriginSeq.txt");       //��������� ���� ��� ������

    if (!file.is_open())                   // ���� ���� �� ������
        throw (Except(3));

    char *input;
    input = new char[10];
    while (! file.eof())                //���� ���� �� ������
    {
        file.getline (input, 10);
        if (input != "")                //���� �� ������ ������, ������� � ������������������
        {                               //�����, ������ ���������� ������
            int buff = atoi (input);
            seq.Append(buff);
        }
    }

    delete [] input;
    file.close();                              //��������� ����
    cout << "������ �� ����� �������\n";
    return;
}

/*����� �� ����� ������������������*/
void OutputTo (Sequence <int> *seq)
{
    for (int i=0; i <= ((*seq).getLength()-1); i++)
        cout << (*seq).Get(i) << "  ";
    cout << "\n";
    return;
}

/*��������, ��� ����������������� �������������*/
bool Is_Sorted (Sequence <int> &seq)
{
    int flag=1;
    for (int i=0; i < seq.getLength()-1; i++)
    {
        if (flag == 0)
            return false;
        else
        {
            if ((seq.Compare(i+1, i)) || (seq.Get(i+1) == seq.Get(i)))
                flag = 1;
            else
                flag = 0;
        }
    }

    return true;
}

/*��������, ��� ����������������� ������������� � �������� �������*/
bool Is_Sorted_Reverse (Sequence <int> &seq)
{
    int flag;
    for (int i=seq.getLength()-1; i > 0; i--)
    {
        if (flag == 0)
            return false;
        else
        {
            if (seq.Compare(i-1, i)  || (seq.Get(i-1) == seq.Get(i)))
                flag = 1;
            else
                flag = 0;
        }
    }

    return true;
}

bool MainTest()
{
    srand(time(0));

    ofstream file;
    file.open("OriginSeq.txt");
    int data;
    for (int i=1; i < 2500; i++)
    {
        data = -50 + rand() % 101;      //��������� ����� �� -50 �� 50
        file << data << endl;
    }
    data = -50 + rand() % 101;
    file << data;
    file.close();

    ArraySequence <int> ar1;
    ArraySequence <int> ar2;
    ArraySequence <int> ar3;
    ListSequence <int> l1;
    ListSequence <int> l2;
    ReadFile(ar1);
    ReadFile(ar2);
    ReadFile(ar3);
    ReadFile(l1);
    ReadFile(l2);

    cout << "\nC��������� 2500 ���������:\n" << endl;

    int timer_1, timer_2, timer_3;

    file.open("Test_results.txt");


    /*����������������� �������*/
    cout << "����������������� �������" << endl;
{
    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "���������� ��������� ������� ���������\n����� ���������: " << timer_1 << endl;
    else
    {
        cout << "���������� ��������� �� ���������\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "��������� ���������� ������� ���������\n����� ���������: " << timer_2 << endl;
    else
    {
        cout << "��������� ���������� �� ���������\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "���������� ����� ������� ���������\n����� ���������: " << timer_3 << endl;
    else
    {
        cout << "���������� ����� �� ��������a\n";
        return false;
    }

    file << "����������������� �������\n�������: " << timer_1 << endl;
    file << "��������� ����������: " << timer_2 << endl;
    file << "���������� �����: " << timer_3 << endl;

    cout << "\n����������������� ������" << endl;

    timer_1 = BubbleSort(l1);
    if (Is_Sorted(l1))
        cout << "���������� ��������� ������� ���������\n����� ���������: " << timer_1 << endl;
    else
    {
        cout << "���������� ��������� �� ���������\n";
        return false;
    }

    timer_2 = ShakeSort(l2);
    if (Is_Sorted(l2))
        cout << "��������� ���������� ������� ���������\n����� ���������: " << timer_2 << endl;
    else
    {
        cout << "��������� ���������� �� ���������\n";
        return false;
    }

    file << "����������������� ������\n�������: " << timer_1 << endl;
    file << "��������� ����������: " << timer_2 << endl;
}


    /*������� � �������� �������*/
    cout << "\n������� � �������� �������" << endl;
{
    ar1.InverseSeq();
    if (Is_Sorted_Reverse(ar1))
        cout << "������������������ ar1 ������������� � �������� �������" << endl;
    else
    {
        cout << "������������������ ar1 �� ������������� � �������� �������" << endl;
        return false;
    }

    ar2.InverseSeq();
    if (Is_Sorted_Reverse(ar2))
        cout << "������������������ ar2 ������������� � �������� �������" << endl;
    else
    {
        cout << "������������������ ar2 �� ������������� � �������� �������" << endl;
        return false;
    }

    ar3.InverseSeq();
    if (Is_Sorted_Reverse(ar3))
        cout << "������������������ ar3 ������������� � �������� �������" << endl;
    else
    {
        cout << "������������������ ar3 �� ������������� � �������� �������" << endl;
        return false;
    }

    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "���������� ��������� ������� ���������\n����� ���������: " << timer_1 << endl;
    else
    {
        cout << "���������� ��������� �� ���������\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "��������� ���������� ������� ���������\n����� ���������: " << timer_2 << endl;
    else
    {
        cout << "��������� ���������� �� ���������\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "���������� ����� ������� ���������\n����� ���������: " << timer_3 << endl;
    else
    {
        cout << "���������� ����� �� ��������a\n";
        return false;
    }

    file << "������� � �������� �������\n�������: " << timer_1 << endl;
    file << "��������� ����������: " << timer_2 << endl;
    file << "���������� �����: " << timer_3 << endl;
}


    /*��������������� �������*/
    cout << "\n��������������� �������" << endl;
{
    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "���������� ��������� ������� ���������\n����� ���������: " << timer_1 << endl;
    else
    {
        cout << "���������� ��������� �� ���������\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "��������� ���������� ������� ���������\n����� ���������: " << timer_2 << endl;
    else
    {
        cout << "��������� ���������� �� ���������\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "���������� ����� ������� ���������\n����� ���������: " << timer_3 << endl;
    else
    {
        cout << "���������� ����� �� ��������a\n";
        return false;
    }

    file << "��������������� �������\n�������: " << timer_1 << endl;
    file << "��������� ����������: " << timer_2 << endl;
    file << "���������� �����: " << timer_3 << endl;
}

    file.close();


    return true;
}

#endif // TESTS_CPP



/*
    try
    {

    }
    catch (Except &e)
    {
        cout << "!!!" << e.Message() << endl;
    }

 */
