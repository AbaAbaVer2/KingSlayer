#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>

#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CardWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameManager* m_gameManager;
    void updateUI();

    // 界面控件指针
    QTextEdit* logTextEdit;
    QWidget* bossCardContainer; // Boss卡片容器
    QLabel* bossImageLabel;     // Boss图片预留
    QLabel* bossHpLabel;
    QLabel* bossAtkLabel;
    
    QLabel* roundLabel;      // 显示第几回合
    QLabel* shieldLabel;     // 显示当前黑桃护盾
    QLabel* handCountLabel;  // 显示手牌数量
    QPushButton* playCardBtn;// 出牌按钮
    QPushButton* rulesBtn;   // 游戏规则按钮
    QPushButton* drawPileBtn;
    QPushButton* restartBtn; // 重开游戏按钮
    QPushButton* discardPileBtn;
    
    QHBoxLayout* handLayout; // 用于动态存放手牌
    int cheatClickCount = 0; // 记录外挂连击次数

    void setupUI();

private slots:
    void onPlayCardClicked(); // 出牌按钮点击事件
    void onRulesClicked();    // 规则按钮点击事件
    void onDrawPileClicked(); // 点击抽牌堆
    void onDiscardPileClicked(); // 点击弃牌堆
    void onRestartClicked();  // 点击重开游戏

    void onBossTookDamage(int damage); // 触发飘字和震动特效
    void animateCardsFlying(const QList<CardWidget*>& widgets); // 出牌飞行动画
};
#endif // MAINWINDOW_H
