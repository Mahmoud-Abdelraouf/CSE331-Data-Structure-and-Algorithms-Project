// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "xmlparser.h"
#include <QDebug>
#include "graph.h"
#include "post.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    outputTextEdit = findChild<QTextEdit *>("outputTextEdit"); // Initialize outputTextEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendToOutput(const QString &text)
{
    outputTextEdit->append(text);
}

void MainWindow::on_pushButton_clicked()
{
    QString outputString;
    QString filePath = "D:\\workspace\\QT_workspace\\xmlparse\\sample.xml";
    XMLparser *newParse = new XMLparser(filePath);
    QTextStream stream(stdout);
    stream.setString(&outputString);
    qInfo().nospace().noquote() << "Redirecting output to QTextEdit.";
    if(newParse->isValidFile())
    {
        const QList <User*> users = newParse->parse();
        for(int i = 0; i < users.size();i++)
        {

            qInfo()<<users.at(i)->getId();
            qInfo() << users.at(i)->getName();

            for(int j = 0; j < users.at(i)->getPosts().size();j++)
            {
                qInfo() << (users.at(i)->getPosts()).at(j)->getBody();
                for(int k= 0; k < ((users.at(i)->getPosts()).at(j))->getTopics().size();k++ )
                    qInfo() <<  ((users.at(i)->getPosts()).at(j)->getTopics()).at(k);

            }
            for(int l = 0; l< users.at(i)->getFollowersId().size();l++)
                qInfo() << (users.at(i)->getFollowersId()).at(l);
        }
        QList<QString> ids;
        for(int j = 0; j < users.size();j++){
            ids.push_back(users.at(j)->getId());
        }

        Graph graph(users.size(),ids);
        QList<QString> followers;
        for(int j = 0; j <users.size();j++){

            followers = users.at(j)->getFollowersId();
            graph.setAdjacencyListForVertex(users.at(j)->getId(),followers);

        }
        graph.printGraph();
        QString mostInfluential = graph.findMostInfluentialUser();

        appendToOutput("");
        appendToOutput("\nMost Influential User: " + mostInfluential);


        QString MostActiveUser = graph.findMostActiveUser();
        appendToOutput("\nMost Active User: " + MostActiveUser);

        QList<QString> MutualFollowers = graph.findMutualFollowers("3","2");;

        for (int j = 0; j < MutualFollowers.size(); j++)
        {
            QString output = "\nMutual Followers: " + MutualFollowers.at(j);
            appendToOutput(output);
        }

        QList<QString> SuggestFollowers = graph.suggestUsersToFollow("2");;
        for (int j = 0; j < SuggestFollowers.size(); j++)
        {
            QString output = "\nSuggest Followers: " + SuggestFollowers.at(j);
            appendToOutput(output);
        }

        QList<post*> userPosts;
        for(int j = 0; j <users.size();j++){
            userPosts.append(users.at(j)->getPosts());
        }
        QList<post*> foundPosts;
        foundPosts.append(searchPosts("Lorem","solar_energy",userPosts));
        for(int j = 0; j <foundPosts.size();j++){
            QString output = "\n Post: " + foundPosts.at(j)->getBody();
            appendToOutput(output);
        }



    }
    else
    {
        delete newParse;
    }
}
