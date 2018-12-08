#ifndef CLASSSEQUENCE_H
#define CLASSSEQUENCE_H
#include <iostream>
#include <cstdlib>
#include "exceptions.cpp"

using namespace std;


template <typename TElem> class listNode
{
public:
    listNode <TElem> *prev;
    TElem body;
    listNode <TElem> *next;
};

template <typename TElem> class Sequence
{
public:
    virtual int getLength() = 0;
    virtual int getIsEmpty() = 0;
    virtual TElem Get(int index) = 0;
    virtual TElem GetFirst() = 0;
    virtual TElem GetLast() = 0;
    virtual void Append (TElem item) = 0;
    virtual void Prepend (TElem item) = 0;
    virtual void InsertAt (int index, TElem item) = 0;
};


template <typename TElem> class arraySequence: public Sequence <TElem>
{
private:
    TElem **arSeq;
    int arLength;
    int isEmpty;

public:

    /*конструктор*/
    arraySequence()
    {
        arSeq = new TElem*[100];
        if (arSeq==NULL) return;          //если выделение памяти не выполнилось, завершить программу

        arLength = 0;
        isEmpty = 1;                        //1-последовательность пустая, 0-не пустая
    }

    /*проверка того, что последовательность пустая*/
    int getIsEmpty()
    {
        return (isEmpty);
    }

    /*число элементов*/
    int getLength()
    {
        return (arLength);
    }

    /*получить данные ячейки по индексу*/
    TElem Get(int index)
    {
        if ((index >= 0)&&(index < arLength))       //если индекс в [0..длина массива], все хорошо
        {
            if (getIsEmpty() == 0)                  //если последовательность не пустая, то возвратим элемент с index
                return (*arSeq[index]);
        }
        else
            throw (IndexBeyonds());
    }

    /*получить первый элемент последовательности*/
    TElem GetFirst()
    {
        if (getIsEmpty() == 0)
            return (*(arSeq[0]));
        else
        {
            return 0;
        }
    }

    /*получить последний элемент*/
    TElem GetLast()
    {
        if (getIsEmpty() == 0)
            return (*(arSeq[arLength-1]));      //если последовательность не пустая, то вернем значение последней ячейки
        else
            return 0;
    }

    /*получение подпоследовательности*/
    arraySequence <TElem> GetSubsequence(int startIndex, int endIndex)
    {
        arraySequence <TElem> subSec;

        if ((startIndex >= 0)&&(endIndex >= 0))     //если индексы положительные
        {
            if ((endIndex < arLength)&&(startIndex <= endIndex))  //и если endIndex & startIndex меньше...
            {
                int num=startIndex;

                while (num != (endIndex+1))         //создадим подпоследовательность [startIndex..endIndex]
                {
                    subSec.Append (*arSeq[num]);
                    num++;
                }
            }
            else
                throw (IndexBeyonds());
        }
        else
            throw (IndexBeyonds());

        return (subSec);
    }

    /*добавление элемента в конец*/
    void Append (TElem item)
    {
        if (getIsEmpty() == 1 )         //если последовательность была пустая
        {
            isEmpty = 0;                //то теперь последовательность не пустая
        }

        TElem *cell = new TElem;
        *cell = item;

        arSeq[arLength] = cell;
        arLength++;
        return;
    }

    /*добавление элемента в начало*/
    void Prepend (TElem item)
    {
        TElem *cell = new TElem;
        *cell = item;

        if (getIsEmpty() == 1 )         //если последовательность была пустая
        {
            arSeq[0] = cell;
            isEmpty = 0;                //то теперь последовательность не пустая
        }
        else
        {
            int i=0;
            int *buff1;                 //2 buff для хранения указателей на инфу
            int *buff2;

            buff1 = arSeq[0];
            while (i < (arLength-1))
            {
                buff2 = arSeq[i+1];
                arSeq[i+1] = buff1;
                buff1 = buff2;
                i++;
            }
            arSeq[arLength] = buff1;
            arSeq[0] = cell;
        }
        arLength++;
        return;
    }

    /*вставить элемент в позицию index*/
    void InsertAt (int index, TElem item)
    {
        TElem *cell = new TElem;
        *cell = item;

        if ((index >= 0)&&(index < arLength))
        {
            if (getIsEmpty() == 1 )
            {
                arSeq[0] = cell;
                isEmpty = 0;
            }
            else
            {
                int i = index;
                int *buff1;
                int *buff2;
                buff1 = arSeq[i];
                arSeq[i] = cell;

                while (i < (arLength-1))
                {
                    buff2 = arSeq[i+1];
                    arSeq[i+1] = buff1;
                    buff1 = buff2;
                    i++;
                }
                arSeq[arLength] = buff1;
            }
        arLength++;
        }
        else
            throw (IndexBeyonds());
        return;
    }

    //деструктор
    ~arraySequence()
    {
       /* for (int i=0; i < arLength; i++)
        {
            delete arSeq[i];
        }
        delete [] arSeq;*/



        cout << "Я сделяль :)\n";
    }

};

