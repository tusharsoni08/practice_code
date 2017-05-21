// heap.cpp, Tushar Soni

#include "stack.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Based on 0th index as root of heap
#define PARENT(i) floor((i-1)/2)
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

int heap_size;

void EXCHANGE(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

/*
 * Heaps: Basic Heap Operations (MAX_HEAPIFY, BUILD_MAX_HEAP, HEAP_SORT)
*/
void MAX_HEAPIFY(vector<int> &A, int i){

    unsigned int left_index = LEFT(i);
    unsigned int right_index = RIGHT(i);
    int largest = i;

    if((left_index < heap_size) && (A[left_index] > A[i])) largest = left_index;
    if((right_index < heap_size) && (A[right_index] > A[largest])) largest = right_index;

    if(largest != i){
        EXCHANGE(A[i], A[largest]);
        MAX_HEAPIFY(A, largest);
    }

}

void BUILD_MAX_HEAP(vector<int> &A){
    heap_size = A.size();
    for(int i=floor((heap_size-1)/2); i >= 0; i--)
        MAX_HEAPIFY(A, i);
}

void HEAP_SORT(vector<int> &A){
    BUILD_MAX_HEAP(A);
    heap_size = A.size();
    while (heap_size > 1) {
        EXCHANGE(A[0], A[heap_size-1]);
        heap_size -= 1;
        MAX_HEAPIFY(A, 0);
    }
}


/*
 * Priority Queue Operations: Based on Max-Heap (HEAP_MAXIMUM, HEAP_EXTRACT_MAX, HEAP_INCREASE_KEY,
 * MAX_HEAP_INSERT, HEAP_DELETE)
*/
int HEAP_MAXIMUM(vector<int> &A){
    return A[0];
}

int HEAP_EXTRACT_MAX(vector<int> &A){
    if(heap_size < 1) return -1;
    int max = A[0];
    A[0] = A[heap_size-1];
    heap_size -= 1;
    MAX_HEAPIFY(A, 0);
    return max;
}

void HEAP_INCREASE_KEY(vector<int> &A, int i, int key){
    if(A[i] > key) return;
    A[i] = key;
    while((i > 0) &&(A[PARENT(i)] < A[i])){
        EXCHANGE(A[PARENT(i)], A[i]);
        i = PARENT(i);
    }
}

void MAX_HEAP_INSERT(vector<int> &A, int key){
    heap_size += 1;
    //A[heap_size] = INT_MIN;
    A.push_back(INT_MIN);
    HEAP_INCREASE_KEY(A, heap_size-1, key);
}

void HEAP_DELETE(vector<int> &A, int i){
    A[i] = A[heap_size-1];
    heap_size -= 1;
    if(A[i] > A[PARENT(i)]){
        int key = A[i];
        A[i] = INT_MIN;
        HEAP_INCREASE_KEY(A, i, key);
    }
    else MAX_HEAPIFY(A, i);
}

int main()
{
    //   index :     0  1  2  3  4  5 6 7 8 9 10  11 12 13
    vector<int> A = {27,17,3,16,13,10,1,5,7,12,4, 8, 9, 0};
    vector<int> B = {5,13,2,25,7,17,20,8,4};
    vector<int> C = {27,17,10,16,13,9,1,5,7,12,4, 8, 3, 0};
    vector<int> D = {10,5,9,2,3,7,8};

    //make sure to change the vector for (heap_size) as that vector size initially.
    //heap_size = D.size();
    //MAX_HEAPIFY(A, 2); tested!!
    //BUILD_MAX_HEAP(B);  tested!!
    //HEAP_SORT(B);  tested!!
    //MAX_HEAP_INSERT(C, 2);  tested!!
    //HEAP_EXTRACT_MAX(C);  tested!!
    //HEAP_INCREASE_KEY(C, 4, 25);  tested!!
    //HEAP_DELETE(D, 0);  tested!!


    //Stack using priority queue
    Stack stack;
    for(int i=0; i < B.size(); i++){
        stack.push(B[i]);
    }
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    //stack.printStack();

    //output
//    for(int i=0; i < heap_size; i++){
//        cout << D[i] << " ";
//    }
//    cout << endl;

    return 0;
}
