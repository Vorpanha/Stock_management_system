///---here organize of the Read or write func
#pragma once
#include <iostream>
#include "struct_func.h"


void saveToCSV(Product *p);
void loadFromCSV(List* ls);
void updateCSVWhenDelete(string ID);
void updateCSV(string ID,Product *p);
void generateReport(List *ls, int totalProducts, int totalQuantity, float totalValue);