template <typename TElem> class listSequence: public Sequence <TElem>
{
private:
    listNode <TElem> *head;
    int liLength;           //длина последовательности
    int isEmpty;            //последовательность пустая? 0-нет, 1-да

public:

    /*конструктор*/
    listSequence()
    {
        head = NULL;

        liLength = 0;
        isEmpty = 1;        //последовательность пустая
    }

    /*признак того, что последовательность пустая*/
    int getIsEmpty()
    {
        return (isEmpty);
    }

    /*количество элементов*/
    int getLength()
    {
        return (liLength);        
    }

    /*получить данные ячейки по индексу*/
    TElem Get(int index)
    {
        if ((index >= 0)&&(index < getLength()))
        {
            if (getIsEmpty() == 0)
            {
                listNode <TElem> *cell;
                int pos=0;

                cell = head;
                while (pos != index)
                {
                    cell = cell->next;
                    pos++;
                }
                return (cell->body);
            }
           else                                 //если вызвали Get для пустой последовательности
                throw (EmptySeq());
        }
        else
            throw (IndexBeyonds());
    }

    /*получить первый элемент последовательности*/
    TElem GetFirst()
    {
        if (getIsEmpty() == 1)
            throw (EmptySeq());
        else
        {
            return (head->body);
        }
    }

    /*получить последний элемент*/
    TElem GetLast()
    {
        if (getIsEmpty() == 1)
            throw (EmptySeq());
        else
        {
            listNode <TElem> *cell;
            cell=head;
            while (cell->next != NULL)
                cell = cell->next;
            return (cell->body);
        }
    }

    /*получение подпоследовательности*/
    listSequence <TElem> GetSubsequence(int startIndex, int endIndex)
    {
        listSequence <TElem> subSec;
        if ((startIndex >= 0)&&(endIndex >= 0))
        {
            if (endIndex < getLength())
            {
                int num=0;
                listNode <TElem> *cell;

                cell = head;
                while (num != startIndex)
                {
                    cell = cell->next;
                    num++;
                }

                while (num != (endIndex+1))
                {
                    subSec.Append(cell->body);
                    cell = cell->next;
                    num++;
                }      
            }
            else
                throw (IndexBeyonds());
        }
        else
            throw (IndexBeyonds());

        return (subSec);
    }   

    /*добавление элемента в конец*/
    void Append (TElem item)
    {
        listNode <TElem> *newCell = new (listNode <TElem>);
        newCell->body = item;
        newCell->prev = NULL;
        newCell->next = NULL;

        if (getIsEmpty() == 1 )
        {
            head=newCell;
            isEmpty = 0;         
        }
        else
        {
            listNode <TElem> *cell;
            cell = head;

            while (cell->next != NULL)
                cell = cell->next;
            cell->next = newCell;
            newCell->prev = cell;
        }

        liLength++;
        return;
    }

    /*добавление элемента в начало*/
    void Prepend (TElem item)
    {
        listNode <TElem> *newCell = new (listNode <TElem>);
        newCell->body = item;
        newCell->prev = NULL;
        newCell->next = NULL;

        if (getIsEmpty() == 1 )
        {
            head=newCell;
            isEmpty = 0;
        }
        else
        {
            head->prev = newCell;
            newCell->next = head;
            head = head->prev;
        }

        liLength++;
        return;
    }

    /*вставить элемент в позицию index*/
    void InsertAt (int index, TElem item)
    {
        if ((index >= 0)&&(index < getLength()))
        {
            listNode <TElem> *newCell = new (listNode <TElem>);
            newCell->body = item;
            newCell->prev = NULL;
            newCell->next = NULL;

            if (getIsEmpty() == 1 )
            {
                head = newCell;
                isEmpty = 0;
            }
            else
            {
                listNode <TElem> *cell;
                int num = 0;

                cell = head;
                while (num != index)
                    cell = cell->next;

                newCell->prev = cell->prev;
                cell->prev->next = newCell;
                newCell->next = cell;
                cell->prev = newCell;
            }

            liLength++;
            return;
        }
        else
            throw (IndexBeyonds());
    }

    /*деструктор*/
    ~listSequence()
    {
        if (head != NULL)
        {
            while (head->next != NULL)
            {
                head = head->next;
                delete (head->prev);
            }
            delete (head);
        }
        cout <<"Я сделяль :)\n";
    }
};


#endif // CLASSSEQUENCE_H
