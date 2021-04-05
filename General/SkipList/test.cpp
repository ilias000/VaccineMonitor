#include <iostream>

#include "../LinkedList/LinkedListString/LinkedListString.h"
#include "SkipList.h"

using namespace std;

int main(int argc, char* argv[])
{
    LinkedListString* viruses = new LinkedListString();
    viruses->insertNode("ilias");
    viruses->insertNode("nikola");
    SkipList* skiplist = new SkipList(viruses->findNode("ilias"));
    skiplist->insertVirus(viruses->findNode("nikola"));


    skiplist->findVirus("ilias")->insertNodeVaccinated(5);

    skiplist->findVirus("ilias")->insertNodeVaccinated(6);

    skiplist->findVirus("nikola")->insertNodeVaccinated(7);

    skiplist->findVirus("nikola")->insertNodeVaccinated(8);


    skiplist->findVirus("nikola")->printVaccinated();
    skiplist->findVirus("ilias")->printVaccinated();

    delete skiplist;
    delete viruses;
    return 0;
}