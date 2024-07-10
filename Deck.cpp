#include "Deck.h"
#include "Card.h"
#include <vector>
#include <QDebug>
#include <QPair>
#include <QDateTime>

Deck::Deck(int maxC){
    this->maximumShowCard = maxC;
}

void Deck::AddCardToDeck(Card card){
    qDebug() << "Added card to cardlist: " << card.front << card.back;
    this->cardList.push_back(card);
}

void Deck::SetMaxCardToShow(int val){
    this->maximumShowCard = val;
}

void Deck::AddCardToDateDeck(Card card, QDateTime date, int button){
    switch(button){
        case 0://Good case
            if(this->cardDateAddedMap[card.front] == 0){
                this->cardDateList.push_back(qMakePair(date.addSecs(600),card));
                this->cardDateAddedMap[card.front]+=1;
                qDebug() << "datemap: " << this->cardDateAddedMap[card.front];
            }else{
                qDebug() << "Times to add the day: " << this->timesToAddTheDay[this->cardDateAddedMap[card.front]];
                this->cardDateList.push_back(qMakePair(date.addDays(this->timesToAddTheDay[this->cardDateAddedMap[card.front]]),card));
                this->cardDateAddedMap[card.front]+=1;
                qDebug() << "Added card as a good case" << "Date: " << this->cardDateList.back().first;
                qDebug() << "datemap: " << this->cardDateAddedMap[card.front];

            }
            break;
        case 1://Again case
            this->cardDateList.push_back(qMakePair(date.addSecs(60),card));
           // this->cardDateAddedMap[card]++;
            qDebug() << "Added card as an again case" << "Date: " << this->cardDateList.back().first;
            break;
    }
}

Card Deck::handleNextCard(int index){
    bool isOpt;
    int ind = 0;
    for(auto card : this->cardDateList){
        if(card.first <= QDateTime::currentDateTime()){
            isOpt = true;
            break;
        }
        ind++;
    }
    if(isOpt){
        return this->cardDateList.at(ind).second;
    }else if(index < cardList.size()){
        return this->cardList.at(index);
    }/*else if(index >= cardList.size()){

    }*/
}

std::vector<Card> Deck::GetCardList(){
    return this->cardList;
}

int Deck::getMaximumShowCard(){
    return this->maximumShowCard;
}

