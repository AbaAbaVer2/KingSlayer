#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <queue>
#include <optional>
#include <QObject>
#include "card.h"

enum class GameState {
    Playing,
    Win,
    Defeat
};

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject* parent = nullptr);
    void initGame();
    void restartGame();
    void drawCards(int count);

    // 提供给界面的获取数据的接口 (Getters)
    const std::vector<Card>& getHand() const { return Hand; }
    std::optional<Card> getCurrentBoss() const { return CurrentBoss; }
    int getDeckSize() const { return PlayerDeck.size(); }
    int getDiscardSize() const { return DiscardPile.size(); }
    int getBossHp() const { return currentBossHp; }
    int getBossAtk() const { return currentBossAttack; }
    int getShield() const { return currentShield; }
    int getRound() const { return currentRound; }
    GameState getGameState() const { return gameState; }
    bool getIsDefending() const { return isDefending; }
    int getPendingDamage() const { return pendingDamage; }
    const std::vector<Card>& getPlayerDeck() const { return PlayerDeck; }
    const std::vector<Card>& getDiscardPile() const { return DiscardPile; }
    
    void cheatKillBoss(); // 开发者秒杀外挂

    //玩家出牌
    void playCards(const std::vector<Card>& cards);

    // 玩家防守弃牌
    void defendCards(const std::vector<Card>& cards);

signals:
    void battleLog(QString msg);
    void bossTookDamage(int damage);


private:
    std::vector<Card> PlayerDeck;//玩家牌堆
    std::queue<Card> BossDeck;//要打的boss
    void RevealNextBoss();//揭示下一个boss

    // 计算总伤害 (处理梅花翻倍)
    int calculateDamage(const std::vector<Card>& cards);
    // 触发单张卡牌的花色特效
    void activateSuitPower(const Card& card);
    // 辅助函数：从手牌中把打出去的牌删掉
    void removeCardsFromHand(const std::vector<Card>& cards);

    // --- 牌桌状态变量 ---
    std::vector<Card> Hand;         // 玩家手牌
    std::vector<Card> DiscardPile;  // 弃牌堆
    std::optional<Card> CurrentBoss;// 当前boss
    int currentBossHp;              // 当前boss血量
    int currentBossAttack;          // 当前boss攻击力
    int currentShield;              // 玩家护盾值
    int currentRound;               // 当前回合数
    bool isDefending;               // 是否处于防守阶段
    int pendingDamage;              // 待承受的伤害值
    GameState gameState;            // 游戏状态
};

#endif // GAMEMANAGER_H
