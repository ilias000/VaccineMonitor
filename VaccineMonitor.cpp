#include <string>
#include <fstream>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "                             --- THE VACCINE MONITOR PROGRAM STARTED ---                                 " << endl;
    string extensionOfFileName = (".txt");
    string fileName;
    int bloomSize;
    string line; // will store one line of the file each time

    ifstream name;

    if (argc < 5)
    {
        cout << "Gamiese" << endl;
        return 0;
    }

    if (!(string(argv[1]).compare("-c")) && !(string(argv[3]).compare("-b"))) // The form is : ./vaccineMonitor -c citizenRecordsFile –b bloomSize
    {
        fileName = argv[2]; // storing the file name in filename variable
        bloomSize = atoi(argv[4]);
        cout << "test1" << endl;
    }
    else if (!(string(argv[3]).compare("-c")) && !(string(argv[1]).compare("-b"))) // The form is : ./vaccineMonitor  –b bloomSize -c citizenRecordsFile
    {
        fileName = argv[4]; // storing the file name in filename variable
        bloomSize = atoi(argv[2]);
        cout << "test2" << endl;
    }
    else // The form is not correct
    {
        cout << "Please use the right form for the execution command ! " << endl;
        cout << "test3" << endl;
        return 0;
    }

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