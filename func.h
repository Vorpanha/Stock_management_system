///---here only for the function only
#pragma once
#include <iostream>
#include <string>
#include "stream.h"
#include "struct_func.h"

using namespace std;

void for_user_or_admin(){
    cout<<"Which role are you:";
    cout<<"[1]. Admin";
    cout <<"[2]. ";
}

//----------------------------------Manu-----------------------------------
void manu() {
    cout << "=======================================================\n";
    cout << "         STOCK INFORMATION MANAGEMENT SYSTEM\n";
    cout << "=======================================================\n\n";
    cout << "";

    cout << "[1]. Add Stock Item\n";
    cout << "[2]. Display All Stocks\n";
    cout << "[3]. Search Stock\n";
    cout << "[4]. Update Stock\n";
    cout << "[5]. Delete Stock\n";
    cout << "[6]. Generate Report\n";
    cout << "[7]. Exit program\n\n";

    cout << "-------------------------------------------------------\n";
    cout << "Enter your choice : ";
}
//----------------------------------Manu-----------------------------------

//--------------------------------AddStock---------------------------------
void addStock(List *ls) { 

    cout << "=======================================================\n";
    cout << "                    ADD STOCK ITEM\n";
    cout << "=======================================================\n\n";

    Product* New_product = new Product;
    cout << "Product ID(Ex: E001) : ";
    cin >> New_product->Product_ID;
    cin.ignore();
    cout << "Product Name         : ";
    getline(cin, New_product->Product_Name);
    cout << "Quantity             : ";
    cin >> New_product->Quantity;
    cout << "Unit Price           : ";
    cin >> New_product->Unit_Price;
    New_product->next = nullptr;
    
    saveToCSV(New_product);

    if(ls->n == 0) {
        ls->head = New_product;
        ls->tail = New_product;
    } else {
        ls->tail->next = New_product;
        ls->tail = New_product;
    }

    ls->n++;

    cout << "\n-------------------------------------------------------\n";
    cout << "[SUCCESS] Product added successfully.\n";
    cout << "-------------------------------------------------------\n\n";


    cout << "Data saved to stock.csv" << endl;

}
//--------------------------------AddStock---------------------------------

//------------------------------DisplayStock-------------------------------
void displayStock(List *ls) {

    if(ls->head == nullptr) {
        cout << "No stock available." << endl;
        return;
    }

    cout << "=======================================================\n";
    cout << "                   DISPLAY ALL STOCKS\n";
    cout << "=======================================================\n\n";

    cout << "ID\tName\t\tQuantity\tPrice($)\n";
    cout << "-------------------------------------------------------\n";

    Product *temp = ls->head;
    int count = 0;
 
    while(temp != NULL) {
        cout << temp->Product_ID << "\t"
             << temp->Product_Name << "\t\t"
             << temp->Quantity << "\t\t"
             << temp->Unit_Price << endl;
        temp = temp->next;
        count++;
    }

    cout << "-------------------------------------------------------\n\n";
    cout << "Total Products : " << count << endl;

    cout << "\n=======================================================\n";

}
//------------------------------DisplayStock-------------------------------

//------------------------------SearchStock--------------------------------
void searchStock(List *ls) {
    cout << "=======================================================\n";
    cout << "                     SEARCH STOCK\n";
    cout << "=======================================================\n\n";

    if(ls->head == nullptr) {
        cout << "No stock available." << endl;
        return;
    }

    string searchName;
    cout << "Enter Product Name to search: ";
    cin.ignore();
    getline(cin, searchName);

    Product *temp = ls->head;
    bool found = false;

    while(temp != nullptr) {
        if(temp->Product_Name == searchName) {

            cout << "\n-------------------------------------------------------\n";
            cout << "Product Information\n";
            cout << "-------------------------------------------------------\n";

            cout << "ID       : " << temp->Product_ID << endl;
            cout << "Name     : " << temp->Product_Name << endl;
            cout << "Quantity : " << temp->Quantity << endl;
            cout << "Price    : $" << temp->Unit_Price << endl;

            cout << "-------------------------------------------------------\n";
            found = true;
            return;
        }
        temp = temp->next;
    }
    if(!found) {
        cout << "\n-------------------------------------------------------\n";
        cout << "[ERROR] Product not found.\n";
        cout << "-------------------------------------------------------\n";
    }
}
//------------------------------SearchStock--------------------------------

