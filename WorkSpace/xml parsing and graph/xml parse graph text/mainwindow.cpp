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
   // outputTextEdit = findChild<QTextEdit *>("outputTextEdit"); // Initialize outputTextEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_userdialog_clicked()
{
    QDialog *dialog = new QDialog();
    dialog -> setWindowModality(Qt::WindowModality::ApplicationModal);
    dialog -> setMinimumWidth(640);
    dialog -> setMinimumHeight(640);


    QString outputString;
    QString filePath = "C:\\Users\\might\\Downloads\\CSE331-Data-Structure-and-Algorithms-Project\\WorkSpace\\xml parsing and graph\\xml parse graph text\\sample.xml";
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
        //graph.printGraph();

        /********** most active ****************************/
        QString MostActiveUser = graph.findMostActiveUser();
        QLabel *active = new QLabel();
        active-> setText("Most active user:");
        active-> setGeometry(10,10,150,50);
        active->setParent(dialog);
        active->show();

        QTextEdit *activeOP = new QTextEdit();
        activeOP-> setGeometry(160,10,150,50);
        activeOP->setParent(dialog);
        activeOP->append(MostActiveUser);
        activeOP->show();

        /********** most influence ****************************/
        QString mostInfluential = graph.findMostInfluentialUser();
        QLabel *influence = new QLabel();
        influence-> setText("Most Influential user:");
        influence-> setGeometry(10,80,150,50);
        influence->setParent(dialog);
        influence->show();

        QTextEdit *influenceOP = new QTextEdit();
        influenceOP-> setGeometry(160,80,150,50);
        influenceOP->setParent(dialog);
        influenceOP->append(mostInfluential);
        influenceOP->show();

        /************ *******************************/
        QLabel *muatualLabel = new QLabel();
        muatualLabel-> setText("Mutual Followers between:");
        muatualLabel-> setGeometry(10,160,150,50);
        muatualLabel->setParent(dialog);
        muatualLabel->show();

        QTextEdit *mutual1 = new QTextEdit();
        mutual1-> setToolTip("Enter value of first user");
        mutual1-> setGeometry(160,160,150,50);
        mutual1->setParent(dialog);
        mutual1->show();

        QTextEdit *mutual2 = new QTextEdit();
        mutual2-> setToolTip("Enter value of second user");
        mutual2-> setGeometry(320,160,150,50);
        mutual2->setParent(dialog);
        mutual2->show();

        QPushButton *Mutualbutton = new QPushButton("Get Mutual Followers");
        Mutualbutton->setGeometry(480, 160, 120, 50);
        Mutualbutton->setParent(dialog);
        Mutualbutton->show();

        QTextEdit *mutualOP = new QTextEdit();
        mutualOP->setGeometry(10, 240, 600, 50);
        mutualOP->setParent(dialog);
        mutualOP->show();
        connect(Mutualbutton, &QPushButton::clicked, [=]() {
            // Retrieve the text from mutual1 and mutual2
            QString user1 = mutual1->toPlainText();
            QString user2 = mutual2->toPlainText();
            // Call the function with the entered values
            QList<QString> MutualFollowers = graph.findMutualFollowers(user1, user2);
            // Append the result to mutualOP
            for (int j = 0; j < MutualFollowers.size(); j++)
            {
                QString output = MutualFollowers.at(j) + "  ";
                mutualOP->append(output);
            }

        });

        /*********************************************/
        QLabel *suggestlLabel = new QLabel();
        suggestlLabel-> setText("Suggest followers for:");
        suggestlLabel-> setGeometry(10,310,150,50);
        suggestlLabel->setParent(dialog);
        suggestlLabel->show();

        QTextEdit *suggest = new QTextEdit();
        suggest-> setToolTip("Enter value of user");
        suggest-> setGeometry(160,310,150,50);
        suggest->setParent(dialog);
        suggest->show();

        QPushButton *suggestbutton = new QPushButton("Get sugggestions");
        suggestbutton->setGeometry(480, 310, 120, 50);
        suggestbutton->setParent(dialog);
        suggestbutton->show();

        QTextEdit *suggestOP = new QTextEdit();
        suggestOP-> setGeometry(10,380,600,50);
        suggestOP->setParent(dialog);
        suggestOP->show();

        connect(suggestbutton, &QPushButton::clicked, [=]() {
            QString user = suggest->toPlainText();
            QList<QString> SuggestFollowers = graph.suggestUsersToFollow(user);
            for (int j = 0; j < SuggestFollowers.size(); j++)
            {
                QString output = SuggestFollowers.at(j) + "  ";
                suggestOP->append(output);
            }

        });

        QPushButton *closebutton = new QPushButton("CLOSE");
        closebutton->setGeometry(260, 450, 120, 50);
        closebutton->setParent(dialog);
        closebutton->show();

        connect(closebutton, &QPushButton::clicked, [=]() {
            dialog->close();
        });


    }
    else
    {
        delete newParse;
    }


   dialog -> show();
}

