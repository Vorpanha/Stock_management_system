///---here organize of the Read or write func
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "struct_func.h"

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

            Product* p = new Product{id, name,stoi(quantity), stof(price), nullptr};

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

void generateReport(List *ls,int totalProducts,int totalQuantity,float totalValue){
    string gen_path = "generated_report.txt";
    string report = "Here is Producut Summary:\n\n";

    Product *tmp = ls->head;
    while(tmp != nullptr) {
        float value = tmp->Unit_Price * tmp->Quantity;
        report +="ID: " + tmp->Product_ID+" \t ";
        report += tmp->Product_Name+ "\t\tQuantity: ";
        report += to_string(tmp->Quantity)+ "\t\tValue: $" ;
        report += to_string(value)+"\n";
        tmp = tmp->next;
    }

    delete tmp;

    report+= "\n-------------------------------------------------------\n";
    report += "Total Products      : " + to_string(totalProducts);
    report += "\nTotal Quantity      : " + to_string(totalQuantity) ;
    report += "\nTotal Stock Value   : $" + to_string(totalValue);
    report+=  "\n=======================================================\n";

    file.open(gen_path,ios::out);
    file<<report;
    file.close();    

}
