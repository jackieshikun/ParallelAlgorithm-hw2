//
//  main.cpp
//  hw2
//
//  Created by Shikun LI on 10/26/17.
//  Copyright © 2017 Shikun LI. All rights reserved.
//

#include <iostream>
#include "sort.hpp"
using namespace std;

int * generateArray(int size){
    int * array = new int[size];
    srand(NULL);
    for(int i = 0; i < size; i++){
        array[i] = rand() % NUM_RANGE;
    }
    return array;
}

class Test{
public:
    void doTesting(){
        clock_t start, end;
        start = clock();
        sortAlg->sort();
        end = clock();
        sortAlg->print();

        cout<<"clock cost:" << ((end - start) / 1000000) <<" Million cycles"<<"for algorithm:" << name << endl;
        
        cout<<endl<<endl;
        
    }
    ~Test(){}
    void setAlg(SortBasic * sb){
        this->sortAlg = sb;

    }
    void setName(string s){
        this->name = s;
    }
    
private:
    SortBasic * sortAlg;
    string name;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World11111!\n";
    
    int * array = generateArray(SIZE);
    
    SortBasic * temp = new QuickSort(array, SIZE);
    Test * test = new Test();
    test->setAlg(temp);
    test->setName("Sequential quick sort");
    test->doTesting();
    delete temp;
    
    
    temp = new RadixSort(array, SIZE);
    test->setAlg(temp);
    test->setName("Sequential Radix Sort");
    test->doTesting();
    delete temp;
    
    temp = new BitonicSort(array, SIZE);
    test->setName("Sequential Bitonic Sort");
    test->setAlg(temp);
    test->doTesting();
    delete temp;
    
    
    delete test;
    delete [] array;
    return 0;
}
