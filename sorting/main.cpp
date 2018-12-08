#include <locale.h>
#include "sorting.h"
#include "tests.cpp"

using namespace std;

/*������ �� �����*/
void ReadF (Sequence <int> &seq)
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
            seq.Append(buff);
        }
    }

    delete [] input;
    file.close();                              //��������� ����
    return;
}

/*����� �� ����� ������������������*/
void OutputToScr (Sequence <int> *seq)
{
    for (int i=0; i <= (seq->getLength()-1); i++)
        cout << seq->Get(i) << "  ";
    cout << "\n";
    return;
}

/*������� ����*/
void MainMenu()
{
    cout << "�������� ������ ���������� ������������������:\n";
    cout << "1) ���������� �������\n";
    cout << "2) ��������� ������������������\n";
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

//����������� �� ����� ����-��� � ������
void CopySeq (Sequence <int> &orig, Sequence <int> &copy)
{
    int buff;
    for (int i=0; i < orig.getLength(); i++)
    {
        buff = orig.Get(i);
        copy.Append(buff);
    }
    return;
}

/*����������� �������� �� ����*/
void Actions(int b, ArraySequence <int> *ar, ListSequence <int> *l)
{
    ofstream file;
    file.open("OriginSeq.txt");         //��������� ���� ��� ������

    if (!file)                          // ���� ���� ������ �������
        throw (Except(3));              //���������� ����������

    int data, num;
    char *info;
    info = new char[10];               //= (char*)calloc(12, sizeof(char));
    switch (b)
    {
    case 1:
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
    case 2:
        srand(time(0));
        cout << "������� ����� ���������: ";
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

    for (int i=0; i < 3; i++)
        ReadF(ar[i]);

    if (num <= 3000)
    {
        for (int i=0; i < 3; i++)
            ReadF(l[i]);
    }
}


int main()
{
    setlocale(0, "rus");

    cout << "���������� ������: " << MainTest() << endl;

  /*  MainMenu();

    int pos;
    do
    {
        cout << "������� ����� ������� �� ����: ";
        cin >> pos;
    }
    while ((pos < 0)||(pos > 2));

    ArraySequence <int> arr[3];
    ListSequence <int> list[3];
    try
    {
    Actions (pos, arr, list);
}
catch (Except &e)
{
    cout << e.Message();
}
    int ans;
    cout << "������ ������� �������� ������������������ �� �����?\n0)���\n1)��\n" << endl;
    cin >> ans;
    if ((ans != 1) && (ans != 0))
        throw (Except(1));
    else
    {
        if (ans == 1)
            OutputToScr(&arr[0]);
    }

    ofstream result;
    double t1, t2, t3;

    cout << "\n���������� ��������:\n" << endl;

    t1 = BubbleSort(arr[0]);
    cout << "������          - " << t1 << "�c\n";
    result.open ("TimeResults.txt");
    result << "����� ���������� ���������: " << t1 << endl;

    t2 = ShakeSort(arr[1]);
    cout << "���������        - " << t2 << "�c\n";
    result << "����� ��������� ����������: " << t2 << endl;

    t3 = ShellSort(arr[2]);
    cout << "���������� ����� - " << t3 << "�c\n";
    result << "����� ���������� �����: " << t3 << endl;

    //����� ������ �� ����������� ��������� ������� ��� ��������
    cout << "\n�����:" << endl;
    if ((t1 == 0) || (t2 == 0))
    {
        cout << "������� ���� ��������� � ������������������" << endl;
    }
    else
    {
        Compare_Sort_In(t1, t2, t3);                        //��������� ���������� ��� �������
    }

    //���������� ��� ������� (���� � ����������������� �� ����� 3000 ���������)
    if (arr[1].getLength() <= 3000)
    {
        double t4, t5, t6;

        cout << "\n\n���������� �������:\n" << endl;

        t4 = BubbleSort(list[0]);
        cout << "������   - " << t4 << "�c\n";
        result << "����� ���������� ���������: " << t4 << endl;

        t5 = ShakeSort(list[1]);
        cout << "��������� - " << t5 << "�c\n";
        result << "����� ��������� ����������: " << t5 << endl;

        t6 = ShellSort(list[2]);
        cout << "���������� ����� - " << t6 << "�c\n";
        result << "����� ���������� �����: " << t6 << endl;

        //����� ������ �� ���������� ��� ������� � ����� �����
        cout << "\n�����:" << endl;
        if ((t1 == 0) || (t2 == 0))
        {
            cout << "������� ���� ��������� � ������������������" << endl;
        }
        else
        {
            Compare_Sort_In(t4, t5, t6);                    //��������� ���������� ��� �������

            cout << "\n\n��������� ��������:" << endl;
            Compare_Sort_Out(t1, t4);                       //��������� ��������
            cout << "\n��������� ��������� ����������:" << endl;
            Compare_Sort_Out(t2, t5);                       //��������� ��������� ����������
            cout << "\n��������� ���������� �����:" << endl;
            Compare_Sort_Out(t3, t6);                       //��������� ��������� ����������
        }
    }
    result.close();

    cout << "\n\n��������� ���������� �������� � ����!\n" << endl;

    cout << "������ ��������������� ������������������ �� �����?\n0)���\n1)��\n" << endl;
    do
    {
        cout << "������� ����� ������� �� ����: ";
        cin >> ans;
    }
    while ((ans != 1) && (ans != 0));

    if (ans == 1)
        OutputToScr(&arr[0]);
*/
    return 0;
}


/*


    srand(time(0));
    ListSequence <int> list3;
    int data;
    double timer;
    for (int i=1; i < 50; i++)
    {
        data = -50 + rand() % 101;      //��������� ����� �� -50 �� 50
        list3.Append(data);
    }
    OutputToScr (&list3);
    cout << list3.Running() << endl;
    timer = ShellSort(list3);
    OutputToScr (&list3);





   // CopySeq(ar1, ar2);
    //CopySeq(ar1, ar3);


        //CopySeq(ar1, l1);
        //CopySeq(ar1, l2);
        //CopySeq(ar1, l3);

    */
