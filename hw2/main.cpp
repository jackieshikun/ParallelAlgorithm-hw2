//
//  main.cpp
//  hw2
//
//  Created by Shikun LI on 10/26/17.
//  Copyright © 2017 Shikun LI. All rights reserved.
//

#include <iostream>
#include "sort.hpp"
#include "sort.cpp"
using namespace std;

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


int * generateArray(int size){
    //cout<<"size:"<<size<<endl;
    int * array = new int[size];
    //srand(time(NULL));
    srand(NULL);
    for(int i = 0; i < size; i++){
        array[i] = rand() % NUM_RANGE;
    }
    return array;
}

class Test{
public:
    void doTesting(){
        //clock_t start, end;
        double start, end;
        bool isAscending = sortAlg->isAscending();
        cout<<"Before sorting: Is ascending? "<< isAscending<<endl;
        start = rdtsc();
        sortAlg->sort();
        end = rdtsc();
        isAscending = sortAlg->isAscending();
        cout<<"After sorting: Is ascending? "<< isAscending<<endl;
        //sortAlg->print();

        cout<<name<<" cost:" << ((end - start) / (1024*1024)) <<" Million cycles"<< endl;
        
        cout<<endl;
        
    }
    ~Test(){}
    void setAlg(SortBasic * sb){
        if(sortAlg != NULL){
            delete sortAlg;
        }
        this->sortAlg = sb;

    }
    void setName(string s){
        this->name = s;
    }
    
private:
    SortBasic * sortAlg;
    string name;
};

//Parallel quick sort
/*
int partition(int array [], int start, int end){
    if(start > end) return -1;
    int pivot = array[end];
    int left = start;
    for(int i = start; i < end; i++){
        if(array[i] < pivot){
            swap(array[i], array[left]);
            left++;
        }
    }
    swap(array[left], array[end]);
    return left;
}
struct qStr{
    int * array;
    int start;
    int end;
}typedef QSTR;

void * seqQsort(void * para){
    QSTR * temp = (QSTR *)para;
    int * array = temp->array;
    int start = temp->start;
    int end = temp->end;
    if(start > end) return NULL;
    int index = partition(array, start, end);
    QSTR temp1;
    temp1.array = array;
    temp1.start = start;
    temp1.end = index - 1;
    seqQsort(&temp1);
    QSTR temp2;
    temp2.array = array;
    temp2.start = index + 1;
    temp2.end = end;
    seqQsort(&temp2);
    return NULL;
}
*/
typedef struct {
    int start_index;
    int* data_set;
    int end_index;
}info;

//utility function
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 1.
//quicksort part
void quickSort_sequential(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
         at right place */
        int pi = partition(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSort_sequential(arr, low, pi - 1);
        quickSort_sequential(arr, pi + 1, high);
    }
}

//2.
//quicksort pthread
void* quickSort(void *data)
{
    info *tmp = (info*)data;
    int low, high;
    low = tmp->start_index;
    high = tmp->end_index;
    int* num = tmp->data_set;
    if(low<high){
        int pi = partition(num, low, high);
        quickSort_sequential(num, low, pi-1);
        quickSort_sequential(num, pi+1, high);
    }
    return NULL;
}
void quickSort_pthread(int a[], int low, int high){
    
    info *dat = (info*)malloc(sizeof(info));
    dat->data_set=(int*)malloc(sizeof(int)*SIZE);
    dat->data_set=a;
    dat->start_index=0;
    dat->end_index=SIZE-1;
    
    info other_info;
    
    pthread_attr_t attr;
    pthread_t thread_id1;
    pthread_attr_init(&attr);
    
    if( low < high)
    {
        int j = partition( dat->data_set, low, high);
        
        other_info.start_index = j + 1;
        other_info.end_index = high;
        other_info.data_set = dat->data_set;
        
        if (pthread_create(&thread_id1, NULL, quickSort, &other_info)) {
            fprintf(stderr, "No threads for you.\n");
        }
        
        dat->start_index= low;
        dat->end_index= j-1;
        
        if(dat->end_index < 0)
            dat->end_index = 0;
        quickSort(dat);  /* don't care about the return value */
        
        pthread_join(thread_id1, NULL);
    }
}



bool isAscending(int array [], int size){
    if(array == NULL || size < 2)    return true;
    for(int i = 1; i < size; i++){
        if(array[i] < array[i - 1]) return false;
    }
    return true;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    
    int * array = generateArray(SIZE);
    Test * test = new Test();
    double start, end;
    
    test->setAlg(new QuickSort(array, SIZE));
    test->setName("Sequential quick sort");
    test->doTesting();
    /*
    int * copy = new int [SIZE];
   
    memcpy(copy, array, SIZE);
    bool is = isAscending(copy, SIZE);
    cout<<"Before sorting: Is ascending? "<< is<<endl;
    start = rdtsc();
    quickSort_sequential(copy, 0, SIZE - 1);
    end = rdtsc();
    is = isAscending(copy, SIZE);
    cout<<"After sorting: Is ascending? "<< is<<endl;
    cout<<" cost:" << ((end - start) / (1024 * 1024)) <<" Million cycles"<< endl<<endl;
    
    delete [] copy;
    is = isAscending(array, SIZE);
    cout<<"Before sorting: Is ascending? "<< is<<endl;
    
    start = rdtsc();
    quickSort_pthread(array, 0, SIZE - 1);
    end = rdtsc();
    
    is = isAscending(array, SIZE);
    cout<<"After sorting: Is ascending? "<< is<<endl;
    cout<<" cost:" << ((end - start) / (1024*1024)) <<" Million cycles"<< endl;
    */
    /*
    int index = partition(array, 0, SIZE - 1);
    int rc;
    QSTR para;
    para.array = array;
    para.start = 0;
    para.end = index - 1;
    pthread_t p1;
    if((rc = pthread_create(&p1, NULL, seqQsort, &para ))){
        cout<<"Parallel quick sort initialization failed";
        return -1;
    }
    
    QSTR para2;
    para2.start = index + 1;
    para2.end = SIZE - 1;
    para2.array = array;
    seqQsort(&para2);
    pthread_join(p1, NULL);
     */
    
    
    test->setAlg(new RadixSort(array, SIZE));
    test->setName("Sequential Radix Sort");
    test->doTesting();
    
    test->setAlg(new BitonicSort(array, SIZE));
    test->setName("Sequential Bitonic Sort");
    test->doTesting();
    
    
    test->setAlg(new ParaQuickSort(array, SIZE));
    test->setName("Parallel quick sort");
    test->doTesting();
    
    test->setAlg(new ParaRadixSort(array, SIZE));
    test->setName("Parallel Radix sort");
    test->doTesting();
    
    
    test->setAlg(new ParaBitonicSort(array, SIZE));
    test->setName("Parallel Bitonic sort");
    test->doTesting();
    
    delete test;
    delete [] array;
    return 0;
}

