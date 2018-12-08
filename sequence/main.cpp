#include <iostream>
#include <locale.h>
#include "tests.h"
#include "classsequence.cpp"

using namespace std;



/*меню действий над последовательностью*/
void menu()
{
    cout << "ПРЕДУПРЕЖДЕНИЕ! Отсчет элементов начинается с нуля!" << endl;
    cout << "1)Добавить элемент в начало" << endl;
    cout << "2)Добавить элемент по индексу" << endl;
    cout << "3)Добавить элемент в конец" << endl;
    cout << "4)Узнать число элементов" << endl;
    cout << "5)Данные первого элемента" << endl;
    cout << "6)Данные элемента по индексу" << endl;
    cout << "7)Данные последнего элемента" << endl;
    cout << "8)Подпоследовательность" << endl;
    cout << "9)Проверка на пустоту" << endl;
    cout << "10)Выйти" << endl;
}

/*меню для массива*/
void actmenu1 (arraySequence <int> &Arr, int b)
{
    switch (b)
    {
    int item, index;
    case 1:
        cout << "Введите число:" << endl;
        cin >> item;
        Arr.Prepend(item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 2:
        cout << "Введите число:" << endl;
        cin >> item;
        cout << "Введите индекс:" << endl;
        cin >> index;
        Arr.InsertAt(index, item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 3:
        cout << "Введите число:" << endl;
        cin >> item;
        Arr.Append(item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 4:
        cout << "\nЧисло элементов: " << Arr.getLength() << "\n" << endl;
        break;
    case 5:
        cout << "\nПервый элемент: " << Arr.GetFirst() << "\n"  << endl;
        break;
    case 6:
        cout << "Введите индекс:" << endl;
        cin >> index;
        cout << "\nЭлемент "<< index << ": " << Arr.Get(index) << "\n" << endl;
        break;
    case 7:
        cout << "\nПоследний элемент: " << Arr.GetLast() << "\n" << endl;
        break;
    case 8:
        cout << "Введите индекс первого элемента:" << endl;
        cin >> item;
        cout << "Введите индекс последнего элемента:" << endl;
        cin >> index;
        Arr.GetSubsequence(item, index);
        cout << "\nСоздана подпоследовательность\n" << endl;
        break;
    case 9:
        cout << "\nСписок пуст? (да - 1, нет - 0): " << Arr.getIsEmpty() << "\n" << endl;
        break;
    }
}

/*меню для списка*/
void actmenu2 (listSequence <int> &H, int b)
{
    switch (b)
    {
    int item, index;
    case 1:
        cout << "Введите число:" << endl;
        cin >> item;
        H.Prepend(item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 2:
        cout << "Введите число:" << endl;
        cin >> item;
        cout << "Введите индекс:" << endl;
        cin >> index;
        H.InsertAt(index, item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 3:
        cout << "Введите число:" << endl;
        cin >> item;
        H.Append(item);
        cout << "\nДобавлено\n"<< endl;
        break;
    case 4:
        cout << "\nЧисло элементов: " << H.getLength() << "\n" << endl;
        break;
    case 5:
        cout << "\nПервый элемент: " << H.GetFirst() << "\n"  << endl;
        break;
    case 6:
        cout << "Введите индекс:" << endl;
        cin >> index;
        cout << "\nЭлемент "<< index << ": " << H.Get(index) << "\n" << endl;
        break;
    case 7:
        cout << "\nПоследний элемент: " << H.GetLast() << "\n" << endl;
        break;
    case 8:
        cout << "Введите индекс первого элемента:" << endl;
        cin >> item;
        cout << "Введите индекс последнего элемента:" << endl;
        cin >> index;
        H.GetSubsequence(item, index);        
        cout << "\nСоздана подпоследовательность\n" << endl;
        break;
    case 9:
        H.getIsEmpty();
        break;
    }
}

/*для вызова теста для массива*/
void arrTest()
{
    arraySequence <int> arr;
    cout << "Результат: " << MainTest(arr) << endl;
    cout << "Результат: " << ArSubsequence(arr) << endl;
    return;
}

/*для вызова теста для списка*/
void listTest()
{
    listSequence <int> list;
    cout << "Результат: " << MainTest(list) << endl;
    cout << "Результат: " << liSubsequence(list) << endl;
    return;
}


int main()
{
    setlocale(0, "rus");

    //arrTest();
    //listTest();

    int ex = 0;                                 //переменная для выхода из программы: 0-не выходить, 1-выйти из программы

    while (ex != 1)                             //пока ex != 1 из программы не выйдем
    {
        cout << "Что вы хотите сделать?" << endl;
        cout << "1) работать с массивом" << endl;
        cout << "2) работать со списком" << endl;
        cout << "3) выйти из программы" << endl;

        int a;                                  //выбор пункта из главного меню
        do
        {
            cout << "Пункт:";
            cin >> a;
            cout << "\n";
        }
        while ((a < 1)||(a > 3));               //пока а не равно 1..3 индекс неверен
        switch (a)
        {
        case 1:
        {
            arraySequence <int> Arr;
            int b = 0;                          //выбор пункта из menu
            while (b < 10)
            {
                menu();
                do
                {
                    cout << "Выберите пункт:" << endl;
                    cin >> b;
                }
                while ((b < 1)||(b > 10));      //пока b не из 1..10, индекс неверен
                actmenu1 (Arr, b);
            }
            break;
        }
        case 2:
        {
            listSequence <int> H;
            int b = 0;                          //выбор пункта из menu
            while (b < 10)
            {
                menu();
                do
                {
                    cout << "Выберите пункт:" << endl;
                    cin >> b;
                }
                while ((b < 1)||(b > 10));      //пока b не из 1..10, индекс неверен
                actmenu2 (H, b);
            }
            break;
        }
        default:
            ex = 1;
            break;
        }

        cout << "Хотите выйти из программы? (1 - да, 0 - нет)" << endl;
        cin >> ex;
     }
    return 0;
}
