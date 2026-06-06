#include "gamemanager.h"
#include <algorithm> // 包含打乱用的 std::shuffle
#include <random>    // 包含随机数引擎
#include <QString>

GameManager::GameManager(QObject* parent) : QObject(parent) {
    restartGame();
}

void GameManager::initGame()
{
    PlayerDeck.clear();
    DiscardPile.clear();
    Hand.clear();
    while(!BossDeck.empty()) BossDeck.pop();
    currentRound = 1;
    currentShield = 0;
    isDefending = false;
    pendingDamage = 0;
    gameState = GameState::Playing;

    // 1. 生成玩家的牌堆（花色：红桃到黑桃，点数：A到10）
    for(int s = static_cast<int>(Suit::Hearts) ; s <= static_cast<int>(Suit::Spades) ; s++){
        for(int r = static_cast<int>(Rank::Ace) ; r <= static_cast<int>(Rank::Ten) ; r++){
            PlayerDeck.push_back(Card(static_cast<Suit>(s), static_cast<Rank>(r)));
        }
    }

    // 2. 打乱玩家牌堆
    std::random_device rd;  // 获取真实随机数种子
    std::mt19937 g(rd());   // 使用梅森旋转算法生成伪随机数序列
    std::shuffle(PlayerDeck.begin(), PlayerDeck.end(), g);

    // 3. 生成Boss的队列 (规则: 4张J洗匀 -> 4张Q洗匀 -> 4张K洗匀)
    std::vector<Rank> bossRanks = {Rank::Jack, Rank::Queen, Rank::King};
    for(Rank r : bossRanks) {
        std::vector<Card> tempBosses;
        // 生成该阶段的4个Boss
        for(int s = static_cast<int>(Suit::Hearts) ; s <= static_cast<int>(Suit::Spades) ; s++){
            tempBosses.push_back(Card(static_cast<Suit>(s), r));
        }
        // 打乱这4个Boss
        std::shuffle(tempBosses.begin(), tempBosses.end(), g);
        // 存入正式的 BossDeck 队列中（注：std::queue 用 push）
        for(const Card& c : tempBosses) {
            BossDeck.push(c);
        }
    }


}

void GameManager::restartGame()
{
    initGame();
    drawCards(8);
    RevealNextBoss();
}

//玩家抽牌
void GameManager::drawCards(int count)
{
    for(int i = 0; i < count; i++) {
        if(PlayerDeck.empty()) {
            // 如果牌堆空了，先把弃牌堆洗回牌堆
            std::shuffle(DiscardPile.begin(), DiscardPile.end(), std::mt19937(std::random_device()()));
            PlayerDeck = DiscardPile;
            DiscardPile.clear();
        }
        if(!PlayerDeck.empty()) {
            Hand.push_back(PlayerDeck.back());
            PlayerDeck.pop_back();
        }
    }
}

void GameManager::playCards(const std::vector<Card> &cards)
{
    if (gameState != GameState::Playing) return;
    if (cards.empty() || !CurrentBoss.has_value()) return;

    // 第一步：扣除手牌，并将这些牌扔进弃牌堆
    removeCardsFromHand(cards);
    for(const Card& c : cards) { DiscardPile.push_back(c); }

    // 第二步：结算花色特效（遍历 cards，挨个调用 activateSuitPower）
    for(const Card& c : cards) {
        activateSuitPower(c);
    }

    // 第三步：结算伤害并扣除 Boss 血量
    int dmg = calculateDamage(cards);
    emit battleLog(QString("🗡️ 造成最终伤害: %1 点").arg(dmg));
    currentBossHp -= dmg;
    if (dmg > 0) emit bossTookDamage(dmg);

    // 第四步：Boss 死亡判定
    if (currentBossHp == 0) {
        // 触发【精准击杀】规则！把 CurrentBoss 放回 PlayerDeck 的最顶端！
        // 然后调用 RevealNextBoss() 翻开下一个 Boss
        PlayerDeck.push_back(CurrentBoss.value());
        RevealNextBoss();
    }
    else if (currentBossHp < 0) {
        // 触发【普通击杀】！把 CurrentBoss 扔进弃牌堆 DiscardPile。
        // 然后调用 RevealNextBoss()
        DiscardPile.push_back(CurrentBoss.value());
        RevealNextBoss();
    }
    else {
        // Boss 没死，进入 Boss 攻击回合（挨打环节）
        int actualDmg = std::max(0, currentBossAttack - currentShield);
        
        if (actualDmg > 0) {
            isDefending = true;
            pendingDamage = actualDmg;
            
            // 检查玩家所有的手牌加起来够不够防守
            int totalHandValue = 0;
            for (const Card& c : Hand) {
                totalHandValue += c.playValue();
            }
            if (totalHandValue < actualDmg) {
                // 惨遭击杀！防守失败！
                gameState = GameState::Defeat;
            }
        } else {
            // 护盾完全抵消了伤害，直接进入下一回合
            emit battleLog("🛡️ 护盾完全抵消了 Boss 的攻击！");
            currentShield = 0; // 回合结束清空护盾
            currentRound++;
        }
    }
}

