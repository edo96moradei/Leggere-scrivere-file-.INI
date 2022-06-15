//
// Created by admin on 15/12/2021.
//

#include <iostream>
#include "INI.h"

INI::INI(const string &fn, int nChar){
    fileName = fn;
    string section;
    string comment;
    char lineChar[nChar];
    project.open(fileName, ios::in); //operazione di lettura da un flusso
    if(project.is_open()) {
        string stringa(lineChar);
        while (!project.eof()) { //eof: end-of-file
            project.getline(lineChar, 1000);
            switch (lineChar[0]) {
                case '[': {
                    section = lineChar;
                    section.erase(section.begin());
                    addSection(section);
                    break;
                }
                case ';': {
                    comment = lineChar;
                    comment.erase(comment.begin());
                    break;
                }
                default: { //non ho nè un commento nè una sezione -> leggo un parametro
                    auto position = stringa.find('=');
                    string parametro(stringa, 0, position); //costruttore stringa da 0 a '='
                    string valore(stringa, position + 1, string::npos); //costruttore stringa da '=' a fine stinga
                    if (stringa.length() > 0)
                        addParam(parametro, valore, section);
                    break;
                }
            }
        }
    }
    project.close();
}

INI::~INI() {
}

const string &INI::getFileName() const {
    return fileName;
}

int INI::addSection(const string &section) {
    auto itr = fileINI.find(section); //l'iteratore va all'elemento section
    if(itr == fileINI.end()) {
        fileINI[section].insert(make_pair("", ""));
        cout<<"Aggiunta sezione ["<<section<<"]"<<endl;
        state = no_errors;
    }else{
        state = exist;
    }
    return state;
}

int INI::addParam(const string &section, const string &parameter, const string &value) {
    try {
        auto itr = fileINI.at(section).insert(make_pair(parameter, value)); //accedo alla sezione e inserisco la coppia ( , )
        cout<<"Alla sezione "<<"["<<section<<"]"<<" aggiunto ("<<parameter<<","<<value<<")"<<endl;
        if(itr.second){
            state = no_errors;
        }else{
            state = exist;
        }
    }catch(out_of_range& e){
        state = errors;
    }
    return state;
}

int INI::addComment(const string &section, const string &parameter, const string &comment) {
    try {
        state = errors;
        auto position = fileINI.at(section).find(parameter);
        if(position != fileINI.at(section).end()){
            state = addParam(section, parameter+ "%%%%", ";" +comment);
            cout<<"Aggiunta commento: "<<comment<<" alla sezione "<<"["<<section<<"]"<< "e parametro "<<parameter<<endl;
        }else{
            state = no_errors;
        }
    }catch(out_of_range& e){
        state = errors;
    }
    return state;
}

int INI::addComment(const string &section, const string &comment) {
    try {
        auto position = fileINI[section+ "%%%%"].insert(make_pair("%%%%", ";" +comment));
        cout<<"Aggiunta commento "<<comment<<" alla sezione "<<"["<<section<<"]"<<endl;
        if(position.second){
            state = no_errors;
        }else{
            state = exist;
        }
    }catch(out_of_range& e){
        state = errors;
    }
    return state;
}

int INI::deleteSection(const string &section) {
    long int itr = (long) fileINI.erase(section);
    cout<<"Eliminata sezione "<<"["<<section<<"]"<<endl;
    if(itr > 0){
        state = no_errors;
    }else{
        state = errors;
    }
    return state;
}

int INI::deleteParam(const string &section, const string &parameter) {
    try {
        long int itr = (long) fileINI.at(section).erase(parameter);
        if(itr > 0){
            cout<<"Eliminato parametro "<<parameter<<" alla sezione "<<"["<<section<<"]"<<endl;
            state = no_errors;
        }else{
            state = errors;
        }
    }catch(const out_of_range& e){
        state = errors;
    }
    return state;
}

int INI::renameSection(const string &section, const string &newSection) {
    auto position = fileINI.find(section);
    if(position != fileINI.end()){
        fileINI.insert(make_pair(newSection, position->second));
        fileINI.erase(position);
        cout<<"Rinomino la sezione "<<"["<<section<<"]"<<" nella nuova sezione "<<"["<<newSection<<"]"<<endl;
        state = no_errors;
    }else{
        state = errors;
    }
    return state;
}

int INI::renameParam(const string &section, const string &newParameter, const string &parameter) {
    try {
        auto position = fileINI.at(section).find(parameter);
        if(position != fileINI.at(section).end()){
            auto itr = fileINI.at(section).insert(make_pair(newParameter, position->second));
            if(itr.second){
                fileINI[section].erase(position);
                state = no_errors;
            }else{
                state = exist;
            }
        }else{
            state = errors;
        }
        cout<<"Rinomino il parametro "<<parameter<<" nel nuovo parametro "<<newParameter<<" della sezione "<<"["<<section<<"]"<<endl;
    }catch(const out_of_range& e){
        state = errors;
    }
    return state;
}

int INI::changeParam(const string &section, const string &value, const string &parameter) {
    try {
        auto position = fileINI.at(section).find(parameter);
        if(position != fileINI.at(section).end()){
            position-> second = value;
            state = no_errors;
        }else{
            state = errors;
        }
    }catch(const out_of_range& e){
        state = errors;
    }
    return state;
}

void INI::print(){
    for (auto &itr1 : fileINI) {
        if(itr1.first.find("%%%%") == string::npos) {
            cout << "[" << itr1.first << "]" << endl; //stampa sezione (e suo eventuale relativo commento)
        }
        for(auto itr2 = itr1.second.begin() ; itr2 != itr1.second.end() ; itr2++) {
            if(itr2->first.find("%%%%") != string::npos) {
                cout<<itr2->second<<endl; //stampo commenti
            }else{
                if (itr2->first != "") {
                    cout << itr2->first << " = " << itr2->second << endl; //stampa parametro e valore
                }
            }
        }
    }
}

int INI::getParam(const string &section, const string &parameter, string& value) {
    try {
        auto position = fileINI.at(section).find(parameter);
        if(position != fileINI.at(section).end()) {
            value = position->second;
            state = no_errors;
        }else{
            cout<<"ERRORE!"<<endl;
            state = errors;
        }
    }
    catch(const out_of_range& err) {
        state = errors;
    }
    return state;
}

int INI::getComment(const string &section, const string &parameter, string &comment) {
    try {
        string str;
        if(parameter == ""){ //commento sezione
            str = section;
            str.pop_back();
            auto position = fileINI.at(str+"%%%%").find("%%%%");
            if(position != fileINI.at(str+"%%%%").end()) {
                comment = position->second;
                state = no_errors;
            }else{
                cout << "ERRORE!" << endl;
                state = errors;
            }
        }else{ //commento parametro
            str = parameter;
            str.pop_back();
            auto position = fileINI.at(section).find(str+"%%%%");
            if(position != fileINI.at(section).end()) {
                comment = position->second;
                state = no_errors;
            }else{
                cout << "ERRORE!" << endl;
                state = errors;
            }
        }
    }
    catch(const out_of_range& err) {
    }
    return state;
}














