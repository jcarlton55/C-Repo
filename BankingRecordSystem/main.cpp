/*
Author : Justin Carlton
Date : 5/30/2021
Purpose : Basic Banking Record System Program
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

class account_query{
    private:
        char accountNumber[20];
        char firstName[10];
        char lastName[10];
        float totalBalance;

    public:
        void showData();
        void writeData();
        void writeRecord();
        void readRecord();
        void searchRecord();
        void editRecord();
        void deleteRecord();

};

void account_query::showData(){
    std::cout << "Account Number: " << accountNumber << std::endl;
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
    std::cout << "\nEnter Balance: ";
    std::cin >> totalBalance;
    std::cout << std::endl;
}

void account_query::writeRecord(){
    std::ofstream outfile;
    outfile.open("record.bank", std::ios::binary|std::ios::app);
    writeData();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}

void account_query::readRecord(){
    std::ifstream infile;
    infile.open("record.bank", std::ios::binary);
    if(!infile){
        std::cout << "Error with opening file! File not found!" << std::endl;
        return;
    }

    std::cout << "\n***Data from file***" << std::endl;
    while (!infile.eof()){
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))){
            showData();
        }
    }
    infile.close();
}

void account_query::searchRecord(){
    int n;
    std::ifstream infile;
    infile.open("record.bank", std::ios::binary);
    if(!infile){
        std::cout << "\nError with opening file! File not found!" << std::endl;
        return;
    }
    infile.seekg(0,std::ios::end);
    int count = infile.tellg()/sizeof(*this);
    std::cout << "\nThere are " << count << " records in the file.";
    std::cout << "\nEnter record number to search for: ";
    std::cin >> n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    showData();
}

void account_query::editRecord(){
    int n;
    std::fstream iofile;
    iofile.open("record.bank", std::ios::in|std::ios::binary);
    if(!iofile){
        std::cout << "\nError with opening file! File not found!" << std::endl;
        return;
    }
    iofile.seekg(0,std::ios::end);
    int count = iofile.tellg()/sizeof(*this);
    std::cout << "\nThere are " << count << " records in the file.";
    std::cout << "\nEnter record number to edit: ";
    std::cin >> n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    showData();
    iofile.close();
    iofile.open("record.bank", std::ios::out|std::ios::in|std::ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    std::cout << "\nEnter data to modify: " << std::endl;
    writeData();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void account_query::deleteRecord(){
    int n;
    std::ifstream infile;
    infile.open("record.bank", std::ios::binary);
    if(!infile){
        std::cout << "\nError with opening file! File not found!" << std::endl;
        return;
    }
    infile.seekg(0,std::ios::end);
    int count = infile.tellg()/sizeof(*this);
    std::cout << "\nThere are " << count << " records in the file. ";
    std::cout << "\nEnter the record number to delete: ";
    std::cin >> n;
    std::fstream tmpfile;
    tmpfile.open("tmpfile.bank", std::ios::out|std::ios::binary);
    infile.seekg(0);
    for(int i = 0; i < count; i++){
        infile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if (i == (n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
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