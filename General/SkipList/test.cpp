#include <iostream>

#include "SkipList.h"

using namespace std;

int main(int argc, char* argv[])
{
    LinkedListString* viruses = new LinkedListString();
    viruses->insertNode("ilias");
    SkipList* skiplist = new SkipList(viruses->findNode("ilias"));
    SkipList* vac = skiplist->getVaccinated(viruses->findNode("ilias"));
    SkipList* nvac = skiplist->getNonVaccinated(viruses->findNode("ilias"));

    vac->add(0);
    nvac->add(1);
    vac2->add(3);
    nvac2->add(4);
    vac->print();
    nvac->print();
    vac2->print();
    nvac2->print();
    cout << endl;
    delete skiplist;
    delete viruses
        return 0;
}