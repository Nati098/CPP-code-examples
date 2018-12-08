#include <locale.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "tests.cpp"
//#include "C:\Bill\z\Programms\MyLib\sortedsequence.cpp"


using namespace std;

/*������ �� �����*/
void ReadFile (SortedSequence <int, int> &seq)
{
    ifstream file ("OriginSeq.txt");       //��������� ���� ��� ������

    if (!file.is_open())                   // ���� ���� �� ������
        throw (Except(3));

    char *input;
    input = new char[10];
    while (! file.eof())                //���� ���� �� ������
    {
        file.getline (input, 10);       //��������� ������
        if (input == '\0')
              file.ignore();                  //����� �������� ������ ������ ������ � ����. ����������
        else
        {
            int buff = atoi (input);
            seq.Add(buff);
        }
    }

    delete [] input;
    file.close();                              //��������� ����
    return;
}

/*�������� �� ��, ��� ������� �����*/
bool Is_Digit (char *str)
{
    int i=0;
    int flag=1;
    if (str[0] == '-')   //���� ������ ����� - "-", �� �� ������
        i++;
    while (str[i] != '\0')      //���� �� ������ �� ����� �����
    {
        if (!isdigit(str[i]))   //���� ������ ����� - �� �����,
            flag = 0;           //�� flag = 0

        if (flag == 0)
            return false;       //� �� ������ �� �������

        i++;                    //�����, flag = 1 � ��������� ����.����� �����
    }
    return true;
}

/*������� ����*/
void MainMenu()
{
    cout << "\n�������� �����:\n";
    cout << "1)  ���������� ������������������\n";
    cout << "2)  ���������� ��������� ������\n";
    cout << "3)  ���������� ���-������\n";
    cout << "4)  ����� ������������������\n";
    cout << "5)  ����� ��������� ������\n";
    cout << "6)  ����� ���-������\n";
    cout << "7)  �������� �����\n";
    cout << "8)  ����� �� ��������� ������\n";
    cout << "9)  ����� �� ���-������\n";
    cout << "10) ����� ����\n";
    cout << "0) �����\n";
}

void Menu_1()
{
    cout << "\n�������� �����:\n";
    cout << "1) ���������� �������\n";
    cout << "2) ��������� ��������� �����\n";
}

void Menu_2()
{
    cout << "\n�������� �����:\n";
    cout << "1) �����������\n";
    cout << "2) ������� '�������� �������'\n";
    cout << "3) ������� ����� ���������\n";
    cout << "4) ����� � ������� ����\n";
}

/*����������� �������� �� Menu_1*/
void FillActions(int b)
{
    ofstream file;
    file.open("OriginSeq.txt");         //��������� ���� ��� ������

    if (!file)                          // ���� ���� ������ �������
        throw (Except(3));              //���������� ����������

    int data, num;
    char *info;
    info = new char[10];
    switch (b)
    {
    case 1:                             //������ ����
        num = 0;
        cout << "\n������� �����:\n(��� ������ �������� 'end')\n";


        while (stricmp(info, "end") != 0)
        {
            cin >> info;
            if (stricmp(info, "end") != 0)
            {
                if (!Is_Digit(info))
                    cout << "����������� ������� �����\n";
                else
                {
                    data = atoi(info);
                    file << data << endl;
                    num++;
                }
            }
        }
        break;
    case 2:                     //��������� ��������� �����
        srand(time(0));
        cout << "\n������� ����� ���������: ";
        cin >> num;
        for (int i=0; i < num-1; i++)
        {
            data = -50 + rand() % 101;      //��������� ����� �� -50 �� 50
            file << data << endl;
        }
        data = -50 + rand() % 101;
        file << data;
        break;
    }
    delete [] info;
    file.close();
    return;
}

/*����������� �������� �� Menu_2*/
void SearchSeqActions(int b, SortedArray <int, int> &ar)
{
    int data;
    cout << "\n������� �����, ������� ���� �����: ";
    cin >> data;

    double start = clock();                 //����
    switch (b)
    {
    case 1:
        cout << "\n��������� ������: " << ar.BinarySearch(data) << endl;
        break;
    case 2:
        cout << "\n��������� ������: " << ar.GoldenRatio(data) << endl;
        break;
    case 3:
        int n;              //���-�� ��������
        cout << "������� ����� �������� (����������, �� ������ 15): ";
        cin >> n;
        cout << "\n��������� ������: " << ar.Fibonacci(data, n) << endl;
        break;
    }
    double timer = clock() - start;
    cout << "����� ������ (� ��): " << timer << endl;
    return;
}

