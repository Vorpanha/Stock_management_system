#include <iostream>
#include <cscapi.h>
#include <conio.h> //used for press any key fun which it call _getch()
#include <windows.h>
#include "../header/struct_func.h"
#include "../header/stream.h"
#include "../header/func.h"
#include "../header/ui_controller.h"


void load_ui_elements() {
      
    system("cls"); //to cls any cls in terminal
    
    List *L1 = createEmptyList();

    loadFromCSV(L1);
    handle_miss_input(L1);
}

void handle_miss_input(List *L1) {
    string choice;
    for_user_or_admin();
    cin>>choice;
    while(1) {
        if(choice =="1") {
            system("cls");
            for_admin(L1);
        }
        else if(choice == "2") {
            system("cls");
            for_user(L1);
        } else if(choice == "0") {
            system("cls");
            Exit();
            break;
        } else {
            error_pop_up();
            Sleep(1000);
            system("cls");
            handle_miss_input(L1);
        }
    }
}

void for_admin(List *L1) {
    string choice = "-1";
    while(1) {
        manuforAdmin();
        cin >> choice;
        system("cls");
        if(choice == "1") {
            addStock(L1);
            decide_to_stop();
        } else if(choice == "2") {
            displayStock(L1);
            decide_to_stop();
        } else if(choice == "3") {
            searchStock(L1);
            decide_to_stop();
        } else if(choice == "4") {
            updateStock(L1);
            decide_to_stop();
        } else if(choice == "5") {
            deleteStock(L1);
            decide_to_stop();
        } else if(choice == "6") {
            generateReport(L1);
            Sleep(1000);
        } else if(choice == "7") {
            handle_miss_input(L1);
            decide_to_stop();
        } else if(choice == "0") {
            Exit();
            break;
        } else {
            error_pop_up();
            Sleep(500);
        }
        system("cls");
    }
    Exit();
}

void for_user(List *L1) {
    string choice = "-1";
    while(1) {
        manuforUser();
        cin >> choice;
        system("cls");
        if(choice == "1") {
            displayStock(L1);
            decide_to_stop();
        } else if(choice == "2") {
            searchStock(L1);
            decide_to_stop();
        } else if(choice == "3") {
            generateReport(L1);
            Sleep(1000);
        } else if(choice == "0") {
            Exit();
            break;
        } else {
            error_pop_up();
            Sleep(500);
        }
        system("cls");
    }
    Exit();
}

void error_pop_up(){
    cout << "\n-------------------------------------------------------\n";
    cout << "[ERROR] Please try again!\n";
    cout << "-------------------------------------------------------\n";
}

void decide_to_stop() {
    cout << "\nPress anykey to exit to main menu.....\n";
    _getch();
}