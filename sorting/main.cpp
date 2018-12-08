#include <locale.h>
#include "sorting.h"
#include "tests.cpp"

using namespace std;

/*чтение из файла*/
void ReadF (Sequence <int> &seq)
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
            seq.Append(buff);
        }
    }

    delete [] input;
    file.close();                              //закрываем файл
    return;
}

/*вывод на экран последовательности*/
void OutputToScr (Sequence <int> *seq)
{
    for (int i=0; i <= (seq->getLength()-1); i++)
        cout << seq->Get(i) << "  ";
    cout << "\n";
    return;
}

/*главное меню*/
void MainMenu()
{
    cout << "Выберите способ заполнения последовательности:\n";
    cout << "1) заполнение вручную\n";
    cout << "2) генерация последовательности\n";
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

//копирование из одной посл-сти в другую
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

/*выполняемые действия из меню*/
void Actions(int b, ArraySequence <int> *ar, ListSequence <int> *l)
{
    ofstream file;
    file.open("OriginSeq.txt");         //открываем файл для записи

    if (!file)                          // если файл нельзя открыть
        throw (Except(3));              //выкидываем исключение

    int data, num;
    char *info;
    info = new char[10];               //= (char*)calloc(12, sizeof(char));
    switch (b)
    {
    case 1:
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
    case 2:
        srand(time(0));
        cout << "Введите число элементов: ";
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

    cout << "РЕЗУЛЬТАТЫ ТЕСТОВ: " << MainTest() << endl;

  /*  MainMenu();

    int pos;
    do
    {
        cout << "Введите номер позиции из меню: ";
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
    cout << "Хотите вывести исходную последовательность на экран?\n0)нет\n1)да\n" << endl;
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

    cout << "\nСОРТИРОВКА МАССИВОВ:\n" << endl;

    t1 = BubbleSort(arr[0]);
    cout << "Пузырёк          - " << t1 << "мc\n";
    result.open ("TimeResults.txt");
    result << "ВРЕМЯ СОРТИРОВКИ ПУЗЫРЬКОМ: " << t1 << endl;

    t2 = ShakeSort(arr[1]);
    cout << "Шейкерная        - " << t2 << "мc\n";
    result << "ВРЕМЯ ШЕЙКЕРНОЙ СОРТИРОВКИ: " << t2 << endl;

    t3 = ShellSort(arr[2]);
    cout << "Сортировка Шелла - " << t3 << "мc\n";
    result << "ВРЕМЯ СОРТИРОВКИ ШЕЛЛА: " << t3 << endl;

    //вывод исходя из результатов показаний времени для массивов
    cout << "\nВЫВОД:" << endl;
    if ((t1 == 0) || (t2 == 0))
    {
        cout << "Слишком мало элементов в последовательности" << endl;
    }
    else
    {
        Compare_Sort_In(t1, t2, t3);                        //сравнение сортировок для массива
    }

    //сортировка для списков (если в послеовательности не более 3000 элементов)
    if (arr[1].getLength() <= 3000)
    {
        double t4, t5, t6;

        cout << "\n\nСОРТИРОВКА СПИСКОВ:\n" << endl;

        t4 = BubbleSort(list[0]);
        cout << "Пузырёк   - " << t4 << "мc\n";
        result << "ВРЕМЯ СОРТИРОВКИ ПУЗЫРЬКОМ: " << t4 << endl;

        t5 = ShakeSort(list[1]);
        cout << "Шейкерная - " << t5 << "мc\n";
        result << "ВРЕМЯ ШЕЙКЕРНОЙ СОРТИРОВКИ: " << t5 << endl;

        t6 = ShellSort(list[2]);
        cout << "Сортировка Шелла - " << t6 << "мc\n";
        result << "ВРЕМЯ СОРТИРОВКИ ШЕЛЛА: " << t6 << endl;

        //вывод исходя из резльтатов для списков и общий вывод
        cout << "\nВЫВОД:" << endl;
        if ((t1 == 0) || (t2 == 0))
        {
            cout << "Слишком мало элементов в последовательности" << endl;
        }
        else
        {
            Compare_Sort_In(t4, t5, t6);                    //сравнение сортировок для списков

            cout << "\n\nСРАВНЕНИЕ ПУЗЫРЬКА:" << endl;
            Compare_Sort_Out(t1, t4);                       //сравнение Пузырька
            cout << "\nСРАВНЕНИЕ ШЕЙКЕРНОЙ СОРТИРОВКИ:" << endl;
            Compare_Sort_Out(t2, t5);                       //сравнение Шейкерной сортировки
            cout << "\nСРАВНЕНИЕ СОРТИРОВКИ ШЕЛЛА:" << endl;
            Compare_Sort_Out(t3, t6);                       //сравнение Шейкерной сортировки
        }
    }
    result.close();

    cout << "\n\nВременные показатели записаны в файл!\n" << endl;

    cout << "Хотите отсортированную последовательность на экран?\n0)нет\n1)да\n" << endl;
    do
    {
        cout << "Введите номер позиции из меню: ";
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
        data = -50 + rand() % 101;      //генерация чисел от -50 до 50
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
