///---here organize of the Read or write func
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "struct_func.h"
#include <iomanip>

using namespace std;

fstream file;
string path = "Stock_info.csv", title = "Product ID,Product name,Quantity,Unit prices\n";


void saveToCSV(Product *p){
    bool exist = false;

    if(!exist) {
        fstream check(path, ios::in);
        if (check.is_open()) {
            exist = true;
            check.close();
        }
    }

    if(exist)
        file.open(path,ios::app);
    else{
        file.open(path,ios::out);
        file <<title;
    }
    file << p->Product_ID <<","
         << p->Product_Name <<","
         << to_string(p->Quantity) << ","
         <<to_string(p->Unit_Price) << endl;
    file.close();

}
void loadFromCSV(List* ls){
    bool exist = false;

    if(!exist) {
        fstream check(path, ios::in);
        if(check.is_open()) {
            exist = true;
            check.close();
        }
    }

    if(exist){
        file.open(path,ios::in);
        string line;
        getline(file, line);

        while(getline(file, line)) {
            stringstream s(line);
            string id, name, quantity, price;

            getline(s, id, ',');
            getline(s, name, ',');
            getline(s, quantity, ',');
            getline(s, price, ',');

            Product* p = new Product{id, name, stoi(quantity), stof(price), nullptr};

            if (ls->n == 0) ls->head = p;
            else ls->tail->next = p;
            ls->tail = p;
            ls->n++;
        }

        file.close();
    }
}

void updateCSVWhenDelete(string ID) {
    List* tmp = createEmptyList();//for reading file only
    loadFromCSV(tmp);
    if(tmp->n != 0) {
        string data;
        Product *current = tmp->head;
        file.open(path,ios::out);
        file << title;
        while(current != nullptr) {
            if(current->Product_ID != ID) {
                file << current->Product_ID << ","
                     <<current->Product_Name << ","
                     <<to_string(current->Quantity) << ","
                     <<to_string(current->Unit_Price) << endl;
            }
            current = current->next;
        }
        file.close();
    }
    delete tmp;
}

void updateCSV(string ID,Product *p){
    List* tmp = createEmptyList();//for reading file only
    loadFromCSV(tmp);
    if(tmp->n != 0){
        string data;
        Product *current = tmp->head;
        file.open(path,ios::out);
        file <<title;
        while(current != nullptr){
            if(current->Product_ID != ID)
                file << current->Product_ID << ","
                     << current->Product_Name<<","
                     << to_string(current->Quantity) <<","
                     <<to_string(current->Unit_Price)<<"\n";
            else    
                file << p->Product_ID << "," 
                     <<p->Product_Name<< "," 
                     <<to_string(p->Quantity) <<"," 
                     <<to_string(p->Unit_Price)<< endl;
            current = current->next;
        }
        file.close();
    }
    delete tmp;
}

//--------------------------------GenerateReportTXT-------------------------------
void generateReport(List *ls, int totalProducts, int totalQuantity, float totalValue) {

    ofstream outfile;
    outfile.open("generated_report.txt");

    outfile << "=====================================================================\n";
    outfile << "                         INVENTORY REPORT\n";
    outfile << "=====================================================================\n\n";

    outfile << left
         << setw(13) << "Product ID" << "| "
         << setw(23) << "Product Name" << "| "
         << setw(13) << "Quantity" << "| "
         << "Unit Price" << endl;

    outfile << "---------------------------------------------------------------------\n";

    Product *tmp = ls->head;

    while(tmp != nullptr) {
        float value = tmp->Unit_Price * tmp->Quantity;

        outfile << left
             << setw(13) << tmp->Product_ID << "| "
             << setw(23) << tmp->Product_Name << "| "
             << setw(13) << tmp->Quantity << "| $"
             << value << endl;

        tmp = tmp->next;
    }

    outfile << "---------------------------------------------------------------------\n\n";

    outfile << "Inventory Summary\n";
    outfile << "---------------------------------------------------------------------\n";
    outfile << "Records Found : " << totalProducts << endl;
    outfile << "Total Quantity: " << totalQuantity << endl;
    outfile << "Total Value   : $" << totalValue << endl;
    outfile << "---------------------------------------------------------------------\n";

    outfile.close();
}