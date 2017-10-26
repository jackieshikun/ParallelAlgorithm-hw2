//
//  sort.cpp
//  hw2
//
//  Created by Shikun LI on 10/26/17.
//  Copyright © 2017 Shikun LI. All rights reserved.
//

#include "sort.hpp"
#include<iostream>
using namespace std;

class SortBasic{
public:
    SortBasic(int a [], int n){
        size = n;
        array = new int [size];
        memcpy(array, a, sizeof(int) * size);
    }
    ~SortBasic(){
        delete [] array;
    }
    virtual void sort()=0;
    int * getArray(){
        return array;
    }
    void print(){
        for(int i = 0; i < size; i++){
            cout<<array[i]<<",";
        }
        cout<<endl;
    }
protected:
    int size;
    int * array;

};

class QuickSort: public SortBasic{
public:
    QuickSort(int a [], int size):SortBasic(a, size){}
    void sort(){
        squentialQuickSort(array, 0, size - 1);
    }
private:
    void squentialQuickSort(int array [], int start, int end){
        if(start > end) return;
        int pivot = array[end];
        int left = start;
        for(int i = start; i < end; i++){
            if(array[i] < pivot){
                swap(array[left], array[i]);
                left++;
            }
        }
        swap(array[left], array[end]);
        squentialQuickSort(array, start, left - 1);
        squentialQuickSort(array, left + 1, end);
    }
};

class RadixSort: public SortBasic{
public:
    RadixSort(int a[], int size):SortBasic(a, size){}
    void sort(){
        for(int exp = 1; NUM_RANGE / exp > 0; exp *= 10){
            countSort(array, size, exp);
        }
    }
private:
    void countSort(int array[], int size, int exp){
        int output[size]; // output array
        int i, count[10] = {0};
        
        // Store count of occurrences in count[]
        for (i = 0; i < size; i++)
            count[ (array[i]/exp)%10 ]++;
        
        // Change count[i] so that count[i] now contains actual
        //  position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        // Build the output array
        for (i = size - 1; i >= 0; i--)
        {
            output[count[ (array[i]/exp)%10 ] - 1] = array[i];
            count[ (array[i]/exp)%10 ]--;
        }
        
        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (i = 0; i < size; i++)
            array[i] = output[i];
    }
    
    void compAndSwap(int a[], int i, int j, int dir)
    {
        if (dir==(a[i]>a[j]))
            swap(a[i],a[j]);
    }
};

class BitonicSort : public SortBasic{
public:
    BitonicSort(int a [], int size): SortBasic(a, size){}
    void sort(){
        bitonicSort(array, 0, size, 1);
    }
private:
    void compAndSwap(int a[], int i, int j, int dir)
    {
        if (dir==(a[i]>a[j]))
            swap(a[i],a[j]);
    }
    
    /*It recursively sorts a bitonic sequence in ascending order,
     if dir = 1, and in descending order otherwise (means dir=0).
     The sequence to be sorted starts at index position low,
     the parameter cnt is the number of elements to be sorted.*/
    void bitonicMerge(int a[], int low, int cnt, int dir)
    {
        if (cnt>1)
        {
            int k = cnt/2;
            for (int i=low; i<low+k; i++)
                compAndSwap(a, i, i+k, dir);
            bitonicMerge(a, low, k, dir);
            bitonicMerge(a, low+k, k, dir);
        }
    }
    
    
    
    void bitonicSort(int a[],int low, int size, int dir)
    {
        if (size>1)
        {
            int k = size/2;
            
            // sort in ascending order since dir here is 1
            bitonicSort(a, low, k, 1);
            
            // sort in descending order since dir here is 0
            bitonicSort(a, low+k, k, 0);
            
            // Will merge wole sequence in ascending order
            // since dir=1.
            bitonicMerge(a,low, size, dir);
        }
    }
};
