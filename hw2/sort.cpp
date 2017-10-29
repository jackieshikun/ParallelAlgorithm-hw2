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
    virtual void sort()=0;
    virtual ~SortBasic(){};
    void print(){
        cout<<"Array context"<<endl;
        for(int i = 0; i < size; i++){
            cout<<array[i]<<",";
        }
        cout<<endl;
    }
    bool isAscending(){
        if(array == NULL || size < 2)    return true;
        for(int i = 1; i < size; i++){
            if(array[i] < array[i - 1]) return false;
        }
        return true;
    }
    
protected:
    int size;
    int * array;
};

class QuickSort: public SortBasic{
public:
    QuickSort(int a [], int size):SortBasic(a, size){}
    ~QuickSort(){
        delete [] array;
    }
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
    ~RadixSort(){
        delete [] array;
    }

    void sort(){
        /*
        for(int exp = 1; NUM_RANGE / exp > 0; exp *= 10){
            countSort(array, size, exp);
        }
         */
        int exp = getExp();
        rSort(0, size, exp);
    }
    
protected:
    void rSort(int start, int end, int exp){
        if(start >= end - 1 || exp == 0)  return;
        if(isAscending(start, end)) return;
        int count[2] = {};
        for(int i = start; i < end; i++){
            int num = andOperation(array[i],exp);
            count[num]++;
        }
        count[1] += count[0];
        int middle = count[0] + start;
        int * temp = new int [end - start];
        for(int i = 0; i < end - start; i++){
            int num = andOperation(array[i+start],exp);
            //cout<<"i:"<<i<<" num:"<<num<<endl;
            temp[count[num]-1] = array[i+start];
            count[num]--;
        }
        
        for(int i = 0; i < end-start; i++){
            array[i+start] = temp[i];
        }
        delete [] temp;
        rSort(start, middle, exp >> 1);
        rSort(middle, end, exp >> 1);
    }
    bool isAscending(int start, int end){
        if(start >= end)    return true;
        for(int i = start + 1; i < end; i++){
            if(array[i] < array[i-1])   return false;
        }
        return true;
    }
    int andOperation(int num, int exp){
        int digit = num & exp;
        if(digit == 0)    return 0;
        return 1;
    }
    int getExp(){
        int exp = 1;
        while(exp < NUM_RANGE)  exp<<=1;
        return exp;
    }
    /*
    void countSort(int array[], int size, int exp){
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
    void compAndSwap(int a[], int i, int j, int dir)
    {
        if (dir==(a[i]>a[j]))
            swap(a[i],a[j]);
    }
     */
};





class BitonicSort:public SortBasic{
public:
    BitonicSort(int a [], int size): SortBasic(a, size){}
    void sort(){
        bitonicSort(array, 0, size, 1);
    }

    ~BitonicSort(){
        delete [] array;
    }
private:
    void compAndSwap(int a[], int i, int j, int dir)
    {
        if (dir==(a[i]>a[j]))
            swap(a[i],a[j]);
    }

    void bitonicMerge(int a[], int low, int size, int dir)
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
    void bitonicSort(int a[],int low, int size, int dir)
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
    
};

struct qSort{
    ParaQuickSort * myClass;
    int start;
    int end;
    int threadID;
}typedef QSORTPARAM;


