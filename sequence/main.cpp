#include <iostream>
#include <locale.h>
#include "tests.h"
#include "classsequence.cpp"

using namespace std;



/*���� �������� ��� �������������������*/
void menu()
{
    cout << "��������������! ������ ��������� ���������� � ����!" << endl;
    cout << "1)�������� ������� � ������" << endl;
    cout << "2)�������� ������� �� �������" << endl;
    cout << "3)�������� ������� � �����" << endl;
    cout << "4)������ ����� ���������" << endl;
    cout << "5)������ ������� ��������" << endl;
    cout << "6)������ �������� �� �������" << endl;
    cout << "7)������ ���������� ��������" << endl;
    cout << "8)���������������������" << endl;
    cout << "9)�������� �� �������" << endl;
    cout << "10)�����" << endl;
}

/*���� ��� �������*/
void actmenu1 (arraySequence <int> &Arr, int b)
{
    switch (b)
    {
    int item, index;
    case 1:
        cout << "������� �����:" << endl;
        cin >> item;
        Arr.Prepend(item);
        cout << "\n���������\n"<< endl;
        break;
    case 2:
        cout << "������� �����:" << endl;
        cin >> item;
        cout << "������� ������:" << endl;
        cin >> index;
        Arr.InsertAt(index, item);
        cout << "\n���������\n"<< endl;
        break;
    case 3:
        cout << "������� �����:" << endl;
        cin >> item;
        Arr.Append(item);
        cout << "\n���������\n"<< endl;
        break;
    case 4:
        cout << "\n����� ���������: " << Arr.getLength() << "\n" << endl;
        break;
    case 5:
        cout << "\n������ �������: " << Arr.GetFirst() << "\n"  << endl;
        break;
    case 6:
        cout << "������� ������:" << endl;
        cin >> index;
        cout << "\n������� "<< index << ": " << Arr.Get(index) << "\n" << endl;
        break;
    case 7:
        cout << "\n��������� �������: " << Arr.GetLast() << "\n" << endl;
        break;
    case 8:
        cout << "������� ������ ������� ��������:" << endl;
        cin >> item;
        cout << "������� ������ ���������� ��������:" << endl;
        cin >> index;
        Arr.GetSubsequence(item, index);
        cout << "\n������� ���������������������\n" << endl;
        break;
    case 9:
        cout << "\n������ ����? (�� - 1, ��� - 0): " << Arr.getIsEmpty() << "\n" << endl;
        break;
    }
}

/*���� ��� ������*/
void actmenu2 (listSequence <int> &H, int b)
{
    switch (b)
    {
    int item, index;
    case 1:
        cout << "������� �����:" << endl;
        cin >> item;
        H.Prepend(item);
        cout << "\n���������\n"<< endl;
        break;
    case 2:
        cout << "������� �����:" << endl;
        cin >> item;
        cout << "������� ������:" << endl;
        cin >> index;
        H.InsertAt(index, item);
        cout << "\n���������\n"<< endl;
        break;
    case 3:
        cout << "������� �����:" << endl;
        cin >> item;
        H.Append(item);
        cout << "\n���������\n"<< endl;
        break;
    case 4:
        cout << "\n����� ���������: " << H.getLength() << "\n" << endl;
        break;
    case 5:
        cout << "\n������ �������: " << H.GetFirst() << "\n"  << endl;
        break;
    case 6:
        cout << "������� ������:" << endl;
        cin >> index;
        cout << "\n������� "<< index << ": " << H.Get(index) << "\n" << endl;
        break;
    case 7:
        cout << "\n��������� �������: " << H.GetLast() << "\n" << endl;
        break;
    case 8:
        cout << "������� ������ ������� ��������:" << endl;
        cin >> item;
        cout << "������� ������ ���������� ��������:" << endl;
        cin >> index;
        H.GetSubsequence(item, index);        
        cout << "\n������� ���������������������\n" << endl;
        break;
    case 9:
        H.getIsEmpty();
        break;
    }
}

/*��� ������ ����� ��� �������*/
void arrTest()
{
    arraySequence <int> arr;
    cout << "���������: " << MainTest(arr) << endl;
    cout << "���������: " << ArSubsequence(arr) << endl;
    return;
}

/*��� ������ ����� ��� ������*/
void listTest()
{
    listSequence <int> list;
    cout << "���������: " << MainTest(list) << endl;
    cout << "���������: " << liSubsequence(list) << endl;
    return;
}


int main()
{
    setlocale(0, "rus");

    //arrTest();
    //listTest();

    int ex = 0;                                 //���������� ��� ������ �� ���������: 0-�� ��������, 1-����� �� ���������

    while (ex != 1)                             //���� ex != 1 �� ��������� �� ������
    {
        cout << "��� �� ������ �������?" << endl;
        cout << "1) �������� � ��������" << endl;
        cout << "2) �������� �� �������" << endl;
        cout << "3) ����� �� ���������" << endl;

        int a;                                  //����� ������ �� �������� ����
        do
        {
            cout << "�����:";
            cin >> a;
            cout << "\n";
        }
        while ((a < 1)||(a > 3));               //���� � �� ����� 1..3 ������ �������
        switch (a)
        {
        case 1:
        {
            arraySequence <int> Arr;
            int b = 0;                          //����� ������ �� menu
            while (b < 10)
            {
                menu();
                do
                {
                    cout << "�������� �����:" << endl;
                    cin >> b;
                }
                while ((b < 1)||(b > 10));      //���� b �� �� 1..10, ������ �������
                actmenu1 (Arr, b);
            }
            break;
        }
        case 2:
        {
            listSequence <int> H;
            int b = 0;                          //����� ������ �� menu
            while (b < 10)
            {
                menu();
                do
                {
                    cout << "�������� �����:" << endl;
                    cin >> b;
                }
                while ((b < 1)||(b > 10));      //���� b �� �� 1..10, ������ �������
                actmenu2 (H, b);
            }
            break;
        }
        default:
            ex = 1;
            break;
        }

        cout << "������ ����� �� ���������? (1 - ��, 0 - ���)" << endl;
        cin >> ex;
     }
    return 0;
}
