//
// Created by admin on 21/02/2022.
//

#include <gtest/gtest.h>
#include "../INI.h"

//RICORDA: int state;
//         int errors = 0;
//         int no_errors = 1;
//         int exist = 2;

TEST(fileINItest, testGetFileName){
    INI fileINI("ListinoCD.ini", 1000);

    ASSERT_EQ(fileINI.getFileName(),"ListinoCD.ini");
}

TEST(testINI, testSection){
    INI fileINI("ListinoCD.ini", 1000);

    //test addSection
    EXPECT_EQ(fileINI.addSection("POP"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addSection("POP"), fileINI.state = 2); //esiste già
    EXPECT_EQ(fileINI.addSection("ROCK"), fileINI.state = 2); //esiste già

    //test getSection
    string str1 = "ROCK";
    EXPECT_EQ(fileINI.getSection(str1), fileINI.state = 1);
    string str2 = "BLUES";
    EXPECT_EQ(fileINI.getSection(str2), fileINI.state = 0);

    //test deleteSection
    EXPECT_EQ(fileINI.deleteSection("COUNTRY"), fileINI.state = 0);
    EXPECT_EQ(fileINI.deleteSection("ROCK"), fileINI.state = 1);

    //test renameSection
    EXPECT_EQ(fileINI.renameSection("PUNK-ROCK", "ROCK"), fileINI.state = 0); //rinomino sezione inesistente(error!)
    EXPECT_EQ(fileINI.renameSection("ROCK", "PUNK-ROCK"), fileINI.state = 1);
}

TEST(testINI, testParam){
    INI fileINI("ListinoCD.ini", 1000);

    //test addParam
    EXPECT_EQ(fileINI.addParam("ROCK", "GUNS'N'ROSES", "5"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addParam("ROCK", "GUNS'N'ROSES", "5"), fileINI.state = 2);
    EXPECT_EQ(fileINI.addParam("POP", "GUNS'N'ROSES", "5"), fileINI.state = 0);
    EXPECT_EQ(fileINI.addParam("POP", "MADONNA", "5"), fileINI.state = 1);

    //test getParam
    string str = "5";
    EXPECT_EQ(fileINI.getParam("ROCK", "ARTISTA_ROCK", str), fileINI.state = 0);
    EXPECT_EQ(fileINI.getParam("ROCK", "GUNS'N'ROSES", str), fileINI.state = 1);

    //test deleteParam
    EXPECT_EQ(fileINI.deleteParam("ROCK", "QUEEN"), fileINI.state = 0);
    EXPECT_EQ(fileINI.deleteParam("ROCK", "PINK FLOYD"), fileINI.state = 1);

    //test renameParam
    EXPECT_EQ(fileINI.renameParam("CLASSICAL", "MOZART", "BEETHOVEN"), fileINI.state = 1);
    EXPECT_EQ(fileINI.renameParam("CLASSICAL", "MOZART", "CHOPIN"), fileINI.state = 0);
    EXPECT_EQ(fileINI.renameParam("CLASSICAL", "BACH", "CHOPIN"), fileINI.state = 2);

    //test changeParam
    EXPECT_EQ(fileINI.changeParam("ROCK", "5", "PINK FLOYD"), fileINI.state = 1);
    EXPECT_EQ(fileINI.changeParam("ROCK", "5", "BACH"), fileINI.state = 0);
    EXPECT_EQ(fileINI.changeParam("ROCK", "5", "NOME_SBAGLIATO"), fileINI.state = 0);
}

TEST(testINI, testComment){
    INI fileINI("ListinoCD.ini", 1000);

    //test addComment
    EXPECT_EQ(fileINI.addComment("ROCK", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addComment("ROCK", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 0);
    EXPECT_EQ(fileINI.addComment("ROCK", "GUNS'N'ROSES", "Nuovo CD arrivato oggi"), fileINI.state = 0);
    EXPECT_EQ(fileINI.addComment("POP", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 0);

    EXPECT_EQ(fileINI.addComment("CLASSICAL", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addComment("CLASSICAL", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 2);
    EXPECT_EQ(fileINI.addComment("CLASSIC", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 2);

    //test getComment (relativo a parametro)
    string str1 = "Novità CD";
    EXPECT_EQ(fileINI.getComment("CLASSICAL", "BACH", str1), fileINI.state = 1);
    EXPECT_EQ(fileINI.getComment("POP", "PINK FLOYD", str1), fileINI.state = 0);

    //test getComment (relativo a sezione)
    string str2 = "offerta CD ROCK";
    EXPECT_EQ(fileINI.getComment("ROCK", str2), fileINI.state = 1);
    EXPECT_EQ(fileINI.getComment("CLASSICAL", str2), fileINI.state = 0);
}