#include <string>
#include <fstream>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "                             --- THE VACCINE MONITOR PROGRAM STARTED ---                                 " << endl;
    // ifstream file(argv[2]); // opening the file
    // string line;            // will store one line of the file each time

    // while (getline(file, line)) // while we have lines in the file, get the line and store it in the variable line
    // {
    //     // process string ...
    //     cout << line << endl;
    // }
    string extensionOfFileName = (".txt");
    string fileName;
    string line; // will store one line of the file each time

    ifstream name;
    fileName = argv[2];                   // storing the file name in filename variable
    fileName.append(extensionOfFileName); // adding extension to the filename
    name.open(fileName);

    while (getline(name, line)) // while we have lines in the file, get the line and store it in the variable line
    {
        // process string ...
        cout << line << endl;
    }

    cout << "                             --- THE VACCINE MONITOR PROGRAM ENDED ---                                 " << endl;

    return 0;
}