void GameManager::cheatKillBoss()
{
    if (gameState != GameState::Playing || !CurrentBoss.has_value()) return;
    
    emit battleLog("⚡【系统覆盖】开发者外挂启动！Boss 被直接抹杀！");
    DiscardPile.push_back(CurrentBoss.value());
    RevealNextBoss();
    isDefending = false;
    pendingDamage = 0;
    currentShield = 0;
    currentRound++;
}

void GameManager::RevealNextBoss()
{
    //先判断是否胜利
    if(BossDeck.empty()){
        gameState = GameState::Win;
        return;
    }
    //揭示下一个boss
    CurrentBoss = BossDeck.front();
    BossDeck.pop();
    //将护盾值设定为0
    currentShield = 0;
    //根据boss的点数设定血量和攻击力
    if (CurrentBoss->rank == Rank::Jack) {
        currentBossHp = 20;
        currentBossAttack = 10;
    } else if (CurrentBoss->rank == Rank::Queen) {
        currentBossHp = 30;
        currentBossAttack = 15;
    } else if (CurrentBoss->rank == Rank::King) {
        currentBossHp = 40;
        currentBossAttack = 20;
    }
}

int GameManager::calculateDamage(const std::vector<Card> &cards)
{
    int totalDamage = 0;
    for (const Card& c : cards) {
        int val = c.playValue();
        // 只有梅花牌自己的伤害翻倍，且 Boss 不能是梅花
        if (c.suit == Suit::Clubs && CurrentBoss->suit != Suit::Clubs) {
            val *= 2;
        }
        totalDamage += val;
    }
    return totalDamage;
}

void GameManager::activateSuitPower(const Card &card)
{
    // 注意：Card 是类名，要用传进来的小写参数 card.suit
    if(CurrentBoss->suit == card.suit){
        emit battleLog("免疫：Boss免疫了相同花色的特效！");
        return;
    }

    switch(card.suit)
    {
        case Suit::Hearts: {
            // 从弃牌堆随机选取该数值的卡牌，塞回抽牌堆底部 (PlayerDeck 的开头)
            int healVal = card.playValue();
            std::mt19937 g(std::random_device{}());
            std::shuffle(DiscardPile.begin(), DiscardPile.end(), g);
            int recoverCount = std::min(healVal, static_cast<int>(DiscardPile.size()));
            emit battleLog(QString("❤️ 红桃治疗：从弃牌堆恢复了 %1 张牌").arg(recoverCount));
            for (int i = 0; i < recoverCount; ++i) {
                PlayerDeck.insert(PlayerDeck.begin(), DiscardPile.back());
                DiscardPile.pop_back();
            }
            break;
        }
        case Suit::Diamonds: {
            // 抽牌堆抽取等同于伤害值的卡牌放入手牌（不超过手牌上限 8 张）
            int drawVal = card.playValue();
            int spaceLeft = 8 - Hand.size();
            int actualDraw = std::min(drawVal, spaceLeft);
            emit battleLog(QString("♦️ 方块抽牌：抽取了 %1 张牌").arg(actualDraw));
            if (actualDraw > 0) {
                drawCards(actualDraw);
            }
            break;
        }
        case Suit::Clubs:
            emit battleLog("♣️ 梅花暴击：此梅花牌伤害翻倍！");
            break;
        case Suit::Spades:
            currentShield += card.playValue();
            emit battleLog(QString("♠️ 黑桃护盾：增加了 %1 点护盾").arg(card.playValue()));
            break;

    }
}

void GameManager::defendCards(const std::vector<Card> &cards)
{
    // 【防守逻辑实现指南】
    // 1. 计算玩家选中的这些卡牌的总防御点数（遍历 cards，把 playValue() 加起来即可，不要乘2）。
    int defendValue = 0;
    for(const Card& c : cards){
        defendValue += c.playValue();
    }
    // 2. 判断总防御点数是否 >= pendingDamage。
    //    如果不够，或者手牌出错了，直接 return;
    if(defendValue < pendingDamage){
        return;
    }
    // 3. 如果防守点数达标了（防守成功！）：
    //    - 调用 removeCardsFromHand(cards) 把手牌扣掉。
    //    - 遍历 cards 把它们扔进弃牌堆 (DiscardPile.push_back)。
    //    - 把 isDefending 恢复为 false，pendingDamage 设为 0。
    //    - 推进回合数 currentRound++。
    //    - (注意：防守弃牌【绝对不会】触发花色特效，它纯粹只是为了丢点数保命！)
    removeCardsFromHand(cards);
    for(const Card& c : cards){
        DiscardPile.push_back(c);
    }
    isDefending = false;
    pendingDamage = 0;
    currentShield = 0; // 防守完毕也清零护盾
    currentRound++;
    
    // 防守完毕后，轮到玩家回合，如果玩家没有手牌可以出，直接算输！
    if (Hand.empty()) {
        gameState = GameState::Defeat;
    }
}

void GameManager::removeCardsFromHand(const std::vector<Card> &cards)
{
    for (const Card& c : cards) {
        // 使用 std::find 查找手牌里第一张一模一样的牌
        auto it = std::find(Hand.begin(), Hand.end(), c);
        if (it != Hand.end()) {
            Hand.erase(it); // 删掉它
        }
    }
}

