#ifndef EXCEPTIONS_CPP
#define EXCEPTIONS_CPP
#include <iostream>
#include <cstdlib>

using namespace std;

class Except
{
private:
    int errCode;
public:
    virtual int Message() = 0;
};

class IndexBeyonds:Except
{
private:
    int errCode;
public:
    IndexBeyonds()
    {
        errCode = 1;
    }

    int Message()
    {
        cout << "Индекс за пределами допустимого" << endl;
        return (errCode);
    }
};

class EmptySeq:Except
{
private:
    int errCode;
public:
    EmptySeq()
    {
        errCode = 2;
    }

    int Message()
    {
        cout << "Последовательность пустая" << endl;
        return (errCode);
    }
};


#endif
