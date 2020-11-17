#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h> // For WaitKey() function
//#include <iomanip>
//#include "termcolor/termcolor.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;



//define our structure
struct cars_brand{
    //std::string fName{};    //tutaj bedzie nazwa naszej marki
    //define constructor of our structure
    cars_brand(std::string b,std::string s, int p, int c) {
        fBrand = b;
        fModel = s;
        power = p;
        capacity = c;

    }
    //data in our structure
    std::string fBrand{};   //Name of car brand
    std::string fModel{};   //Name of car model
    int power{0};           //numer of horsepower
    int capacity{ 0 };      //size engine of our car
    cars_brand() = default;
};

//define vector of our structure //and get two example 
vector<cars_brand> Car{
       {"Subaru","Impreza", 150,1997},
       {"Subaru","Forester",147,1998}

};

//display our vector of structure
void print_struct(vector <cars_brand> &car) {
    for (auto Cars : car) {
        cout << "Marka: " << Cars.fBrand << " ";
        cout << "Model: " << Cars.fModel << " ";
        cout << "KM: " << Cars.power << " ";
        cout << "Pojemnosc: " << Cars.capacity << " ";
        cout<<endl;
    }


}
//deete element from our vector, 
void delete_element(vector <cars_brand>& car) {
    cout << "Which element may you delete ";
    int n{};
    cin >> n;
    n = n - 1;//because we iterated vector from 0;
    car.erase(car.begin() + n, car.begin() +n+1); // Usuñ indeksy 2, 3

    cout << "The " << n + 1 << " was deleted" << endl;

}

//add new element in vector, we fill all of our structure.
void load_element(vector <cars_brand>& car) {
    
    std::string brand{};
    std::string model{};
    int power{};
    int engine_capacity{};

    cout << "Added new car: " << endl;

    cout << "Brand: ";
    cin >> brand;

    cout << "Model: ";
    cin >> model;

    cout << "Power(KM): ";
    cin >> power;

    cout << "Capacity(cm3): ";
    cin >> engine_capacity;

    car.push_back(cars_brand(brand, model, power, engine_capacity));

}

std::ostream& operator<<(std::ostream& os, const cars_brand& s) {
    os << "Marka: " << s.fBrand
        << " Model: " << s.fModel
        << " Power: " << s.power
        << " Capacity(cm3): " << s.capacity << "\n";
        


    return os;
}

std::istringstream& operator >>(std::istringstream& is, cars_brand& s) {

    std::string other[4];
    
    
    is >> other[0] >> s.fBrand >> other[1] >> s.fModel >> other[2] >> s.power >> other[3] >> s.capacity;
    
    return is;

}

void save_to_file(vector<cars_brand>& Cars) {
    std::ofstream outFile;
    outFile.open("struktura.txt", std::ios::out); //Saving as
    if (outFile.is_open())
    {
        for (int index = 0; index < Cars.size(); index++) {
            outFile << Cars[index];

        }

        outFile.close();
    }


}
void read_from_file(vector<cars_brand>& Cars) {
    std::ifstream inFile;
    inFile.open("model.txt", std::ios::in); //read from file
    if (inFile.is_open()) {
        cout << "File is open\n";
        std::string linia;
        while(std::getline(inFile,linia)){
            std::istringstream iss(linia);
            cars_brand s;
           

            iss >> s;
            Cars.push_back(s);

        }
        inFile.close();


    }

}
//here we geet size of our console, because I want display Main Menu in the center of console
int get_console_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int col, row;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    col = csbi.srWindow.Right - csbi.srWindow.Left + 1; //we 
    row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return row, col;
}
//fucntion which is responsibility for display our menu
void print_menu() {
    //create vector with element of our menu
    std::vector<std::string> menu;
    menu.push_back("Main Menu\n");
    menu.push_back("*");
    menu.push_back("1.Read from file\n");
    menu.push_back("2.Save to file\n");
    menu.push_back("3.Display\n");
    menu.push_back("4.Add cars\n");
    menu.push_back("5.Delete cars\n");
    menu.push_back("6.Exit\n");
    
    int col, row;
    //get size of our console and save to row and col
    row, col = get_console_size(); //get size from windows;

    
    std::vector<int> size_text_vector;
    for (int i = 0; i < menu.size(); i++) {
        size_text_vector.push_back(menu[i].size());
    }
    //display menu in center of console
    std::cout.width((col / 2) + size_text_vector[0] / 2);
    std::cout << std::right << menu[0];

    const char* star = const_cast<char*>(menu[1].c_str());
    std::cout << std::string(col, *star) << std::endl;

    for (int i = 2; i < menu.size(); i++) {
        cout << menu[i];
    }




}
//the function is resposibility for get char from keyborad and run the option which user choose.
void choose_menu() {

    int wybor{};


    for (;;) {
        
        print_menu();
        
        wybor = _getch();
        system("cls");
            switch (wybor) {
            case '1':
                cout << "Read from file\n";
                read_from_file(Car);
                break;

            case '2':
                cout << "Read from file\n";
                save_to_file(Car);
                break;

            case '3':
                cout << "Display cars\n";
                print_struct(Car);
                break;

            case '4':
                cout << "Add new cars\n";
                load_element(Car);

                break;

            case '5':
                cout << "Delete cars\n";
                delete_element(Car);
                break;
            case '6':
                cout << "Exit\n";
                Sleep(1500);
                exit(0);
                break;
            
                
                //default: cout << "No menu options!\n";
                    //break;

            }
        


        //system("cls");
    }




}





int main(){
    

    //run our program
    choose_menu();


return 0;
}
    


