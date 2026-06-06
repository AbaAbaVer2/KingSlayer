#include "card.h"
#include <string>


Card::Card(Suit s, Rank r):suit(s),rank(r)
{

}

int Card::playValue() const
{
    if (rank == Rank::Jack) return 10;
    if (rank == Rank::Queen) return 15;
    if (rank == Rank::King) return 20;
    return static_cast<int>(rank);
}

QString Card::imagePath() const
{
    QString suitStr;
    switch (suit) {
        case Suit::Hearts: suitStr = "heart"; break;
        case Suit::Diamonds: suitStr = "diamond"; break;
        case Suit::Clubs: suitStr = "club"; break;
        case Suit::Spades: suitStr = "spade"; break;
    }

    // 用户的图片全是用数字命名的，例如 club_1.png, heart_11.png
    QString rankStr = QString::number(static_cast<int>(rank));

    // 资源文件路径
    return QString(":/card/%1_%2.png").arg(suitStr, rankStr);
}

QString Card::toString() const {
    QString sStr, rStr;
    switch(suit) {
        case Suit::Hearts: sStr = "❤️ 红桃"; break;
        case Suit::Diamonds: sStr = "♦️ 方块"; break;
        case Suit::Clubs: sStr = "♣️ 梅花"; break;
        case Suit::Spades: sStr = "♠️ 黑桃"; break;
    }
    if(rank == Rank::Ace) rStr = "A";
    else if(rank == Rank::Jack) rStr = "J";
    else if(rank == Rank::Queen) rStr = "Q";
    else if(rank == Rank::King) rStr = "K";
    else rStr = QString::number(static_cast<int>(rank));
    return sStr + " " + rStr;
}
