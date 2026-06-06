#include "playvalidator.h"

bool PlayValidator::isValidPlay(const std::vector<Card>& cards) {
    if (cards.empty()) return false;
    if (cards.size() == 1) return true;
    
    if (cards.size() == 2) {
        bool hasAce = cards[0].rank == Rank::Ace || cards[1].rank == Rank::Ace;
        bool bothAces = cards[0].rank == Rank::Ace && cards[1].rank == Rank::Ace;
        if (hasAce && !bothAces) return true;
    }
    
    Rank firstRank = cards[0].rank;
    int totalValue = 0;
    for (const Card& c : cards) {
        if (c.rank != firstRank) return false;
        totalValue += c.playValue();
    }
    
    if (totalValue <= 10) return true;
    return false;
}

QString PlayValidator::getInvalidReason(const std::vector<Card>& cards) {
    if (cards.empty()) return "未选择卡牌。";
    if (cards.size() == 1) return "";
    
    if (cards.size() == 2) {
        bool hasAce = cards[0].rank == Rank::Ace || cards[1].rank == Rank::Ace;
        bool bothAces = cards[0].rank == Rank::Ace && cards[1].rank == Rank::Ace;
        if (hasAce && !bothAces) return ""; 
    }
    
    Rank firstRank = cards[0].rank;
    int totalValue = 0;
    for (const Card& c : cards) {
        if (c.rank != firstRank) {
            return "连击失败：选择的卡牌必须点数全部相同，或者是一张 A 搭配另一张非 A 卡牌。";
        }
        totalValue += c.playValue();
    }
    
    if (totalValue > 10) {
        return QString("连击失败：同点数连击的总和不能超过 10（当前总和 %1）。").arg(totalValue);
    }
    
    return "非法的出牌组合。";
}

int PlayValidator::calculateBaseDamage(const std::vector<Card>& cards) {
    int damage = 0;
    for (const Card& c : cards) {
        damage += c.playValue();
    }
    return damage;
}