class ParaQuickSort:public SortBasic{
public:
    ParaQuickSort(int a[], int size): SortBasic(a, size){
        size_per_thread = SIZE/THREAD_NUM;
        pt = new pthread_t [THREAD_NUM];
    }
    ~ParaQuickSort(){
        delete [] array;
        delete [] pt;
    }
    void sort(){
        int pIndex = 1;
        int rc = 0;
        void * exit_status;
        
        QSORTPARAM para;
        para.myClass = this;
        para.start = 0;
        para.end = size - 1;
        para.threadID = pIndex;
        if((rc = pthread_create(&pt[pIndex], NULL, _thread_t, &para ))){
            cout<<"Parallel quick sort initialization failed";
            return;
        }
        pthread_join(pt[pIndex], &exit_status);
        
    }
private:
    int size_per_thread;
    pthread_t * pt;
    static void * _thread_t(void * param){
        QSORTPARAM * ptr = (QSORTPARAM *)param;
        ptr->myClass->qsort(ptr->start, ptr->end, ptr->threadID);
        return NULL;
    }
    int partition(int start, int end){
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
    void seqQsort(int start, int end){
        if(start > end) return;
        int index = partition(start, end);
        seqQsort(start, index - 1);
        seqQsort(index+1, end);
    }
    
    void qsort(int start, int end, int tid){
        if(start > end) return;
        //cout<<tid<<endl;
        int rc = 0;
        int index = partition(start, end);
        void * exit_status1;
        void * exit_status2;
        bool isLeft = false;
        bool isRight = false;
        
        if(index - start <= size_per_thread || tid * 2 >= THREAD_NUM){
            seqQsort(start, index - 1);
        }else{
            //tid++;
            cout<<tid<<end;
            QSORTPARAM para;
            para.myClass = this;
            para.start = start;
            para.end = index - 1;
            para.threadID = tid * 2;
            if((rc = pthread_create(&pt[para.threadID], NULL, _thread_t, &para ))){
                cout<<"Parallel quick sort initialization failed";
                return;
            }
            isLeft = true;
            
        }
        
        if(end - index <= size_per_thread || tid * 2 + 1 >= THREAD_NUM){
            seqQsort(index + 1, end);
        }else{
            //tid++;
            QSORTPARAM para;
            para.myClass = this;
            para.start = index + 1;
            para.end = end;
            para.threadID = tid * 2 + 1;
            if((rc = pthread_create(&pt[para.threadID], NULL, _thread_t, &para ))){
                cout<<"Parallel quick sort initialization failed";
                return;
            }
            isRight = true;
            
            
        }
        if(isLeft)  pthread_join(pt[tid * 2], &exit_status1);
        if(isRight) pthread_join(pt[tid * 2 + 1], &exit_status2);
    }
    
};
struct rSortStr{
    ParaRadixSort * myClass;
    int start;
    int end;
    int tid;
    int exp;
    
}typedef RSORT;

class ParaRadixSort:public SortBasic{
public:
    ParaRadixSort(int a [], int size):SortBasic(a,size){
        size_per_thread = SIZE/THREAD_NUM;
        pt = new pthread_t [THREAD_NUM];
    }
    ~ParaRadixSort(){
        delete [] array;
        delete [] pt;
    }
    void sort(){
        int pIndex = 1;
        int rc = 0;
        void * exit_status;
        
        RSORT para;
        para.myClass = this;
        para.start = 0;
        para.end = size;
        para.tid = pIndex;
        para.exp = getExp();
        if((rc = pthread_create(&pt[pIndex], NULL, _thread_t, &para ))){
            cout<<"Parallel quick sort initialization failed";
            return;
        }
        pthread_join(pt[pIndex], &exit_status);
    }
private:
    int size_per_thread;
    pthread_t * pt;
    static void * _thread_t(void * param){
        RSORT * ptr = (RSORT *)param;
        ptr->myClass->RadixSort(ptr->start, ptr->end, ptr->tid, ptr->exp);
        return NULL;
    }
    void RadixSort(int start, int end, int tid, int exp){
        int rc = 0;
        int index = partition(start, end, exp);
        void * exit_status1;
        void * exit_status2;
        bool isLeft = false;
        bool isRight = false;
        if(index - start <= size_per_thread || tid * 2 >= THREAD_NUM){
            rSort(start, index, exp >> 1);
        }else{
            //tid++;
            RSORT para;
            para.myClass = this;
            para.start = start;
            para.end = index;
            para.tid = tid * 2;
            para.exp = exp >> 1;
            if((rc = pthread_create(&pt[para.tid], NULL, _thread_t, &para ))){
                cout<<"Parallel Radix sort initialization failed";
                return;
            }
            isLeft = true;
            
        }
        
        if(end - index <= size_per_thread || tid * 2 + 1 >= THREAD_NUM){
            rSort(index, end, exp>>1);
        }else{
            //tid++;
            RSORT para;
            para.myClass = this;
            para.start = index;
            para.end = end;
            para.tid = tid * 2 + 1;
            para.exp = exp >> 1;
            if((rc = pthread_create(&pt[para.tid], NULL, _thread_t, &para ))){
                cout<<"Parallel quick sort initialization failed";
                return;
            }
            isRight = true;
            //pthread_join(pt[para.tid], &exit_status);
            
        }
        if(isLeft)  pthread_join(pt[tid * 2], &exit_status1);
        if(isRight) pthread_join(pt[tid * 2 + 1], &exit_status2);
    }
    
    int partition(int start, int end, int exp){
        if(start >= end - 1 || exp == 0)  return-1;
        if(isAscending(start, end)) return-1;
        int count[2] = {};
        for(int i = start; i < end; i++){
            int num = andOperation(array[i],exp);
            count[num]++;
        }
        count[1] += count[0];
        int middle = count[0] + start;
        int * temp = new int [end - start];
        for(int i = 0; i < end - start; i++){
            int num = andOperation(array[i+start],exp);
            temp[count[num]-1] = array[i+start];
            count[num]--;
        }
        
        for(int i = 0; i < end-start; i++){
            array[i+start] = temp[i];
        }
        delete [] temp;
        return middle;
    }
    
