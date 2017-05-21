/*
 * stack.h, Tushar Soni
 * Description: Stack interface using Priority Queue.
*/

#ifndef STACK_H
#define STACK_H
#include <utility>
#include <vector>

using namespace std;

class Stack
{
public:
    Stack();
    ~Stack();

    void push(int val);
    void pop();
    int top();
    void printStack();

private:
    vector<pair<int, int> > pq;
    int key;
    int priority;
    int heap_size = 0;

    void Exchange(pair<int, int> &a, pair<int, int> &b);
    void Max_heapify(vector<pair<int, int> > &A, int i);
    void Build_max_heap(vector<pair<int, int> > &A);
    int Heap_extract_max();
    int Heap_maximum();
};

#endif // STACK_H
