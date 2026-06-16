///---here only for the function only
#pragma once
#include <iostream>
#include <string>
#include <cscapi.h>
#include <windows.h>
#include "stream.h"
#include "struct_func.h"
#include <iomanip>

using namespace std;

bool is_duplicated(string ID);
string reEnterID(string new_id, string statement);

//-------------------------------------Exit-------------------------------------
void Exit() {
    cout << "\n=====================================================================\n";
    cout << "                            EXIT PROGRAM\n";
    cout << "=====================================================================\n\n";

    cout << "Thank you for using the Stock Inventory System.\n";
    cout << "Program terminated successfully.\n\n";

    cout << "---------------------------------------------------------------------\n";
    cout << "Status : Closed\n";
    cout << "---------------------------------------------------------------------\n";

    Sleep(1000);
    exit(0);
}
//-------------------------------------Exit--------------------------------------

//-------------------------------------LoginPortal--------------------------------------
void for_user_or_admin() {
    cout << "\n=====================================================================\n";
    cout << "                             LOGIN PORTAL\n";
    cout << "=====================================================================\n\n";

    cout << "  [1] Administrator\n";
    cout << "  [2] User\n";
    cout << "  [0] Exit Program\n\n";

    cout << "---------------------------------------------------------------------\n";
    cout << "Select your role : ";
}
//-------------------------------------LoginPortal--------------------------------------

//----------------------------------Admin Menu-----------------------------------
void manuforAdmin() {
    cout << "\n=====================================================================\n";
    cout << "                 STOCK INFORMATION MANAGEMENT SYSTEM\n";
    cout << "=====================================================================\n\n";

    cout << "  [1] Add Stock Item\n";
    cout << "  [2] Display All Stocks\n";
    cout << "  [3] Search Stock\n";
    cout << "  [4] Update Stock\n";
    cout << "  [5] Delete Stock\n";
    cout << "  [6] Generate Report\n";
    cout << "  [7] Back to Operator\n";
    cout << "  [0] Exit Program\n\n";

    cout << "---------------------------------------------------------------------\n";
    cout << "Enter your choice : ";
}
//----------------------------------Admin Menu-----------------------------------

//----------------------------------User Menu-----------------------------------
void manuforUser() {
    cout << "\n=====================================================================\n";
    cout << "                 STOCK INFORMATION MANAGEMENT SYSTEM\n";
    cout << "=====================================================================\n\n";

    cout << "  [1] Display All Stocks\n";
    cout << "  [2] Search Stock\n";
    cout << "  [3] Generate Report\n";
    cout << "  [0] Exit Program\n\n";

    cout << "---------------------------------------------------------------------\n";
    cout << "Enter your choice : ";
}
//----------------------------------User Menu-----------------------------------

//--------------------------------AddStock---------------------------------
string reEnterID(string new_id){
    system("cls");
    cout << "---------------------------------------------------------------------\n";
    cout << "                     ID ALREADY EXISTS\n";
    cout << "                     PLEASE TRY AGAIN\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Product ID (Ex: E001) : ";
    cin >> new_id;

    
    string tmpName,tmpID;
    int tmpQuantity;
    float tmpPrice;
    
    List *ls = createEmptyList();
    loadFromCSV(ls);
    Product *ptmp = ls->head;
    
    while(ptmp != nullptr) {
        if(new_id == ptmp->Product_ID) {
            cout<<"Comparing.....";
            Sleep(150);
            return reEnterID(new_id);
        }
        ptmp = ptmp->next;
    }

    cout << "=======================================================\n";
    cout << "                    ADD STOCK ITEM\n";
    cout << "=======================================================\n\n";
    
    return new_id;
}

bool is_duplicated(string ID){
    List *ls = createEmptyList();
    loadFromCSV(ls);
    Product *ptmp = ls->head;

    while(ptmp != nullptr){
        if(ptmp->Product_ID == ID){
            return true;
            break;
        }
        ptmp = ptmp->next;
    }

    delete ptmp, ls;
    return false;
}

void addStock(List *ls) {

    cout << "\n=====================================================================\n";
    cout << "                          ADD STOCK ITEM\n";
    cout << "=====================================================================\n\n";

    string tmpName, tmpID;
    int tmpQuantity;
    float tmpPrice;

    cout << "Product ID (Ex: E001) : ";
    cin >> tmpID;

    if(is_duplicated(tmpID)) {
        tmpID = reEnterID(tmpID);
    }

    cin.ignore();
    cout << "Product Name         : ";
    getline(cin, tmpName);
    cout << "Quantity             : ";
    cin >> tmpQuantity;
    cout << "Unit Price           : ";
    cin >> tmpPrice;
    
    Product* New_product = new Product{tmpID,tmpName,tmpQuantity,tmpPrice,nullptr};
    
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

    cout << "\n---------------------------------------------------------------------\n";
    cout << "                 PRODUCT ADDED SUCCESSFULLY\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Data saved to Stock_info.csv\n";
    cout << "---------------------------------------------------------------------\n";
}
//--------------------------------AddStock---------------------------------