//-------------------------------UpdateStock-------------------------------
void updateStock(List* ls) {

    cout << "=======================================================\n";
    cout << "                     UPDATE STOCK\n";
    cout << "=======================================================\n\n";

    string searchID;
    bool found = false;
    cout << "Enter ID to update: ";
    cin >> searchID;

    Product *temp = ls->head;

    while (temp != nullptr) {
        if (temp->Product_ID == searchID) {
            cout << "\n-------------------------------------------------------\n";
            cout << "Current Product Information\n";
            cout << "-------------------------------------------------------\n";

            cout << "ID          : " << temp->Product_ID << endl;
            cout << "Name        : " << temp->Product_Name << endl;
            cout << "Quantity    : " << temp->Quantity << endl;
            cout << "Price ($)   : " << temp->Unit_Price << endl;

            cout << "-------------------------------------------------------\n\n";

            cin.ignore();
            cout << "New Product_Name: ";
            getline(cin, temp->Product_Name);
            cout << "New Quantity: ";
            cin >> temp->Quantity;
            cout << "New Unit_Price: ";
            cin >> temp->Unit_Price;
            
            updateCSV(searchID,temp);

            cout << "\n-------------------------------------------------------\n";
            cout << "[SUCCESS] Product updated successfully.\n";
            cout << "Data saved to stock.csv\n";
            cout << "-------------------------------------------------------\n";

            found = true;
            return;
        }
        temp = temp->next;
    }
    if(!found) {
        cout << "\n-------------------------------------------------------\n";
        cout << "[ERROR] Product not found.\n";
        cout << "-------------------------------------------------------\n";
    }
}
//-------------------------------UpdateStock-------------------------------

//-------------------------------DeleteStock-------------------------------
void deleteStock(List *ls) {

    if(ls->head == nullptr) {
        cout << "\nNo stock available." << endl;
        return;
    }

    string idSearch;
    char choice;

    cout << "=======================================================\n";
    cout << "                     DELETE STOCK\n";
    cout << "=======================================================\n\n";

    cout << "Enter Product ID: ";
    cin >> idSearch;

    Product *current = ls->head;
    Product *tmp = nullptr;
    bool found = false;

    while(current != nullptr) {
        if(current->Product_ID == idSearch) {
            found = true;
            cout << "\n-------------------------------------------------------\n";
            cout << "Product Information\n";
            cout << "-------------------------------------------------------\n";

            cout << "ID          : " << current->Product_ID << endl;
            cout << "Name        : " << current->Product_Name << endl;
            cout << "Quantity    : " << current->Quantity << endl;
            cout << "Price ($)   : " << current->Unit_Price << endl;

            cout << "-------------------------------------------------------\n";

            cout << "\nConfirm Delete (Y/N): ";
            cin >> choice;
            
            if(choice == 'Y' || choice == 'y') {
                if(tmp == nullptr) {
                    ls->head = ls->head->next;
                } else {
                    tmp->next = current->next;
                }
                delete current;
                ls->n--;

                updateCSVWhenDelete(idSearch);

                cout << "\n-------------------------------------------------------\n";
                cout << "[SUCCESS] Product deleted successfully.\n";
                cout << "-------------------------------------------------------\n";
                return;
            } else {
                cout << "\n-------------------------------------------------------\n";
                cout << "Delete operation cancelled.\n";
                cout << "-------------------------------------------------------\n";
            }
        }
        tmp = current;
        current = current->next;
    }
    if(!found) {
        cout << "\n-------------------------------------------------------\n";
        cout << "[ERROR] Product not found.\n";
        cout << "-------------------------------------------------------\n";
    }
}
//-------------------------------DeleteStock-------------------------------

//-----------------------------GenerateReport------------------------------
void generateReport(List *ls) {

    if(ls->head == nullptr) {
        cout << "No stock available." << endl;
        return;
    }

    Product *tmp = ls->head;

    int totalProducts = 0;
    int totalQuantity = 0;
    float totalValue = 0;

    cout << "======================================================\n";
    cout << "                  INVENTORY REPORT\n";
    cout << "=======================================================\n\n";

    cout << "Product Summary\n";
    cout << "-------------------------------------------------------\n\n";

    while(tmp != nullptr) {
        float value = tmp->Unit_Price * tmp->Quantity;

        cout << tmp->Product_ID
             << "  "
             << tmp->Product_Name
             << "   Quantity: "
             << tmp->Quantity
             << "   Value: $"
             << value
             << endl;

        totalProducts++;
        totalQuantity += tmp->Quantity;
        totalValue += value;
        tmp = tmp->next;
    }

    cout << "\n-------------------------------------------------------\n";
    cout << "Total Products      : " << totalProducts << endl;
    cout << "Total Quantity      : " << totalQuantity << endl;
    cout << "Total Stock Value   : $" << totalValue << endl;

    cout << "\n=======================================================\n";

    cout << "Wish to export as txt (Y/N): ";
    string choose;
    cin >> choose;

    if(choose == "Y"|| choose =="y") {
        cout << "saved as generated_report.txt";
        generateReport(ls, totalProducts, totalQuantity, totalValue);
        cout << "\nDone!" << endl;
    }
    else
        cout << "Exiting to main menu......" <<endl;
}
//-----------------------------GenerateReport------------------------------