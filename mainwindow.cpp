#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Deck.h"
#include "Card.h"
#include <string>
#include <QDebug>
#include <QLabel>
#include <QFrame>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>

Card c1{"11+11","22"};
Card c2{"22+22","44"};
Deck* deck = new Deck(5,"valaminemamerika");
int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //deck->AddCardToDeck(c1);
    //deck->AddCardToDeck(c2);
    //ui->frontFrame->findChild<QLabel*>("showLb")->setText(deck->GetCardList().at(0).front);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->revealBtn->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_revealBtn_clicked()
{

    qDebug() << "asd";
    ui->frontFrame->findChild<QLabel*>("showLb")->setText(deck->GetCardList().at(currentIndex).back);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->revealBtn->setVisible(false);
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Again...";
    Card cardo = deck->GetCardList().at(currentIndex);
    deck->AddCardToDateDeck(cardo,QDateTime::currentDateTime(),1);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->revealBtn->setVisible(true);
    currentIndex++;
    if(currentIndex == deck->getMaximumShowCard()){
        ui->frontFrame->findChild<QLabel*>("showLb")->setText("Completed the today studies:)");
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->revealBtn->setVisible(false);
        deck->SetDeckEndIndex(currentIndex);
    }else{
        ui->frontFrame->findChild<QLabel*>("showLb")->setText(deck->handleNextCard(currentIndex).front);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "Goood";
    Card cardo = deck->GetCardList().at(currentIndex);
    deck->AddCardToDateDeck(cardo,QDateTime::currentDateTime(),0);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->revealBtn->setVisible(true);
    currentIndex++;
    if(currentIndex == deck->getMaximumShowCard()){
        ui->frontFrame->findChild<QLabel*>("showLb")->setText("Completed the today studies:)");
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->revealBtn->setVisible(false);
        deck->SetDeckEndIndex(currentIndex);
    }else{
        ui->frontFrame->findChild<QLabel*>("showLb")->setText(deck->handleNextCard(currentIndex).front);
    }

}


void MainWindow::on_addDeckBtn_clicked()
{
    qDebug() << "adddeck nyomva";
    QDir dir("C:/Users/zeten/OneDrive/Dokumentumok/CarderHarder");
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fname = dialog.getOpenFileName();
    QFile deckFile(fname/*dir.filePath("notdeck.json")*/);
    qDebug() << deckFile.exists();
    if(deckFile.exists()){
        if(deckFile.open(QIODevice::ReadOnly)){
            qDebug() << "olvasás?";
            QByteArray bytes = deckFile.readAll();
            deckFile.close();

            QJsonParseError error;
            QJsonDocument document = QJsonDocument::fromJson(bytes, &error);
            if(error.error != QJsonParseError::NoError){
                qDebug() << "Error while reading dzseuon";
                return;
            }else{
                qDebug() << "No error in read";
            }
            if(document.isObject()){
                qDebug() << "Object??";
                QJsonObject deckObject = document.object();
                QJsonArray deckArray = deckObject.value("Cards").toArray();

                for(auto card : deckArray){
                    QJsonObject obj = card.toObject();
                    Card cardo{obj.value("front").toString(),obj.value("back").toString()};
                    deck->AddCardToDeck(cardo);
                }
            }
        }
    }
    QFile file(deck->getName()+".txt");
    if(file.exists()){
        deck->LoadProgrss();
        currentIndex = deck->getLastEndedIndex();
        qDebug() << "New old index: " << currentIndex;
    }
    ui->frontFrame->findChild<QLabel*>("showLb")->setText(deck->GetCardList().at(currentIndex-3).front);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->revealBtn->setVisible(true);

}

