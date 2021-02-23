#include <string>
#include <fstream>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "                             --- THE VACCINE MONITOR PROGRAM STARTED ---                                 " << endl;
    ifstream file(argv[2]);
    string line;
    while (getline(file, line))
    {
        // process string ...
        cout << line << endl;
    }
    cout << "                             --- THE VACCINE MONITOR PROGRAM ENDED ---                                 " << endl;

    return 0;
}