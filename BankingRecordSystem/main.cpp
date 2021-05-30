/*
Author : Justin Carlton
Date : 5/30/2021
Purpose : Basic Banking Record System Program
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

class account_query
{
    private:
        char accountNumber[20];
        char firstName[10];
        char lastName[10];
        float totalBalance;

    public:
        void showData();
        void rwriteData();
        void writeRecord();
        void readRecord();
        void searchRecord();
        void editRecord();
        void deleteRecord();

};

void account_query::showData(){
    std::cout << "Account Number: " << AccountNumber << std::endl;
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "Current Balance: " << totalBalance << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
}

void account_query::writeData(){
    std::cout << "\nEnter Account Number: ";
    std::cin >> accountNumber;
    std::cout << "\nEnter First Name: ";
    std::cin >> firstName;
    std::cout << "\nEnter Last Name: ";
    std::cin >> lastName;
    std::cout << "Enter Balance: ";
    std::cin >> totalBalance;
    std::cout << std::endl;
}

int main(){
    account_query A;
    int choice;
    std::cout << "***Account Information System***" << std::endl;
    while(true){
        std::cout << "Select one option below: ";
        std::cout << "\n\t1--> Add record to file";
        std::cout << "\n\t2--> Show record from file";
        std::cout << "\n\t3--> Search Record from file";
        std::cout << "\n\t4--> Update Record";
        std::cout << "\n\t5--> Delete Record";
        std::cout << "\n\t6--> Quit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        
        switch(choice){
            case 1:
                A.writeRecord();
                break;
            case 2:
                A.readRecord();
                break;
            case 3:
                A.searchRecord();
                break;
            case 4:
                A.editRecord();
                break;
            case 5:
                A.deleteRecord();
                break;
            case 6:
                exit(0);
                break;
            default:
                std::cout << "\nEnter one of the options provided.";
                exit(0);
        }
    }

    system("pause");
    return 0;
}