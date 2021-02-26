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
    if (string(argv[1]) == "-c") // The form is : ./vaccineMonitor -c citizenRecordsFile –b bloomSize
    {
        fileName = argv[2]; // storing the file name in filename variable
        bloomSize = atoi(argv[4]);
    }
    else if (string(argv[3]) == "-c") // The form is : ./vaccineMonitor  –b bloomSize -c citizenRecordsFile
    {
        fileName = argv[4]; // storing the file name in filename variable
        bloomSize = atoi(argv[2]);
    }
    else // The form is not correct
    {
        cout << "Please use the right form for the execution command ! " << endl;
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