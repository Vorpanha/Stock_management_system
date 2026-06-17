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

List* createEmptyList();