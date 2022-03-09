//
// Created by admin on 22/02/2022.
//

#ifndef READWRITE_INI_INI_H
#define READWRITE_INI_INI_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

class INI{
public:
    INI(const string &fileName);

    int errors = 0;
    int no_errors = 1;
    int exist = 2;
    int state;

    const string &getFileName() const;

    int addSection(const string &section);
    int addParam(const string &section, const string &parameter, const string &value);
    int addComment(const string &section,const string &parameter, const string &comment);
    int addComment(const string &section, const string &comment);

    int deleteSection(const string &section);
    int deleteParam(const string &section, const string &parameter);

    int renameSection(const string &section, const string &newSection);
    int renameParam(const string &section, const string &newParameter, const string &parameter);
    int changeParam(const string &section, const string &value, const string &parameter);

    void printSections();
    void printParameters(const string &section);
    void printValue(const string &section, const string &parameter);
    void printAll();

    void reset();

    virtual ~INI();
private:
    string fileName;
    map<string, map<string,string>> fileINI;
    fstream project;
    void analyze();
};


#endif //READWRITE_INI_INI_H



