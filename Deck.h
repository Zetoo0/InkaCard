#ifndef DECK_H
#define DECK_H

#include <QDateTime>
#include "Card.h"
#include <vector>
#include <QPair>
#include <QQueue>
#include <QString>
#include <map>

class Deck{
public:
    Deck();
    Deck(int maxC,QString name);
    ~Deck();

    void AddCardToDeck(Card card);
    void AddCardToDateDeck(Card card, QDateTime date, int button);
    void SetMaxCardToShow(int val);
    void SetDeckEndIndex(int val);

    void SaveProgress();
    void LoadProgrss();

    std::vector<Card> GetCardList();
    int getMaximumShowCard();
    int getLastEndedIndex();
    QString getName();

    Card handleNextCard(int index);


private:
    int maximumShowCard;
    int deckEndedIndex;
    QString name;
    std::vector<Card> cardList{};
    std::vector<Card>repeatList{};
    std::map<QString,int> cardDateAddedMap{};
    std::vector<QPair<QDateTime,Card>> cardDateList{};
    std::vector<int> timesToAddTheDay{1,3,9,14,28,56,122,240,360,480};
    //std::map<int,Card> cardMap;
   // std::map<std::string,QDateTime> nextAppear;
    //std::priority_queue<QPair<Card,QString>> appearQueue;

};

#endif // DECK_H