//-------------------------------------DisplayStock--------------------------------------
void displayStock(List *ls) {
    if(ls->head == nullptr) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     NO STOCK AVAILABLE\n";
        cout << "---------------------------------------------------------------------\n";
        return;
    }

    Product *current = ls->head;
    int totalQuantity = 0;

    cout << "\n=====================================================================\n";
    cout << "                          STOCK INVENTORY\n";
    cout << "=====================================================================\n\n";

    cout << left
         << setw(13) << "Product ID" << "| "
         << setw(23) << "Product Name" << "| "
         << setw(13) << "Quantity" << "| "
         << "Unit Price" << endl;

    cout << "---------------------------------------------------------------------\n";

    while(current != NULL) {
        cout << left
             << setw(13) << current->Product_ID << "| "
             << setw(23) << current->Product_Name << "| "
             << setw(13) << current->Quantity << "| $"
             << current->Unit_Price << endl;

        totalQuantity += current->Quantity;
        current = current->next;
    }

    cout << "---------------------------------------------------------------------\n\n";

    cout << "Inventory Summary\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Records Found : " << ls->n << endl;
    cout << "Total Quantity: " << totalQuantity << endl;
    cout << "---------------------------------------------------------------------\n";
}
//-------------------------------------DisplayStock--------------------------------------

//-------------------------------------SearchStock--------------------------------------
void searchStock(List *ls) {
    if(ls->head == nullptr) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     NO STOCK AVAILABLE\n";
        cout << "---------------------------------------------------------------------\n";
        return;
    }

    cout << "\n=====================================================================\n";
    cout << "                           SEARCH STOCK\n";
    cout << "=====================================================================\n\n";

    string searchName;
    cout << "Enter Product Name to Search : ";
    cin.ignore();
    getline(cin, searchName);

    Product *temp = ls->head;
    bool found = false;

    while(temp != nullptr) {
        string lettre_1 = temp->Product_Name.substr(0,searchName.length());
        string lettre_2 = searchName.substr(0,searchName.length());

        //covert to lower case
        for(char &character: lettre_1)
            character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
        for(char &character: lettre_2)
            character = static_cast<char>(tolower(static_cast<unsigned char>(character)));

        if(lettre_1 == lettre_2) {
            cout << "\n---------------------------------------------------------------------\n";
            cout << "                        PRODUCT INFORMATION\n";
            cout << "---------------------------------------------------------------------\n";

            cout << "Product ID   : " << temp->Product_ID << endl;
            cout << "Product Name : " << temp->Product_Name << endl;
            cout << "Quantity     : " << temp->Quantity << endl;
            cout << "Unit Price   : $" << temp->Unit_Price << endl;

            cout << "---------------------------------------------------------------------\n";
            found = true;
        }
        temp = temp->next;
    }

    if(!found) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                    PRODUCT NOT FOUND\n";
        cout << "---------------------------------------------------------------------\n";
    }
}
//-------------------------------------SearchStock--------------------------------------

//-------------------------------UpdateStock-------------------------------
void updateStock(List* ls) {
    if(ls->head == nullptr) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     NO STOCK AVAILABLE\n";
        cout << "---------------------------------------------------------------------\n";
        return;
    }

    cout << "\n=====================================================================\n";
    cout << "                           UPDATE STOCK\n";
    cout << "=====================================================================\n\n";

    string searchID;
    bool found = false;
    cout << "Enter Product ID to Update : ";
    cin >> searchID;

    
    Product *temp = ls->head;

    while(temp != nullptr) {
        if(temp->Product_ID == searchID) {
            cout << "\n---------------------------------------------------------------------\n";
            cout << "                     CURRENT PRODUCT INFORMATION\n";
            cout << "---------------------------------------------------------------------\n";

            cout << "Product ID   : " << temp->Product_ID << endl;
            cout << "Product Name : " << temp->Product_Name << endl;
            cout << "Quantity     : " << temp->Quantity << endl;
            cout << "Unit Price   : $" << temp->Unit_Price << endl;

            cout << "---------------------------------------------------------------------\n\n";

            cin.ignore();
            cout << "New Product Name : ";
            getline(cin, temp->Product_Name);
            cout << "New Quantity     : ";
            cin >> temp->Quantity;
            cout << "New Unit Price   : ";
            cin >> temp->Unit_Price;
            
            updateCSV(searchID,temp);

            cout << "\n---------------------------------------------------------------------\n";
            cout << "                 PRODUCT UPDATED SUCCESSFULLY\n";
            cout << "                 Data saved to Stock_info.csv\n";
            cout << "---------------------------------------------------------------------\n";

            found = true;
            return;
        }
        temp = temp->next;
    }
    if(!found) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     PRODUCT NOT FOUND\n";
        cout << "---------------------------------------------------------------------\n";
    }
}
//-------------------------------UpdateStock-------------------------------

