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



SortBasic::SortBasic(int a [], int n){
    size = n;
    array = new int [size];
    memcpy(array, a, sizeof(int) * size);
}
void SortBasic::print(){
    cout<<"Array context"<<endl;
    for(int i = 0; i < size; i++){
        cout<<array[i]<<",";
    }
    cout<<endl;
        
}

QuickSort::QuickSort(int a [], int size):SortBasic(a, size){}
QuickSort::~QuickSort(){
    delete [] array;
}

void QuickSort::sort(){
    squentialQuickSort(array, 0, size - 1);
}
void QuickSort::squentialQuickSort(int array [], int start, int end){
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
RadixSort::RadixSort(int a[], int size):SortBasic(a, size){}
void RadixSort::sort(){
    for(int exp = 1; NUM_RANGE / exp > 0; exp *= 10){
        countSort(array, size, exp);
    }
}
RadixSort::~RadixSort(){
    delete [] array;
}


void RadixSort::countSort(int array[], int size, int exp){
    int output[size]; // output array
    int i, count[10] = {0};
    
    for (i = 0; i < size; i++)
        count[ (array[i]/exp)%10 ]++;
    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (i = size - 1; i >= 0; i--)
    {
        output[count[ (array[i]/exp)%10 ] - 1] = array[i];
        count[ (array[i]/exp)%10 ]--;
    }
    
    for (i = 0; i < size; i++)
        array[i] = output[i];
}

void RadixSort::compAndSwap(int a[], int i, int j, int dir)
{
    if (dir==(a[i]>a[j]))
        swap(a[i],a[j]);
}


BitonicSort::BitonicSort(int a [], int size): SortBasic(a, size){}
void BitonicSort::sort(){
    bitonicSort(array, 0, size, 1);
}

BitonicSort::~BitonicSort(){
    delete [] array;
}
void BitonicSort::compAndSwap(int a[], int i, int j, int dir)
{
    if (dir==(a[i]>a[j]))
        swap(a[i],a[j]);
}
void BitonicSort::bitonicMerge(int a[], int low, int size, int dir)
{
    if (size>1)
    {
        int k = size / 2;
        for (int i=low; i<low+k; i++)
            compAndSwap(a, i, i+k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, size - k, dir);
    }
}
void BitonicSort::bitonicSort(int a[],int low, int size, int dir)
{
    if (size>1)
    {
        int k = size/2;
        
        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);
        
        // sort in descending order since dir here is 0
        bitonicSort(a, low+k, size - k, 0);
        
        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a,low, size, dir);
    }
}
