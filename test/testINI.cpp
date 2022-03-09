//
// Created by admin on 21/02/2022.
//


#include <gtest/gtest.h>
#include "../INI.h"

//RICORDA: int state;
//         int errors = 0;
//         int no_errors = 1;
//         int exist = 2;

TEST(testINI, testSection){
    INI fileINI("ListinoCD");

    //test addSection
    EXPECT_EQ(fileINI.addSection("POP"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addSection("POP"), fileINI.state = 2); //esiste già
    EXPECT_EQ(fileINI.addSection("ROCK"), fileINI.state = 2); //esiste già

    //test deleteSection
    EXPECT_EQ(fileINI.deleteSection("COUNTRY"), fileINI.state = 0);
    EXPECT_EQ(fileINI.deleteSection("ROCK"), fileINI.state = 1);

    //test renameSection
    EXPECT_EQ(fileINI.renameSection("PUNK-ROCK", "ROCK"), fileINI.state = 0); //rinomino sezione inesistente(error!)
    EXPECT_EQ(fileINI.renameSection("ROCK", "PUNK-ROCK"), fileINI.state = 1);
}

TEST(testINI, testParam){
    INI fileINI("ListinoCD");

    //test addParam
    EXPECT_EQ(fileINI.addParam("ROCK", "GUNS'N'ROSES", "5"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addParam("ROCK", "GUNS'N'ROSES", "5"), fileINI.state = 2);
    EXPECT_EQ(fileINI.addParam("POP", "GUNS'N'ROSES", "5"), fileINI.state = 0);

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
    INI fileINI("ListinoCD");

    //test addComment
    EXPECT_EQ(fileINI.addComment("ROCK", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addComment("ROCK", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 0);
    EXPECT_EQ(fileINI.addComment("ROCK", "GUNS'N'ROSES", "Nuovo CD arrivato oggi"), fileINI.state = 0);
    EXPECT_EQ(fileINI.addComment("POP", "PINK FLOYD", "Nuovo CD arrivato oggi"), fileINI.state = 0);

    EXPECT_EQ(fileINI.addComment("CLASSICAL", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 1);
    EXPECT_EQ(fileINI.addComment("CLASSICAL", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 2);
    EXPECT_EQ(fileINI.addComment("CLASSIC", "LA MIGLIOR MUSICA CLASSICA"), fileINI.state = 2);
}
