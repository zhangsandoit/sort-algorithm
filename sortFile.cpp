//
//  sourtFile.cpp
//  template
//
//  Created by cocoa on 2021/1/11.
//  Copyright © 2021 ronglian. All rights reserved.
//

#include "sourtFile.hpp"

void swap(int array[],int i,int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


void ModInsSort(int Array[],int n, int dalta){
    
    int i, j;
    for (i = dalta; i < n; i++) {
        for (j = i; j >= dalta; j-= dalta) {
            if (Array[j] < Array[j-dalta]) {
                swap(Array, j, j-dalta);
            }else{
                break;
            }
        }
    }
}



#pragma mark ---- 简单排序

//直接插入排序
void InsterSort(int Array[],int n){
    int tempRecord;
    int i,j;
    for (i = 1; i<n; i++) {
        tempRecord = Array[i];
        j = i - 1;
        while (j >=0 && tempRecord < Array[j]) {
            Array[j+1] = Array[j];
            j = j-1;
        }
        Array[j+1] = tempRecord;
    }
}

//冒泡排序
void BubbleSort(int Array[],int n){
    bool noSwap;
    int i, j;
    for (i = 0; i < n -1; i++) {
        noSwap = true;
        for (j = n-1; j>i ; i--) {
            if (Array[j] < Array[j-1]) {
                swap(Array, j, j-1);
                noSwap = false;
            }
        }
        if (noSwap) {
            return;
        }
    }
}

//直接选择排序
void SelectSort(int Array[],int n){
    int i , j ,Smallest;
    for (i = 0; i < n-1; i++) {
        
        Smallest = i;
        for (j = i ; j < n; j++) {
            if (Array[j] < Array[Smallest]) {
                Smallest = j;
                
            }
        }
        swap(Array, i, Smallest);
    }
}


#pragma mark --- Shell 排序

void ShellSort(int Array[],int n){
    int i,delta;
    for (delta = n/2; delta > 0; delta /= 2) {
        for (i = 0; i < delta; i++) {
            ModInsSort(Array, n- i, delta);
        }
        ModInsSort(Array, n, 1);
    }
}

#pragma mark --- 基于分治法的排序


int SelectPiovt(int left,int right){
    return (left + right)/2;
}

int Partition(int array[],int left,int right){
    int l = left;
    int r = right;
    int tempRecord = array[r];
    while (l != r) {
        while (array[l] <= tempRecord && r > l) {
            l++;
        }
        if (l < r) {
            array[r] = array[l];
            r--;
        }
        while (array[r] >= tempRecord && r > l) {
            r--;
        }
        if (l < r) {
            array[l] = array[r];
            l++;
        }
    }
    array[l] = tempRecord;
    return l;
}

//快速排序
void QuickSort(int Array[],int left,int right){
    if (right <= left) {
        return;
    }
    int pivot = SelectPiovt(left, right);
    swap(Array, pivot, right);
    pivot = Partition(Array, left, right);
    QuickSort(Array, left, pivot);
    QuickSort(Array, pivot + 1, right);
    
    
}
//优化的快速排序
#define THEESHOLD 16

void ModQuickSort(int Array[],int left,int right){
    if (right - left + 1 > THEESHOLD) {
        int pivot = SelectPiovt(left, right);
        swap(Array, pivot, right);
        pivot = Partition(Array, left, right);
        ModQuickSort(Array, left, pivot - 1);
        ModQuickSort(Array, pivot + 1, right);
    }
}

void QuickSort(int array[],int n){
    ModQuickSort(array, 0, n - 1);
    InsterSort(array, n);
}


//归并排序
//两路归并排序

void Merge(int array[],int tempArr[], int left,int right,int middle){
    
    int i,j,index1,index2;
    for (j = left; j <= right; j++) {
        tempArr[j] = array[j];
    }
    index1 = left;
    index2 = middle + 1;
    i = left;
    while (index1 <= middle && index2 <= right) {
        if (tempArr[index1] <= tempArr[index2]) {
            array[i++] = tempArr[index1++];
        }else{
            array[i++] = tempArr[index2++];
        }
    }
    while (index1 <= middle) {
        array[i++] = tempArr[index1++];
    }
    while (index2 <= right) {
        array[i++] = tempArr[index2++];
    }
    
}


void MergeSort(int array[],int tempArr[],int left, int right){
    int middle;
    
    if (left < right) {
        middle = (left + right) / 2;
        
        MergeSort(array, tempArr, left, middle);
        MergeSort(array, tempArr, middle + 1, right);
        Merge(array,tempArr,left,right,middle);
    }
}

//优化的两路归并排序
void ModMerge(int array[],int tempArr[],int left,int right,int middle){
    int index1,index2;
    int i , j ,k;
    
    for (i = left; i <= middle; i++) {
        tempArr[i] = array[i];
    }
    for (j = 1; j <= right - middle; j++) {
        tempArr[right - j + 1] = array[j + middle];
    }
    
    for (index1 = left , index2 = right,k = left; k <= right; k++) {
        if (tempArr[index1] <= tempArr[index2]) {
            array[k] = tempArr[index1 ++];
        }else{
            array[k] = tempArr[index2 --];
        }
    }
}

void ModMergeSort(int array[],int tempArr[],int left,int right){
    int middle;
    if (right - left +1 > THEESHOLD) {
        middle = (left + right) / 2;
        ModMergeSort(array, tempArr, left, middle);
        ModMergeSort(array, tempArr, middle + 1, right);
        ModMerge(array, tempArr, left, right, middle);
    }else{
        InsterSort(&array[left], right - left + 1);
    }
}


#pragma mark --- 堆排序

template <class T>
//建堆
class MinHeap{
private:
    T * heapArray;
    int currentSize;
    int maxSize;
    void BuildHeap();
public:
    MinHeap(const int n);
    virtual ~MinHeap(){delete []heapArray;};
    bool isEmpty();
    bool isLeaf(int pos) const;
    int LeftChild(int pos) const;
    int RightChild(int pos) const;
    int Parent(int pos) const;
    bool Remove(int pos, T& node);
    bool Insert(const T& newNode);
    T& RemoveMin();
    void ShiftUp(int pos);
    void ShiftDown(int left);
    
};


void HeapSort(int array[],int n){
    int i;
    MinHeap<int>min_Heap = MinHeap<int>(*array);
    for (i = 0; i < n-1; i++) {
        min_Heap.RemoveMin();
    }
}

#pragma Mark --- 分配排序
//桶排序
void BucketSort(int array[],int n ,int max){
    int * tempArray = new int[n];
    int * count = new int[max];
    int i ;
    for (i = 0; i < n; i++) {
        tempArray[i] = array[i];
    }
    for (i = 0; i < max; i++) {
        count[i] = 0;
    }
    for (i = 0; i < max; i++) {
        count[array[i]]++;
    }
    for (i = 1; i < max; i++) {
        count[i] = count[i - 1] + count[i];
    }
    for (i = n -1; i >= 0; i--) {
        array[--count[tempArray[i]]] = tempArray[i];
    }
    
}

#pragma mark --- 基数排序
//顺序方法的基数排序
void RadixSort(int array[],int n, int d, int r){
    int * tempArr = new int[n];
    int * count = new int[r];
    int i,j,k;
    int Radix = 1;
    //序码
    for (i= 1; i <= d; i++) {
        for (j = 0; j<r; j++) {
            count[j] = 0;
        }
        for (j = 0; j < n; j++) {
            k = (array[j] /Radix) %r;
            count[k]++;
        }
        for (j = 1; j < r; j++) {
            count[j] = count[j - 1] + count[j];
            
        }
        for (j = n- 1; j >= 0; j--) {
            k = (array[j] / Radix) % r;
            count[k] --;
            tempArr[count[k]] = array[j];
        }
        for (j = 0; j < n; j++) {
            array[j] = tempArr[j];
        }
        Radix *= r;
        
    }
    delete []tempArr;
    delete []count;
}

//基于静态连的基数排序

class Node{
public:
    int key;
    int next;
};

class StaticQueue{
public:
    int head;
    int tail;
};


void Distribute(Node * array, int first,int i,int r,StaticQueue * queue){
    int j, k ,a, curr = first;
    for (j = 0; j < r; j++) {
        queue[j].head = -1;
    }
    while (curr != -1) {
        k = array[curr].key;
        for (a = 0; a < i; a++) {
            k = k /r;
        }
        k = k %r;
        if (queue[k].head == -1) {
            queue[k].head = curr;
        }else{
            array[queue[k].tail].next = curr;
        }
        queue[k].tail = curr;
        curr = array[curr].next;
    }
}

void Collect(Node * array,int& first,int r,StaticQueue * queue){
    int last,k = 0;
    while (queue[k].head == -1) {
        k++;
    }
    first = queue[k].head;
    last = queue[k].tail;
    
    while (k < r- 1) {
        k++;
        while (k < r - 1 && queue[k].head == -1) {
            k++;
        }
        if (queue[k].head != -1) {
            array[last].next = queue[k].head;
            last = queue[k].tail;
        }
    }
    array[last].next = -1;
}

void AddrSort(Node * array,int n, int first){
    int i , j;
    j = first;
    Node tempRecord;
    for (i = 0; i < n - 1; i++) {
        tempRecord = array[j];
        array[j] = array[i];
        array[i] = tempRecord;
        array[i].next = j;
        j = tempRecord.next;
        while (j <= i) {
            j = array[j].next;
        }
    }
}

void RadixSort_StaticQueue(Node * array,int n,int d,int r){
    int i ,first = 0;
    StaticQueue * queue = new StaticQueue[r];
    for (i = 0; i < n-1; i++) {
        array[i].next = i + 1;
    }
    array[n - 1].next = -1;
    for (i = 0; i < d; i++) {
        Distribute(array, first, i, r, queue);
        Collect(array, first, r, queue);
    }
    delete [] queue;
    AddrSort(array, n, first);
}


#pragma mark --- 索引排序
//利用索引数字进行循环调整的算法
void AdjustRecord(int array[],int IndexArr[],int n){
    int tempRecord;
    int i , j;
    for (i = 0; i < n; i++) {
        j = i;
        tempRecord = array[i];
        while (IndexArr[j] != i) {
            int k = IndexArr[j];
            array[j] = array[k];
            IndexArr[j] = j;
            j = k;
        }
        array[j] = tempRecord;
        IndexArr[j] = j;
    }
}

//采用简单插入的排序索引
void IndexSort(int Array[],int IndexArr[],int n){
    int i ,j;
    for (i = 0; i < n; i++) {
        IndexArr[i] = i;
    }
    for (i = 1; i < n; i++) {
        for (j = i; j> 0; j--) {
            if (Array[IndexArr[j]] < Array[IndexArr[j-1]]) {
                swap(IndexArr, j, j-1);
            }else break;
        }
    }
    AdjustRecord(Array, IndexArr, n);
}

























