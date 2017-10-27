//
//  sort.hpp
//  hw2
//
//  Created by Shikun LI on 10/26/17.
//  Copyright © 2017 Shikun LI. All rights reserved.
//

#ifndef sort_hpp
#define sort_hpp

#include <stdio.h>
#define SIZE 32
#define NUM_RANGE 100000

class SortBasic{
public:
    SortBasic(int a [], int n);
    virtual void sort()=0;
    virtual ~SortBasic(){};
    void print();
    
protected:
    int size;
    int * array;
};

class QuickSort: public SortBasic{
public:
    QuickSort(int a [], int size);
    ~QuickSort();
    void sort();
    private:
    void squentialQuickSort(int array [], int start, int end);
};


class RadixSort: public SortBasic{
public:
    RadixSort(int a[], int size);
    ~RadixSort();
    void sort();
    
private:
    void countSort(int array[], int size, int exp);
    void compAndSwap(int a[], int i, int j, int dir);
};

class BitonicSort:public SortBasic{
public:
    BitonicSort(int a [], int size);
    void sort();
    ~BitonicSort();
private:
    void compAndSwap(int a[], int i, int j, int dir);
    void bitonicMerge(int a[], int low, int size, int dir);
    void bitonicSort(int a[],int low, int size, int dir);

};


#endif /* sort_hpp */
