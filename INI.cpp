//
// Created by admin on 15/12/2021.
//

#include <iostream>
#include "INI.h"

INI::INI(string fileName, int nComment) {
    this->fileName = fileName;
    this->project.open(fileName);
    this->nComment = nComment;
}

INI::~INI() {
    this->project.close();
}

void INI::checkIsOpen() {
    if(!project.is_open()){
        throw std::runtime_error("file inesistente");
    }
}

const string &INI::getFileName() const {
    return fileName;
}

void INI::setFileName(const string &fileName) {
    INI::fileName = fileName;
}

int INI::addSection(string section) {
    auto itr = fileINI.find(section); //l'iteratore va all'elemento section
    if(itr == fileINI.end()) {
        fileINI[section].insert(make_pair("", ""));
        state = no_errors;
    }else{
        state = exist;
    }
    return state;
}

int INI::addParam(string section, string parameter, string value) {
    try {
        auto itr = fileINI.at(section).insert(make_pair(parameter, value)); //accedo all'elemento e inserisco la coppia ( , )
        state = no_errors;
    }catch(out_of_range e){
        std::cout<<"Tentativo di accedere ad elementi fuori range"<<std::endl;
        state = errors;
    }
    return state;
}

int INI::addComment(string section, string parameter, string comment) {
    try {
        state = errors;
        auto position = fileINI.at(section).find(parameter);
        if(position != fileINI.at(section).end()){
            string str(parameter);
            str.pop_back();
            state = addParam(section, str, "," +comment);
        }else{
            state = errors;
        }
    }catch(out_of_range e){
        std::cout<<"Tentativo di accedere ad elementi fuori range"<<std::endl;
        state = errors;
    }
    return state;
}

int INI::deleteSection(string section) {
    return 0;
}

int INI::deleteParam(string section, string parameter) {
    return 0;
}

int INI::deleteComment(string section, string parameter) {
    return 0;
}






