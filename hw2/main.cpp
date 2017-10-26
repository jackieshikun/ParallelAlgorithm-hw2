//
//  main.cpp
//  hw2
//
//  Created by Shikun LI on 10/26/17.
//  Copyright © 2017 Shikun LI. All rights reserved.
//

#include <iostream>
#include "sort.cpp"

//#define NUM_RANGE 100000
using namespace std;

int * generateArray(int size){
    int * array = new int[size];
    srand(NULL);
    for(int i = 0; i < size; i++){
        array[i] = rand() % NUM_RANGE;
    }
    return array;
}
/*
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
void squentialRadixSort(int array[], int size){
    for(int exp = 1; NUM_RANGE / exp > 0; exp *= 10){
        countSort(array, size, exp);
    }
}

void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir==(a[i]>a[j]))
        swap(a[i],a[j]);
}

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
void sequentialBitonicSort(int array [], int size){
    bitonicSort(array, 0, size, 1);
}


void print(int array[], int size){
    for(int i = 0; i < size; i++){
        cout<<array[i]<<",";
    }
    cout<<endl;
}

*/

class Test{
public:
    Test(SortBasic * sb, string name){
        this->sortAlg = sb;
        this->name = name;
    }
    void doTesting(){
        clock_t start, end;
        start = clock();
        sortAlg->sort();
        end = clock();
        sortAlg->print();

        cout<<"clock cost:" << ((end - start) / 1000000) <<" Million cycles"<<"for algorithm:" << name << endl;
        
        cout<<endl<<endl;
        //cout <<
        //sortAlg->print();
        
    }
    ~Test(){
        //sortAlg->~SortBasic();
        //delete sortAlg;
    }
    
private:
    SortBasic * sortAlg;
    string name;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
        /*
    print(array, SIZE);
    
    int * copy = new int [SIZE];
    memcpy(copy, array, SIZE*sizeof(int));
    print(copy, SIZE);
    squentialQuickSort(copy, 0, SIZE - 1);
    print(copy,SIZE);
    
    memcpy(copy, array, SIZE*sizeof(int));
    squentialRadixSort(copy, SIZE);
    print(copy, SIZE);
    
    memcpy(copy, array, SIZE*sizeof(int));
    sequentialBitonicSort(copy, SIZE);
    print(copy,SIZE);
    */
    
    int * array = generateArray(SIZE);
    QuickSort * a = new QuickSort(array, SIZE);
    
    SortBasic * temp = a;
    Test * test = new Test(temp, "Sequential quick sort");
    test->doTesting();
    delete a;
    delete test;
    
    
    RadixSort * b = new RadixSort(array, SIZE);
    temp = b;
    test = new Test(temp, "Sequential Radix Sort");
    test->doTesting();
    delete b;
    delete test;
    
    
    BitonicSort * c = new BitonicSort(array, SIZE);
    temp = c;
    test = new Test(temp, "Sequential Bitonic Sort");
    test->doTesting();
    delete c;
    delete test;
    
    
    delete [] array;
    return 0;
}
