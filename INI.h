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
    INI(string fileName, int nComment);
    virtual ~INI();
    void checkIsOpen() throw(std::runtime_error);

    const string &getFileName() const;
    void setFileName(const string &fileName);

    int addSection(string section);
    int addParam(string section, string parameter, string value);
    int addComment(string section, string parameter, string comment);

    int deleteSection(string section);
    int deleteParam(string section, string parameter);
    int deleteComment(string section, string parameter);

    int renameSection(string section, string newSection);
    int renameParam(string section, string newParameter, string parameter);
    int changeParam(string section, string value, string parameter);

    void print();
    void reset();

    void end();

private:
    string fileName;
    map<string, map<string,string>> fileINI;
    fstream project;
    int nComment;

    static int errors = 0;
    static int no_errors = 1;
    static int exist = 2;
    int state;
};


#endif //READWRITE_INI_INI_H



