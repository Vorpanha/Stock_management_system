#include <iostream>
#include <cscapi.h>
#include <conio.h> 
#include <windows.h>
#include "struct_func.h"
#include "func.h"

using namespace std;

//--aids ui funcs
void decide_to_stop();

int main() {
    for_user_or_admin();
    int choice;

    system("cls"); //to clear any cls in terminal
    
    List *L1 = createEmptyList();

    loadFromCSV(L1);

    while(choice != 7) {
        manu();
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
        }else if(choice==4) {
            updateStock(L1);
            Sleep(1500);
        } else if(choice == 5) {
            deleteStock(L1);
            Sleep(1500);
        } else if(choice == 6) {
            generateReport(L1);
            Sleep(1000);
        } else if(choice == 7) {
            cout << "=======================================================\n";
            cout << "                    EXIT PROGRAM\n";
            cout << "=======================================================\n";
            cout << "\nThank you for using the system.\n";
            cout << "Program terminated successfully.\n";
            cout << "=======================================================\n";
            Sleep(1000);
            exit(0);
        } else {
            cout << "\n-------------------------------------------------------\n";
            cout << "Invalid choice. Please try again.\n";
            cout << "-------------------------------------------------------\n";
            Sleep(500);
        }
        system("cls");
    }
    return 0;
}

void decide_to_stop(){
    cout << "\nPress anykey to exit to main menu.....\n";
    _getch();
}