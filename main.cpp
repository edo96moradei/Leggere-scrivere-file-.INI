#include <iostream>

#include"INI.h"

using namespace std;

int main() {
    INI fileINI("ListinoCD.ini");
    cout<<"NOME FILE: "<< fileINI.getFileName()<<endl;

    fileINI.addSection("BLUES"); //sezione [BLUES]
    fileINI.addParam("BLUES", "ERIC CLAPTON", "5"); //Aggiungo CD alla nuova sezione
    fileINI.addComment("BLUES","ERIC CLAPTON", " 'Soprannominato SlowHand e' tra i chitarristi blues piu' famosi e influenti...'");
    fileINI.addComment("CLASSICAL","'Offerta CD genere CLASSICAL'");

    fileINI.renameSection("BLUES", "FOLK-BLUES");
    fileINI.changeParam("FOLK-BLUES", "33", "ERIC CLAPTON");
    fileINI.deleteSection("BLUES");

    cout<<"******************STAMPA****************************"<<endl;

    //fileINI.printSections();
    //fileINI.printParameters("JAZZ");
    fileINI.printAll();
    return 0;
}