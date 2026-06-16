#include <iostream>
#include <cscapi.h>
#include <conio.h> //used for press any key fun which it call _getch()
#include <windows.h>
#include "header/struct_func.h"
#include "header/stream.h"
#include "header/func.h"

using namespace std;

//--aids ui funcs
void decide_to_stop();
void handle_miss_input(List *L1);
void for_admin(List *L1);
void for_user(List *L1);

int main() {
    
    system("cls"); //to cls any cls in terminal
    
    List *L1 = createEmptyList();

    loadFromCSV(L1);
    handle_miss_input(L1);
}

void handle_miss_input(List *L1) {
    int choice;
    for_user_or_admin();
    cin>>choice;
    switch(choice){
        case 1:
            system("cls");
            for_admin(L1);
        break;
        case 2:
            system("cls");
            for_user(L1);
            break;
        case 0:
            system("cls");
            Exit();
        break;
        default:
            cout<<"Invalid choice!";
            Sleep(1000);
            system("cls");
            handle_miss_input(L1);
        break;
    }
}

void for_admin(List *L1) {
    int choice = -1;
    while(choice != 0) {
        manuforAdmin();
        cin >> choice;
        system("cls");
        if(choice == 1) {
            addStock(L1);
            Sleep(500);
        } else if(choice == 2) {
            displayStock(L1);
            decide_to_stop();
        } else if(choice == 3) {
            searchStock(L1);
            decide_to_stop();
        } else if(choice==4) {
            updateStock(L1);
            Sleep(1500);
        } else if(choice == 5) {
            deleteStock(L1);
            Sleep(1500);
        } else if(choice == 6) {
            generateReport(L1);
            Sleep(1000);
        } else if(choice == 7) {
            handle_miss_input(L1);
            Sleep(1000);
        } else if(choice == 0) {
            Exit();
        } else {
            cout << "\n-------------------------------------------------------\n";
            cout << "Invalid choice. Please try again.\n";
            cout << "-------------------------------------------------------\n";
            Sleep(500);
        }
        system("cls");
    }
}

void for_user(List *L1) {
    int choice = -1;
    while(choice != 0) {
        manuforUser();
        cin >> choice;
        system("cls");
        if(choice == 1) {
            displayStock(L1);
            decide_to_stop();
        } else if(choice == 2) {
            searchStock(L1);
            decide_to_stop();
        } else if(choice == 3) {
            generateReport(L1);
            Sleep(1000);
        } else if(choice == 0) {
            Exit();
        } else {
            cout << "\n-------------------------------------------------------\n";
            cout << "Invalid choice. Please try again.\n";
            cout << "-------------------------------------------------------\n";
            Sleep(500);
        }
        system("cls");
    }
}


void decide_to_stop() {
    cout << "\nPress anykey to exit to main menu.....\n";
    _getch();
}