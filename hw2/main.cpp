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

int * generateArray(int size){
    int * array = new int[size];
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        array[i] = rand() % NUM_RANGE;
    }
    return array;
}

class Test{
public:
    void doTesting(){
        clock_t start, end;
        bool isAscending = sortAlg->isAscending();
        cout<<"Before sorting: Is ascending? "<< isAscending<<endl;
        start = clock();
        sortAlg->sort();
        end = clock();
        isAscending = sortAlg->isAscending();
        cout<<"After sorting: Is ascending? "<< isAscending<<endl;
        //sortAlg->print();

        cout<<name<<" cost:" << ((end - start) / 1000000.0) <<" Million cycles"<< endl;
        
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


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int * array = generateArray(SIZE);
    Test * test = new Test();
    

    test->setAlg(new QuickSort(array, SIZE));
    test->setName("Sequential quick sort");
    test->doTesting();
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
