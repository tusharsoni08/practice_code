/*
 * stack.cpp, Tushar Soni
 * Description: Stack implementation using Priority Queue.
*/

#include "stack.h"
#include <iostream>
#include <cmath>

using namespace std;

#define PARENT(i) floor((i-1)/2)
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

Stack::Stack()
{
    priority = 0;
}

Stack::~Stack(){

}

void Stack::Exchange(pair<int, int> &a, pair<int, int> &b){
    pair<int, int> temp = a;
    a = b;
    b = temp;
}

void Stack::Build_max_heap(vector<pair<int, int> > &A){
    heap_size = A.size();
    for(int i=floor((heap_size-1)/2); i >= 0; i--)
        Max_heapify(A, i);
}

void Stack::Max_heapify(vector<pair<int, int> > &A, int i){
    unsigned int left_index = LEFT(i);
    unsigned int right_index = RIGHT(i);
    int largest = i;

    if((left_index < heap_size) && (A[left_index].first > A[i].first)) largest = left_index;
    if((right_index < heap_size) && (A[right_index].first > A[largest].first)) largest = right_index;

    if(largest != i){
        Exchange(A[i], A[largest]);
        Max_heapify(A, largest);
    }
}

int Stack::Heap_extract_max(){
    if(heap_size < 1) return -1;
    //int max_key = pq[0].first;
    int max_value = pq[0].second;
    pq[0] = pq[heap_size-1];
    heap_size -= 1;
    Max_heapify(pq, 0);
    return max_value;
}

int Stack::Heap_maximum(){
    if(heap_size > 0){
        return pq[0].second;
    }else{
        return -1;
    }
}

void Stack::push(int val){
    ++priority;
    pq.push_back(make_pair(priority, val));
    Build_max_heap(pq);
}

void Stack::pop(){
    int max = Heap_extract_max();
    if(max == -1){
        cout << "Stack is empty!!" << endl;
    }else{
        cout << "Popped value is: " << max << endl;
    }
}

int Stack::top(){
    int top_val = Heap_maximum();
    if(top_val != -1){
        return top_val;
    }
}

void Stack::printStack(){
    cout << "values ";
    for(int i=0; i < heap_size; i++){
        cout << pq[i].second << " ";
    }
    cout << endl;
    cout << "keys   ";
    for(int i=0; i < heap_size; i++){
        cout << pq[i].first << " ";
    }
}
