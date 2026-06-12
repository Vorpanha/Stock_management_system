///----here is only for the important element

#pragma once
#include <iostream>

using namespace std;

struct Product {
    string Product_ID;
    string Product_Name;
    int Quantity;
    float Unit_Price;
    Product *next;
};  

struct List {
    int n;
    Product *head;
    Product *tail;
};

List* createEmptyList() {
    List* ls = new List{0,nullptr,nullptr};
    return ls;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SortBubble(int arr[], int size) {
    bool state;
    for(int i = 0; i < size - 1; i++) {
        state = false;
        for(int j = 0; j < size - i - 1; j++) { // bubble j < size - 1
            if(arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                state = true;
            }
        }
        if(state == false) {
            break;
        }
    }
}