    void rSort(int start, int end, int exp){
        int middle = partition(start, end, exp);
        if(middle == -1)    return;
        rSort(start, middle, exp >> 1);
        rSort(middle, end, exp >> 1);
    }
    bool isAscending(int start, int end){
        if(start >= end)    return true;
        for(int i = start + 1; i < end; i++){
            if(array[i] < array[i-1])   return false;
        }
        return true;
    }
    int andOperation(int num, int exp){
        int digit = num & exp;
        if(digit == 0)    return 0;
        return 1;
    }
    int getExp(){
        int exp = 1;
        while(exp < NUM_RANGE)  exp<<=1;
        return exp;
    }

};

struct bsortstr{
    ParaBitonicSort * myClass;
    int start;
    int size;
    int dir;
    int tid;
}typedef BSORT;

class ParaBitonicSort:public SortBasic{
public:
    ParaBitonicSort(int a[], int size):SortBasic(a, size){
        size_per_thread = SIZE/THREAD_NUM;
        pt = new pthread_t [THREAD_NUM];

    }
    ~ParaBitonicSort(){
        delete [] array;
        delete [] pt;
    }
    void sort(){
        int pIndex = 1;
        int rc = 0;
        void * exit_status;
        
        BSORT para;
        para.myClass = this;
        para.start = 0;
        para.size = size;
        para.dir = 1;
        para.tid = pIndex;
        if((rc = pthread_create(&pt[pIndex], NULL, _thread_t, &para ))){
            cout<<"Parallel quick sort initialization failed";
            return;
        }
        pthread_join(pt[pIndex], &exit_status);
    }
private:
    static void * _thread_t(void * param){
        BSORT * ptr = (BSORT *)param;
        ptr->myClass->BitonsicSort(ptr->start, ptr->size, ptr->dir, ptr->tid);
        return NULL;
    }
    
    void BitonsicSort(int low, int size, int dir, int tid){
        if(size <= 1)   return;
        int rc = 0;
        int half = size / 2;
        void * exit_status1;
        void * exit_status2;
        bool isLeft = false;
        bool isRight = false;
        if(half <= size_per_thread || tid * 2 >= THREAD_NUM ){
            bitonicSort(low, half, 1);
        }else{
            //tid++;
            BSORT para;
            para.myClass = this;
            para.start = low;
            para.size = half;
            para.dir = 1;
            para.tid = tid * 2;
            if((rc = pthread_create(&pt[para.tid], NULL, _thread_t, &para ))){
                cout<<"Parallel Radix sort initialization failed";
                return;
            }
            isLeft = true;
            
        }
        
        if(half <= size_per_thread || tid * 2 + 1 >= THREAD_NUM){
            bitonicSort(low + half, half, 0);
        }else{
            //tid++;
            BSORT para;
            para.myClass = this;
            para.start = low + half;
            para.size = half;
            para.dir = 0;
            para.tid = tid * 2 + 1;
            if((rc = pthread_create(&pt[para.tid], NULL, _thread_t, &para ))){
                cout<<"Parallel Radix sort initialization failed";
                return;
            }
            isRight = true;
            
        }
        if(isLeft)  pthread_join(pt[tid * 2], &exit_status1);
        if(isRight) pthread_join(pt[tid * 2 + 1], &exit_status2);
        bitonicMerge(low, size, dir);
        
    }
    
    void compAndSwap(int i, int j, int dir)
    {
        if (dir==(array[i]>array[j]))
            swap(array[i],array[j]);
    }
    
    void bitonicMerge(int low, int size, int dir)
    {
        if (size>1)
        {
            int k = size / 2;
            for (int i=low; i<low+k; i++)
                compAndSwap(i, i+k, dir);
            bitonicMerge(low, k, dir);
            bitonicMerge(low+k, k, dir);
            
        }
        
    }
    void bitonicSort(int low, int size, int dir)
    {
        if (size>1)
        {
            int k = size/2;
            
            // sort in ascending order since dir here is 1
            bitonicSort(low, k, 1);
            
            // sort in descending order since dir here is 0
            bitonicSort(low+k, k, 0);
            
            // Will merge wole sequence in ascending order
            // since dir=1.
            bitonicMerge(low, size, dir);
        }
    }
    
    int size_per_thread;
    pthread_t * pt;
    

};
