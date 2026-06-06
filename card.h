#ifndef CARD_H
#define CARD_H

#include <QString>

enum class Suit//花色
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank//点数
{
    Ace = 1,
    Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,
    Jack = 11,
    Queen = 12,
    King = 13
};

class Card
{
public:
    Suit suit;
    Rank rank;
    Card(Suit s, Rank r);

    //重载==来判断两张卡是否相同
    bool operator==(const Card& other) const {
        return suit == other.suit && rank == other.rank;
    }

    int playValue() const; // 获取这张牌的打出点数值
    QString imagePath() const; // 获取对应卡面的图片资源路径
    QString toString() const; // 获取卡牌文字描述
};

#endif // CARD_H
