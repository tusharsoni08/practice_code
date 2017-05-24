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

void Modified_EXCHANGE(pair<int, int> &a, pair<int, int> &b){
    pair<int, int> temp = a;
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

void MIN_HEAPIFY(vector<pair<int, int> > &A, int i){

    unsigned int left_index = LEFT(i);
    unsigned int right_index = RIGHT(i);
    int smallest = i;

    if((left_index < heap_size) && (A[left_index].second < A[i].second)) smallest = left_index;
    if((right_index < heap_size) && (A[right_index].second < A[smallest].second)) smallest = right_index;

    if(smallest != i){
        Modified_EXCHANGE(A[i], A[smallest]);
        MIN_HEAPIFY(A, smallest);
    }

}

void BUILD_MIN_HEAP(vector<pair<int, int> > &A){
    for(int i=floor((heap_size-1)/2); i >= 0; i--)
        MIN_HEAPIFY(A, i);
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

pair<int, int> HEAP_EXTRACT_MIN(vector<pair<int, int> > &A){
    //if(heap_size < 1) return -1;
    int outerVectorIndex = A[0].first;
    int innerVectorValue = A[0].second;
    A[0] = A[heap_size-1];
    A.pop_back();
    heap_size -= 1;
    MIN_HEAPIFY(A, 0);
    return make_pair(outerVectorIndex, innerVectorValue);
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

vector<int> K_Way_Merging(vector<pair<int, vector<int> > > &lists){

    // Here heapArray is vector of pair of (outer_vector_index, inner_vector_value)
    vector<pair<int, int> > heapArray; // It's an intermediate heap array for creating min-heap
    vector<int> sortedList;
    int outerVectorIndex, innerVectorValue, newIndex;

    for(int i=0; i < lists.size(); i++){
        if(lists[i].second.size() > 0)
            heapArray.push_back(make_pair(i, lists[i].second[0]));
    }

    heap_size = heapArray.size();

    while(heap_size > 0){
        BUILD_MIN_HEAP(heapArray);
        pair<int, int> heapMin = HEAP_EXTRACT_MIN(heapArray);
        outerVectorIndex = heapMin.first;
        innerVectorValue = heapMin.second;
        sortedList.push_back(innerVectorValue);
        lists[outerVectorIndex].first++;
        newIndex = lists[outerVectorIndex].first; // updated next array index of min valued element of inner vector
        if(newIndex < lists[outerVectorIndex].second.size()){
            heapArray.push_back(make_pair(outerVectorIndex, lists[outerVectorIndex].second[newIndex]));
            heap_size++;
        }
    }

    return sortedList;
}

int main()
{
    //   index :     0  1  2  3  4  5 6 7 8 9 10  11 12 13
//    vector<int> A = {27,17,3,16,13,10,1,5,7,12,4, 8, 9, 0};
//    vector<int> B = {5,13,2,25,7,17,20,8,4};
//    vector<int> C = {27,17,10,16,13,9,1,5,7,12,4, 8, 3, 0};
//    vector<int> D = {10,5,9,2,3,7,8};

//    //make sure to change the vector for (heap_size) as that vector size initially.
//    //heap_size = D.size();
//    //MAX_HEAPIFY(A, 2); tested!!
//    //BUILD_MAX_HEAP(B);  tested!!
//    //HEAP_SORT(B);  tested!!
//    //MAX_HEAP_INSERT(C, 2);  tested!!
//    //HEAP_EXTRACT_MAX(C);  tested!!
//    //HEAP_INCREASE_KEY(C, 4, 25);  tested!!
//    //HEAP_DELETE(D, 0);  tested!!


//    //Stack using priority queue
//    Stack stack;
//    for(int i=0; i < B.size(); i++){
//        stack.push(B[i]);
//    }
//    cout << stack.top() << endl;
//    stack.pop();
//    cout << stack.top() << endl;
//    stack.pop();
//    cout << stack.top() << endl;
//    stack.pop();
//    cout << stack.top() << endl;
//    stack.pop();
//    stack.pop();
//    stack.pop();
//    stack.pop();
//    cout << stack.top() << endl;
//    stack.pop();
//    cout << stack.top() << endl;
//    stack.pop();
//    stack.pop();
    //stack.printStack();

    //output
//    for(int i=0; i < heap_size; i++){
//        cout << D[i] << " ";
//    }
//    cout << endl;

    // K-Way Mergeing
    vector<pair<int, vector<int> > > lists; // here it's making pair of (inner vector index, inner vector)

    // these are inner or sub sorted vector
    vector<int> v1 = {2,4,6,10,34,50,66,74,87,93,98,110};
    vector<int> v2 = {1,3,11,19,25,30,44,62,78};
    vector<int> v3 = {5,8,12,17,69,72,88,150,200,308};

    lists.push_back(make_pair(0, v1));
    lists.push_back(make_pair(0, v2));
    lists.push_back(make_pair(0, v3));

    vector<int> sortedList = K_Way_Merging(lists);

    for(auto i : sortedList){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