//-------------------------------DeleteStock-------------------------------
void deleteStock(List *ls) {
    if(ls->head == nullptr) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     NO STOCK AVAILABLE\n";
        cout << "---------------------------------------------------------------------\n";
        return;
    }

    displayStock(ls);

    string idSearch;
    char choice;

    cout << "\n=====================================================================\n";
    cout << "                           DELETE STOCK\n";
    cout << "=====================================================================\n\n";

    cout << "Enter Product ID : ";
    cin >> idSearch;

    Product *current = ls->head;
    Product *tmp = nullptr;
    bool found = false;

    while(current != nullptr) {
        if(current->Product_ID == idSearch) {
            found = true;

            cout << "\n---------------------------------------------------------------------\n";
            cout << "                     PRODUCT INFORMATION\n";
            cout << "---------------------------------------------------------------------\n";

            cout << "Product ID   : " << current->Product_ID << endl;
            cout << "Product Name : " << current->Product_Name << endl;
            cout << "Quantity     : " << current->Quantity << endl;
            cout << "Unit Price   : $" << current->Unit_Price << endl;

            cout << "---------------------------------------------------------------------\n";

            cout << "\nConfirm Delete (Y/N) : ";
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

                cout << "\n---------------------------------------------------------------------\n";
                cout << "                 PRODUCT DELETED SUCCESSFULLY\n";
                cout << "---------------------------------------------------------------------\n";

                return;
            } else {
                cout << "\n---------------------------------------------------------------------\n";
                cout << "                  DELETE OPERATION CANCELLED\n";
                cout << "---------------------------------------------------------------------\n";
            }
        }

        tmp = current;
        current = current->next;
    }

    if(!found) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     PRODUCT NOT FOUND\n";
        cout << "---------------------------------------------------------------------\n";
    }
}
//-------------------------------DeleteStock-------------------------------

//--------------------------------GenerateReport-------------------------------
void generateReport(List *ls) {
    if(ls->head == nullptr) {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "                     NO STOCK AVAILABLE\n";
        cout << "---------------------------------------------------------------------\n";
        return;
    }

    Product *tmp = ls->head;

    int totalProducts = 0;
    int totalQuantity = 0;
    float totalValue = 0;

    cout << "\n=====================================================================\n";
    cout << "                         INVENTORY REPORT\n";
    cout << "=====================================================================\n\n";

    cout << left
         << setw(13) << "Product ID" << "| "
         << setw(23) << "Product Name" << "| "
         << setw(13) << "Quantity" << "| "
         << "Unit Price" << endl;

    cout << "---------------------------------------------------------------------\n";

    while(tmp != nullptr) {
        float value = tmp->Unit_Price * tmp->Quantity;

        cout << left
             << setw(13) << tmp->Product_ID << "| "
             << setw(23) << tmp->Product_Name << "| "
             << setw(13) << tmp->Quantity << "| $"
             << value << endl;

        totalProducts++;
        totalQuantity += tmp->Quantity;
        totalValue += value;
        tmp = tmp->next;
    }

    cout << "---------------------------------------------------------------------\n\n";

    cout << "Inventory Summary\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Records Found : " << totalProducts << endl;
    cout << "Total Quantity: " << totalQuantity << endl;
    cout << "Total Value   : $" << totalValue << endl;
    cout << "---------------------------------------------------------------------\n";

    cout << "\nExport Report\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Wish to export as TXT (Y/N) : ";

    string choose;
    cin >> choose;

    if(choose == "Y" || choose == "y") {

        cout << "\n---------------------------------------------------------------------\n";
        cout << "Saving report to generated_report.txt...\n";

        generateReport(ls, totalProducts, totalQuantity, totalValue);

        cout << "Report exported successfully.\n";
        cout << "---------------------------------------------------------------------\n";

    } else {
        cout << "\n---------------------------------------------------------------------\n";
        cout << "Returning to main menu...\n";
        cout << "---------------------------------------------------------------------\n";
    }
}
//--------------------------------GenerateReport-------------------------------