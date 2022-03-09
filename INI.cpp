//
// Created by admin on 15/12/2021.
//

#include <iostream>
#include "INI.h"

INI::INI(const string &fileName) {
    this->fileName = fileName;
    this->project.open(fileName, ios::in);
    if(project.is_open()){
        analyze();
    }
    project.close();
}

void INI::analyze(){
    string thisSection;
    string thisComment;
    string line; //l'analisi del file è fatta riga per riga

    while(!project.eof()){ // leggo dallo stream di input una sequenza di caratteri copiandoli nella stringa
        getline(project, line);
        if(line[0] == '['){ //inizio sezione
            thisSection = line;
            thisSection.pop_back();
            thisSection.erase(thisSection.begin());
            addSection(thisSection);
        }else{
            cout << "Errore: ']' non trovato nella sezione." << endl; // ']' non trovato
            fileINI.clear();
            return;
        }if(!line.empty() && line[0] == ';'){ //ha trovato un commento
            thisComment = line;
            thisComment.erase(thisComment.begin());
        }else if(line.empty()){
            //nulla è memorizzato se la stringa è vuota...
        }else{ //trovato parametro
            for(auto position = line.find(" "); position!=string::npos ; position = line.find(" "))   //Elimino eventuali spazi vuoti
                line.erase(position,1);
            auto itr = line.find('=');
            string parametro(line, 0, itr);
            string valore(line, itr+1, string::npos);
            if(line.length()>0){
                addParam(thisSection, valore, parametro);
            }
        }
    }
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
        auto itr = fileINI[section].insert(make_pair(parameter, value)); //accedo alla sezione e inserisco la coppia ( , )
        cout<<"Alla sezione "<<"["<<section<<"]"<<" aggiunto ("<<parameter<<","<<value<<")"<<endl;
        if(itr.second){
            state = no_errors;
        }else{
            state = exist;
        }
    }catch(out_of_range e){
        std::cout<<"Tentativo di accedere ad elementi fuori range"<<std::endl;
        state = errors;
    }
    return state;
}

int INI::addComment(const string &section, const string &parameter, const string &comment) {
    try {
        state = errors;
        auto position = fileINI[section].find(parameter);
        if(position != fileINI[section].end()){
            state = addParam(section, parameter+ "$", "" +comment);
            cout<<"Aggiunta commento: "<<comment<<" alla sezione "<<"["<<section<<"]"<< "e parametro "<<parameter<<endl;
        }else{
            state = no_errors;
        }
    }catch(out_of_range e){
        std::cout<<"Tentativo di accedere ad elementi fuori range"<<std::endl;
        state = errors;
    }
    return state;
}

int INI::addComment(const string &section, const string &comment) {
    try {
        fileINI[section];
        string str(section);
        str.pop_back();
        auto position = fileINI[str+ "$"].insert(make_pair("", ";"+comment));
        cout<<"Aggiunta commento "<<comment<<" alla sezione "<<"["<<section<<"]"<<endl;
        if(position.second){
            state = no_errors;
        }else{
            state = exist;
        }
    }catch(out_of_range e){
        std::cout<<"Tentativo di accedere ad elementi fuori range"<<std::endl;
        state = errors;
    }
    return state;
}

int INI::deleteSection(const string &section) {
    long int i = (long) fileINI.erase(section);
    cout<<"Eliminata sezione "<<"["<<section<<"]"<<endl;
    if(i > 0){
        state = no_errors;
    }else{
        state = errors;
    }
    return state;
}

int INI::deleteParam(const string &section, const string &parameter) {
    auto itr = fileINI[section].find(parameter);
    if(itr != fileINI[section].end()){
        fileINI[section].erase(parameter);
        cout<<"Eliminato parametro "<<parameter<<" alla sezione "<<"["<<section<<"]"<<endl;
        state = no_errors;
    }else{
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
        auto position = fileINI[section].find(parameter);
        if(position != fileINI[section].end()){
            auto itr = fileINI[section].insert(make_pair(newParameter, position->second));
            if(itr.second){
                fileINI[section].erase(position);
                state = no_errors;
            }else{
                state = exist;
            }
        }else{
            state = errors;
        }
        cout<<"Rinomino il parametro "<<parameter<<" nel nuovo parametro "<<newParameter<<"dell sezione"<<"["<<section<<"]"<<endl;
    }catch(const out_of_range e){
        state = errors;
    }
    return state;
}

int INI::changeParam(const string &section, const string &value, const string &parameter) {
    try {
        auto position = fileINI[section].find(parameter);
        if(position != fileINI[section].end()){
            position-> second = value;
            state = no_errors;
        }else{
            state = errors;
        }
    }catch(const out_of_range e){
        state = errors;
    }
    return state;
}

void INI::printSections() {
    std::cout<<"Sezioni: "<<std::endl;
    for(auto &itr:fileINI){
        std::cout<<itr.first<<std::endl;
    }
}

void INI::printParameters(const string &section) {
    std::cout<<"Parametri della sezione "<<section<< " :"<<std::endl;
    for (auto &itr:fileINI[section]) {
        std::cout<<itr.first<<std::endl;
    }
}

void INI::printValue(const string &section,const string &parameter) {
    std::cout<<"valore del parametro: " <<parameter<<" ="<<fileINI[section][parameter]<<std::endl;
}

void INI::printAll() {
    for (auto &itr:fileINI) {
        if(itr.first != "$"){
            std::cout<<"["<< itr.first<<"]"<<endl;  // Stampo nome della sezione
        }
        for (auto nextItr = itr.second.begin(); nextItr != itr.second.end(); nextItr++) {
            if(nextItr->first == "$"){
                std::cout<<nextItr->second<<endl;
            }else{
                if(nextItr->first != ""){
                    std::cout<<nextItr->first<<"="<<nextItr->second<<endl;
                }
            }
        }
    }
}















