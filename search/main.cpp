#include <locale.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "tests.cpp"
//#include "C:\Bill\z\Programms\MyLib\sortedsequence.cpp"


using namespace std;

/*чтение из файла*/
void ReadFile (SortedSequence <int, int> &seq)
{
    ifstream file ("OriginSeq.txt");       //открываем файл для чтения

    if (!file.is_open())                   // если файл не открыт
        throw (Except(3));

    char *input;
    input = new char[10];
    while (! file.eof())                //пока файл не пустой
    {
        file.getline (input, 10);       //считываем строку
        if (input == '\0')
              file.ignore();                  //чтобы избежать записи пустой строки в след. переменную
        else
        {
            int buff = atoi (input);
            seq.Add(buff);
        }
    }

    delete [] input;
    file.close();                              //закрываем файл
    return;
}

/*проверка на то, что введено число*/
bool Is_Digit (char *str)
{
    int i=0;
    int flag=1;
    if (str[0] == '-')   //если первая буква - "-", то всё хорошо
        i++;
    while (str[i] != '\0')      //пока не дойдем до конца слова
    {
        if (!isdigit(str[i]))   //если данная буква - не цифра,
            flag = 0;           //то flag = 0

        if (flag == 0)
            return false;       //и мы выйдем из функции

        i++;                    //иначе, flag = 1 и мысмотрим след.букву слова
    }
    return true;
}

/*главное меню*/
void MainMenu()
{
    cout << "\nВыберите пункт:\n";
    cout << "1)  заполнение последовательности\n";
    cout << "2)  заполнение бинарного дерева\n";
    cout << "3)  заполнение АВЛ-дерева\n";
    cout << "4)  вывод последовательности\n";
    cout << "5)  вывод бинарного дерева\n";
    cout << "6)  вывод АВЛ-дерева\n";
    cout << "7)  бинарный поиск\n";
    cout << "8)  поиск по бинарному дереву\n";
    cout << "9)  поиск по АВЛ-дереву\n";
    cout << "10) общий тест\n";
    cout << "0) выход\n";
}

void Menu_1()
{
    cout << "\nВыберите пункт:\n";
    cout << "1) заполнение вручную\n";
    cout << "2) генерация случайных чисел\n";
}

void Menu_2()
{
    cout << "\nВыберите пункт:\n";
    cout << "1) стандартный\n";
    cout << "2) методом 'золотого сечения'\n";
    cout << "3) методом чисел Фибоначчи\n";
    cout << "4) назад в главное меню\n";
}

/*выполняемые действия из Menu_1*/
void FillActions(int b)
{
    ofstream file;
    file.open("OriginSeq.txt");         //открываем файл для записи

    if (!file)                          // если файл нельзя открыть
        throw (Except(3));              //выкидываем исключение

    int data, num;
    char *info;
    info = new char[10];
    switch (b)
    {
    case 1:                             //ручной ввод
        num = 0;
        cout << "\nВведите числа:\n(для выхода наберите 'end')\n";


        while (stricmp(info, "end") != 0)
        {
            cin >> info;
            if (stricmp(info, "end") != 0)
            {
                if (!Is_Digit(info))
                    cout << "Неправильно набрано число\n";
                else
                {
                    data = atoi(info);
                    file << data << endl;
                    num++;
                }
            }
        }
        break;
    case 2:                     //генерация случайных чисел
        srand(time(0));
        cout << "\nВведите число элементов: ";
        cin >> num;
        for (int i=0; i < num-1; i++)
        {
            data = -50 + rand() % 101;      //генерация чисел от -50 до 50
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

/*выполняемые действия из Menu_2*/
void SearchSeqActions(int b, SortedArray <int, int> &ar)
{
    int data;
    cout << "\nВведите число, которое надо найти: ";
    cin >> data;

    double start = clock();                 //часы
    switch (b)
    {
    case 1:
        cout << "\nРезультат поиска: " << ar.BinarySearch(data) << endl;
        break;
    case 2:
        cout << "\nРезультат поиска: " << ar.GoldenRatio(data) << endl;
        break;
    case 3:
        int n;              //кол-во итераций
        cout << "Введите число итераций (желательно, не больше 15): ";
        cin >> n;
        cout << "\nРезультат поиска: " << ar.Fibonacci(data, n) << endl;
        break;
    }
    double timer = clock() - start;
    cout << "Время поиска (в мс): " << timer << endl;
    return;
}

/*выподняемые действия из MainMenu*/
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

        cout << "Готово!" << endl;
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

        cout << "Готово!" << endl;
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

        cout << "Готово!" << endl;
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
                cout << "\nВведите номер позиции из меню: ";
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
        cout << "\nВведите число, которое надо найти: ";
        cin >> data;

        start = clock();
        try
        {
            cout << "\nРезультат: " << biTree.Get(data) << endl;
        }
        catch (Except &e)
        {
            cout << e.Message() << endl;
        }

        timer = clock() - start;
        cout << "Время поиска (в мс): " << timer << endl;
        break;

    case 9:
        cout << "\nВведите число, которое надо найти: ";
        cin >> data;

        start = clock();
        try
        {
        cout << "\nРезультат: " << avlTr.Get(data) << endl;
        }
        catch (Except &e)
        {
            cout << e.Message() << endl;
        }

        timer = clock() - start;
        cout << "Время поиска (в мс): " << timer << endl;
        break;

    case 10:
        cout << "Результаты тестов: " << MainTest() << endl;
        break;

    case 0:
        /*выход*/
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
            cout << "\nВведите номер позиции из меню: ";
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
