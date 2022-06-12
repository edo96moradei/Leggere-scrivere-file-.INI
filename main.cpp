#include <iostream>

#include"INI.h"

using namespace std;

int main() {
    INI fileINI("ListinoCD.ini", 1000);
    cout<<"NOME FILE: "<< fileINI.getFileName()<<endl;

    fileINI.addSection("BLUES");
    fileINI.addParam("BLUES", "ERIC CLAPTON", "5");
    fileINI.addComment("BLUES","ERIC CLAPTON", "'Soprannominato SlowHand e' tra i chitarristi blues piu' famosi e influenti...'");
    fileINI.addComment("CLASSICAL", "'Offerta CD genere CLASSICAL'");

    fileINI.renameParam("BLUES", "ERIC CLAPTON 'SLOWHAND'", "ERIC CLAPTON");
    fileINI.renameSection("BLUES", "FOLK-BLUES");
    fileINI.changeParam("FOLK-BLUES", "33", "ERIC CLAPTON");
    fileINI.deleteSection("BLUES");
    cout<<" "<<endl;

    cout<<"******************STAMPA MODIFICHE FILE.ini****************************"<<endl;

    cout<<" "<<endl;
    fileINI.printModifications();
    return 0;
}