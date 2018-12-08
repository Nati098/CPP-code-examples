#ifndef SORTING_H
#define SORTING_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>

#include "C:\Bill\z\Programms\MyLib\sequence.cpp"
#include "C:\Bill\z\Programms\MyLib\exceptions.cpp"

double BubbleSort (Sequence <int> &seq);
double ShakeSort (Sequence <int> &seq);
int increment(long inc[], long length);
double ShellSort(Sequence <int> &seq);
void Compare_Sort_In (int t1, int t2, int t3);
void Compare_Sort_Out (int t1, int t2);

#endif // SORTING_H
