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
    convert.read_file("");
    cout << "\r";
    cout << "Read done!     \n";


    cout << "get Picture ...";
    mask.get(convert);
    cout << "\r";
    cout << "get done!          \n";


    cout << "Using black_white...";
    mask.black_white();
    cout << "\r";
    cout << "Black_white done!      \n";


    cout << "Transfer data...";
    mask.transfer(convert);
    cout << "\r";
    cout << "Transfer done!     \n";


    cout << "Dice count: \n";
    mask.Black_percentage();
 
    
    
    cout << "Write file...";
    convert.write_file();
    cout << "\r";
    cout << "Write done!        \n";


    _getch();

}