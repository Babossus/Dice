#include <conio.h>
#include <iostream>

#include "read_write.cpp"
#include "filter.cpp"

using namespace std;

int main() {
    // vorbereiten
    convert convert;
    mask mask;

    // Durchlauf
    cout << "Read file...";
    convert.read_file();
    cout << "\r";
    cout << "Read done!     \n";

    
    cout << "Using Cournal...";
    mask.curnal(convert);
    std::cout << "\r";
    cout << "Cournal done!      \n";
    
    /*
    cout << "Using black_white";
    mask.black_white();
    std::cout << "\r";
    cout << "Black_white done!      \n";
    */
    
    cout << "Transfer data...";
    mask.transfer(convert);
    std::cout << "\r";
    cout << "Transfer done!     \n";
    

    cout << "Write file...";
    convert.write_file();
    std::cout << "\r";
    cout << "Write done!        \n";


    _getch();

}