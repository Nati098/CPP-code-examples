#ifndef TESTS_CPP
#define TESTS_CPP

#include "sorting.h"

using namespace std;

/*чтение из файла*/
void ReadFile (Sequence <int> &seq)
{
    ifstream file ("OriginSeq.txt");       //открываем файл для чтения

    if (!file.is_open())                   // если файл не открыт
        throw (Except(3));

    char *input;
    input = new char[10];
    while (! file.eof())                //пока файл не пустой
    {
        file.getline (input, 10);
        if (input != "")                //если не пустая строка, заносим в последовательность
        {                               //иначе, просто пропускаем строку
            int buff = atoi (input);
            seq.Append(buff);
        }
    }

    delete [] input;
    file.close();                              //закрываем файл
    cout << "Данные из файла считаны\n";
    return;
}

/*вывод на экран последовательности*/
void OutputTo (Sequence <int> *seq)
{
    for (int i=0; i <= ((*seq).getLength()-1); i++)
        cout << (*seq).Get(i) << "  ";
    cout << "\n";
    return;
}

/*проверка, что послеовательность отсортирована*/
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

/*проверка, что послеовательность отсортирована в обратном порядке*/
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
        data = -50 + rand() % 101;      //генерация чисел от -50 до 50
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

    cout << "\nCортировка 2500 элементов:\n" << endl;

    int timer_1, timer_2, timer_3;

    file.open("Test_results.txt");


    /*НЕОТСОРТИРОВАННЫЕ МАССИВЫ*/
    cout << "НЕОТСОРТИРОВАННЫЕ МАССИВЫ" << endl;
{
    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "Сортировка пузырьком успешно выполнена\nВремя выполения: " << timer_1 << endl;
    else
    {
        cout << "Сортировка пузырьком не выполнена\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "Шейкерная сортировка успешно выполнена\nВремя выполения: " << timer_2 << endl;
    else
    {
        cout << "Шейкерная сортировка не выполнена\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "Сортировка Шелла успешно выполнена\nВремя выполения: " << timer_3 << endl;
    else
    {
        cout << "Сортировка Шелла не выполненa\n";
        return false;
    }

    file << "НЕОТСОРТИРОВАННЫЕ МАССИВЫ\nПузырек: " << timer_1 << endl;
    file << "Шейкерная сортировка: " << timer_2 << endl;
    file << "Сортировка Шелла: " << timer_3 << endl;

    cout << "\nНЕОТСОРТИРОВАННЫЕ СПИСКИ" << endl;

    timer_1 = BubbleSort(l1);
    if (Is_Sorted(l1))
        cout << "Сортировка пузырьком успешно выполнена\nВремя выполения: " << timer_1 << endl;
    else
    {
        cout << "Сортировка пузырьком не выполнена\n";
        return false;
    }

    timer_2 = ShakeSort(l2);
    if (Is_Sorted(l2))
        cout << "Шейкерная сортировка успешно выполнена\nВремя выполения: " << timer_2 << endl;
    else
    {
        cout << "Шейкерная сортировка не выполнена\n";
        return false;
    }

    file << "НЕОТСОРТИРОВАННЫЕ СПИСКИ\nПузырек: " << timer_1 << endl;
    file << "Шейкерная сортировка: " << timer_2 << endl;
}


    /*МАССИВЫ В ОБРАТНОМ ПОРЯДКЕ*/
    cout << "\nМАССИВЫ В ОБРАТНОМ ПОРЯДКЕ" << endl;
{
    ar1.InverseSeq();
    if (Is_Sorted_Reverse(ar1))
        cout << "Последовательность ar1 отсортирована в обратном порядке" << endl;
    else
    {
        cout << "Последовательность ar1 не отсортирована в обратном порядке" << endl;
        return false;
    }

    ar2.InverseSeq();
    if (Is_Sorted_Reverse(ar2))
        cout << "Последовательность ar2 отсортирована в обратном порядке" << endl;
    else
    {
        cout << "Последовательность ar2 не отсортирована в обратном порядке" << endl;
        return false;
    }

    ar3.InverseSeq();
    if (Is_Sorted_Reverse(ar3))
        cout << "Последовательность ar3 отсортирована в обратном порядке" << endl;
    else
    {
        cout << "Последовательность ar3 не отсортирована в обратном порядке" << endl;
        return false;
    }

    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "Сортировка пузырьком успешно выполнена\nВремя выполения: " << timer_1 << endl;
    else
    {
        cout << "Сортировка пузырьком не выполнена\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "Шейкерная сортировка успешно выполнена\nВремя выполения: " << timer_2 << endl;
    else
    {
        cout << "Шейкерная сортировка не выполнена\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "Сортировка Шелла успешно выполнена\nВремя выполения: " << timer_3 << endl;
    else
    {
        cout << "Сортировка Шелла не выполненa\n";
        return false;
    }

    file << "МАССИВЫ В ОБРАТНОМ ПОРЯДКЕ\nПузырек: " << timer_1 << endl;
    file << "Шейкерная сортировка: " << timer_2 << endl;
    file << "Сортировка Шелла: " << timer_3 << endl;
}


    /*ОТСОРТИРОВАННЫЕ МАССИВЫ*/
    cout << "\nОТСОРТИРОВАННЫЕ МАССИВЫ" << endl;
{
    timer_1 = BubbleSort(ar1);
    if (Is_Sorted(ar1))
        cout << "Сортировка пузырьком успешно выполнена\nВремя выполения: " << timer_1 << endl;
    else
    {
        cout << "Сортировка пузырьком не выполнена\n";
        return false;
    }

    timer_2 = ShakeSort(ar2);
    if (Is_Sorted(ar2))
        cout << "Шейкерная сортировка успешно выполнена\nВремя выполения: " << timer_2 << endl;
    else
    {
        cout << "Шейкерная сортировка не выполнена\n";
        return false;
    }

    timer_3 = ShellSort(ar3);
    if (Is_Sorted(ar3))
        cout << "Сортировка Шелла успешно выполнена\nВремя выполения: " << timer_3 << endl;
    else
    {
        cout << "Сортировка Шелла не выполненa\n";
        return false;
    }

    file << "ОТСОРТИРОВАННЫЕ МАССИВЫ\nПузырек: " << timer_1 << endl;
    file << "Шейкерная сортировка: " << timer_2 << endl;
    file << "Сортировка Шелла: " << timer_3 << endl;
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