/*����������� �������� �� MainMenu*/
void Actions (int b, SortedArray <int, int> &ar, BinaryTree <int, int> &biTree, AVL_Tree <int, int> &avlTr)
{
    int a;
    int data;
    double start, timer;

    switch (b)
    {
    case 1:
        if ((biTree.GetLength() == 0)&&(avlTr.GetLength() == 0))
        {
            Menu_1();
            cin >> a;
            FillActions(a);
            ReadFile(ar);
        }
        else
            ReadFile(ar);

        cout << "������!" << endl;
        break;

    case 2:
        if ((ar.GetLength() == 0)&&(avlTr.GetLength() == 0))
        {
            Menu_1();
            cin >> a;
            FillActions(a);
            ReadFile(biTree);
        }
        else
        {
            if (ar.GetLength() == 0)
                ReadFile(biTree);
            else
                CopySeq(ar, biTree);
        }

        cout << "������!" << endl;
        break;

    case 3:
        if ((ar.GetLength() == 0)&&(biTree.GetLength() == 0))
        {
            Menu_1();
            cin >> a;
            FillActions(a);
            ReadFile(avlTr);
        }
        else
        {
            if (ar.GetLength() == 0)
                ReadFile(avlTr);
            else
                CopySeq(ar, avlTr);
        }

        cout << "������!" << endl;
        break;

    case 4:
        cout << "\n";
        ar.OutputToScreen();
        break;

    case 5:
        cout << "\n";
        biTree.OutputToScreen();
        cout << "\n";

    case 6:
        cout << "\n";
        avlTr.OutputToScreen();
        cout << "\n";
        break;

    case 7:
        Menu_2();
        do
        {
            do
            {
                cout << "\n������� ����� ������� �� ����: ";
                cin >> a;
            }
            while ((a < 0)||(a > 4));
            if (a != 4)
                SearchSeqActions(a, ar);
        }
        while (a != 4);
        MainMenu();
        break;

    case 8:
        cout << "\n������� �����, ������� ���� �����: ";
        cin >> data;

        start = clock();
        try
        {
            cout << "\n���������: " << biTree.Get(data) << endl;
        }
        catch (Except &e)
        {
            cout << e.Message() << endl;
        }

        timer = clock() - start;
        cout << "����� ������ (� ��): " << timer << endl;
        break;

    case 9:
        cout << "\n������� �����, ������� ���� �����: ";
        cin >> data;

        start = clock();
        try
        {
        cout << "\n���������: " << avlTr.Get(data) << endl;
        }
        catch (Except &e)
        {
            cout << e.Message() << endl;
        }

        timer = clock() - start;
        cout << "����� ������ (� ��): " << timer << endl;
        break;

    case 10:
        cout << "���������� ������: " << MainTest() << endl;
        break;

    case 0:
        /*�����*/
        break;
    }
    return;
}


int main()
{
    setlocale(0, "rus");

    SortedArray <int, int> arr;
    BinaryTree <int, int> tree_1;
    AVL_Tree <int, int> tree_2;

    MainMenu();
    int pos;
    do
    {
        do
        {
            cout << "\n������� ����� ������� �� ����: ";
            cin >> pos;
        }
        while ((pos < 0)||(pos > 10));

        Actions(pos, arr, tree_1, tree_2);
    }
    while (pos != 0);


    return 0;
}


/*
SortedArray <int, int> arr1;

cout << arr1.GetIsEmpty() << endl;
cout << arr1.GetLength() << endl;

arr1.Add(39);
cout << "+\n";
arr1.Add(-12);
cout << "+\n";
arr1.Add(38);
cout << "+\n";
arr1.Add(17);
cout << "+\n";
arr1.Add(-4);
cout << "+\n";
arr1.Add(-50);
cout << "+\n";
arr1.Add(28);
cout << "+\n";

cout << arr1.GetIsEmpty() << endl;
cout << arr1.GetLength() << endl;
cout << arr1.GetFirst() << endl;
cout << arr1.GetLast() << endl;
cout << arr1.Get(5) << endl;
cout << arr1.IndexOf(39) << endl;
cout << arr1.BinarySearch(39) << endl;
cout << arr1.GoldenRatio(39) << endl;
cout << arr1.Fibonacci(28, 4) << endl;

*/

/*
    BinaryTree <int, int> tr;

    cout << tr.GetIsEmpty() << endl;
    cout << tr.GetLength() << endl;

    tr.Add(28, 28);
    cout << "+\n";
    tr.Add(-12, -12);
    cout << "+\n";
    tr.Add(38, 38);
    cout << "+\n";
    tr.Add(17, 17);
    cout << "+\n";
    tr.Add(-4, -4);
    cout << "+\n";
    tr.Add(-50, -50);
    cout << "+\n";
    tr.Add(39, 39);
    cout << "+\n";

    cout << tr.GetIsEmpty() << endl;
    cout << tr.GetLength() << endl;
    tr.ShowTree();
    cout << "\n" << tr.GetFirst() << endl;
    cout << tr.GetLast() << endl;
    cout << tr.Get(-50) << endl;
    cout << tr.Get(28) << endl;
    cout << tr.Get(38) << endl;
    cout << tr.Get(-12) << endl;
    */
