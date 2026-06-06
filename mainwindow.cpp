#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cardwidget.h"
#include "playvalidator.h"
#include <QDialog>
#include <QFile>
#include <QTextBrowser>
#include <QIcon>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // 1. 初始化游戏核心逻辑
  m_gameManager = new GameManager();

  // 2. 搭建界面空壳
  setupUI();

  // 3. 将真实数据刷到界面上
  updateUI();
}

void MainWindow::setupUI() {
  // 获取中心部件
  QWidget *central = ui->centralwidget;
  QVBoxLayout *mainLayout = new QVBoxLayout(central);

  this->setMinimumSize(1024, 768);
  this->setWindowIcon(QIcon(":/card/icon.jpg"));
  this->setWindowTitle("弑君者 KingSlayer");

  // ================= 1. 上半部分：日志区 + Boss区 =================
  QHBoxLayout *topLayout = new QHBoxLayout();

  // 1.1 左侧：效果（战斗日志）
  QVBoxLayout *logLayout = new QVBoxLayout();
  logLayout->addWidget(new QLabel("效果 / 战斗记录："));
  logTextEdit = new QTextEdit();
  logTextEdit->setReadOnly(true);
  logTextEdit->setFixedWidth(350); // 增大日志框宽度
  logLayout->addWidget(logTextEdit);

  rulesBtn = new QPushButton("📜 游戏规则");
  rulesBtn->setStyleSheet(
      "background-color: #89B4FA; color: #11111B; font-weight: bold; "
      "font-size: 16px; border-radius: 5px; padding: 5px;");
  logLayout->addWidget(rulesBtn);

  topLayout->addLayout(logLayout);

  topLayout->addStretch(); // 推向两边

  // 1.2 中间：Boss信息区
  QVBoxLayout *bossAreaLayout = new QVBoxLayout();

  // 用一个容器把图片和文字包起来当作 Boss 卡片
  bossCardContainer = new QWidget();
  bossCardContainer->setFixedSize(180, 260); // 调大宽和高

  QVBoxLayout *bossCardLayout = new QVBoxLayout(bossCardContainer);

  // 图片预留区 (全卡面)
  bossImageLabel = new QLabel("Boss 全卡面\n点阵图预留");
  bossImageLabel->setAlignment(Qt::AlignCenter);
  bossImageLabel->setStyleSheet(
      "background-color: rgba(0,0,0,0.3); border: 2px dashed #A6E3A1; "
      "border-radius: 8px; color: #A6E3A1; font-weight: bold;");

  bossCardLayout->addWidget(bossImageLabel); // 移除文字区，让图片填满

  bossHpLabel = new QLabel("HP: 20");
  bossAtkLabel = new QLabel("ATK: 10");
  QFont statFont = bossHpLabel->font();
  statFont.setPointSize(12);
  bossHpLabel->setFont(statFont);
  bossAtkLabel->setFont(statFont);

  // 将 Boss卡片 和 HP/ATK 水平排列
  QHBoxLayout *bossStatsLayout = new QHBoxLayout();
  bossStatsLayout->addWidget(bossCardContainer);

  QVBoxLayout *statsLayout = new QVBoxLayout();
  statsLayout->addWidget(bossHpLabel);
  statsLayout->addWidget(bossAtkLabel);
  bossStatsLayout->addLayout(statsLayout);

  bossAreaLayout->addLayout(bossStatsLayout);
  topLayout->addLayout(bossAreaLayout);
  topLayout->addStretch();

  // ================= 2. 下半部分：牌堆 + 手牌区 =================
  QVBoxLayout *bottomAreaLayout = new QVBoxLayout();

  // 抽牌堆和弃牌堆放在手牌上方
  QHBoxLayout *deckLayout = new QHBoxLayout();

  drawPileBtn = new QPushButton("抽牌堆\n(32)");
  drawPileBtn->setFixedSize(60, 60); // 缩小按钮

  playCardBtn = new QPushButton("出牌");
  playCardBtn->setFixedSize(120, 50);
  playCardBtn->setStyleSheet(
      "background-color: #A6E3A1; color: #11111B; font-weight: bold; "
      "font-size: 20px; border-radius: 10px;");

  discardPileBtn = new QPushButton("弃牌堆\n(0)");
  discardPileBtn->setFixedSize(60, 60); // 缩小按钮

  deckLayout->addWidget(drawPileBtn);
  deckLayout->addStretch();
  deckLayout->addWidget(playCardBtn);
  deckLayout->addSpacing(40);
  deckLayout->addWidget(discardPileBtn);
  
  // 移除了这里的 restartBtn

  // 中间偏下：手牌布局
  handLayout = new QHBoxLayout();
  handLayout->setAlignment(Qt::AlignCenter); // 手牌居中
  // (注意：这里不再写死生成假牌，而是交给 updateUI 来生成真实手牌)

  bottomAreaLayout->addLayout(deckLayout);
  bottomAreaLayout->addSpacing(20);

  shieldLabel = new QLabel("🛡️ 护盾: 0");
  shieldLabel->setAlignment(Qt::AlignCenter);
  shieldLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: "
                             "#89B4FA; background: transparent;");
  bottomAreaLayout->addWidget(shieldLabel);

  QHBoxLayout* lowestLayout = new QHBoxLayout();
  handCountLabel = new QLabel("手牌: 0/8");
  handCountLabel->setAlignment(Qt::AlignCenter);
  handCountLabel->setFixedSize(120, 60);
  handCountLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #A6E3A1; background: rgba(0,0,0,0.3); border-radius: 10px; font-family: 'Consolas', 'Microsoft YaHei';");
  lowestLayout->addWidget(handCountLabel);
  lowestLayout->addStretch();
  lowestLayout->addLayout(handLayout);
  lowestLayout->addStretch();
  
  // 为了让 handLayout 继续居中，我们需要右边也有一个 120 宽的空间
  QWidget* rightContainer = new QWidget();
  rightContainer->setFixedSize(120, 60);
  QHBoxLayout* rightLayout = new QHBoxLayout(rightContainer);
  rightLayout->setContentsMargins(0, 0, 0, 0);
  rightLayout->addStretch(); // 把重开按钮推到最右边
  
  restartBtn = new QPushButton("🔄");
  restartBtn->setFixedSize(60, 60);
  restartBtn->setStyleSheet("background-color: #F9E2AF; color: #11111B; font-weight: bold; font-size: 32px; border-radius: 30px;");
  rightLayout->addWidget(restartBtn);
  lowestLayout->addWidget(rightContainer);
  
  bottomAreaLayout->addLayout(lowestLayout);

  // ================= 3. 组装主布局 =================
  roundLabel = new QLabel("Round 1");
  roundLabel->setAlignment(Qt::AlignCenter);
  roundLabel->setStyleSheet(
      "font-size: 48px; font-weight: bold; color: #F38BA8; font-family: "
      "'Consolas', 'Microsoft YaHei'; border: none; background: transparent;");

  mainLayout->addLayout(topLayout);
  mainLayout->addStretch();
  mainLayout->addWidget(roundLabel);
  mainLayout->addStretch();
  mainLayout->addLayout(bottomAreaLayout);

  // ================= 4. 设置 QSS 炫酷皮肤 =================
  // 设置对象名以便 QSS 精准定位
  bossCardContainer->setObjectName("bossCard");
  drawPileBtn->setObjectName("drawPile");
  discardPileBtn->setObjectName("discardPile");

  QString qss = R"(
        /* 全局深邃暗黑风格 */
        QWidget {
            background-color: #1E1E2E;
            color: #CDD6F4;
            font-family: "Microsoft YaHei", "Segoe UI";
        }

        /* 战斗记录区 */
        QTextEdit {
            background-color: #181825;
            border: 2px solid #313244;
            border-radius: 10px;
            padding: 10px;
            font-size: 14px;
        }

        /* Boss卡片样式：暗红渐变，彰显压迫感 */
        QWidget#bossCard {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #F38BA8, stop:1 #313244);
            border: 3px solid #F9E2AF;
            border-radius: 12px;
        }

        /* 属性文本 */
        QLabel {
            font-weight: bold;
            color: #A6E3A1;
        }

        /* 通用卡牌（手牌）按钮 */
        QPushButton, QToolButton {
            background-color: #313244;
            border: 2px solid #45475A;
            border-radius: 12px;
            color: #CDD6F4;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover, QToolButton:hover {
            background-color: #45475A;
            border: 2px solid #89B4FA; /* 悬浮时发出蓝光 */
        }
        QPushButton:pressed, QToolButton:pressed {
            background-color: #585B70;
            border: 2px solid #B4BEFE;
        }

        /* 牌堆按钮专属配色 */
        QPushButton#drawPile {
            background-color: #89DCEB;
            color: #11111B;
            border: 2px solid #74C7D6;
        }
        QPushButton#drawPile:hover { background-color: #94E2D5; }
        
        QPushButton#discardPile {
            background-color: #F38BA8;
            color: #11111B;
            border: 2px solid #EBA0AC;
        }
        QPushButton#discardPile:hover { background-color: #F5C2E7; }
    )";
  this->setStyleSheet(qss);

  // ================= 5. 信号与槽连接 =================
  connect(playCardBtn, &QPushButton::clicked, this,
          &MainWindow::onPlayCardClicked);
  connect(rulesBtn, &QPushButton::clicked, this, &MainWindow::onRulesClicked);
  
  connect(m_gameManager, &GameManager::battleLog, this, [this](QString msg){
      this->logTextEdit->append(msg);
  });
  connect(m_gameManager, &GameManager::bossTookDamage, this, &MainWindow::onBossTookDamage);
  connect(drawPileBtn, &QPushButton::clicked, this, &MainWindow::onDrawPileClicked);
  connect(discardPileBtn, &QPushButton::clicked, this, &MainWindow::onDiscardPileClicked);
  connect(restartBtn, &QPushButton::clicked, this, &MainWindow::onRestartClicked);
}

void MainWindow::onPlayCardClicked() {
  std::vector<Card> selectedCards;

  // 1. 遍历 handLayout 里的所有卡牌控件
  QList<CardWidget*> flyingWidgets;
  for (int i = 0; i < handLayout->count(); ++i) {
    // 拿到布局里的 widget，并尝试转换成 CardWidget
    QWidget *w = handLayout->itemAt(i)->widget();
    CardWidget *cw = qobject_cast<CardWidget *>(w);

    // 如果转换成功，并且这张牌被玩家选中了
    if (cw && cw->getIsSelected()) {
      selectedCards.push_back(cw->getCard());
      flyingWidgets.push_back(cw);
    }
  }

  // 2. 检查玩家到底选了没有
  if (selectedCards.empty()) {
    cheatClickCount++;
    if (cheatClickCount >= 5) {
        cheatClickCount = 0;
        m_gameManager->cheatKillBoss();
        updateUI();
        return;
    }
    logTextEdit->append(QString("【提示】你没有选择任何牌！(%1/5)").arg(cheatClickCount));
    return;
  }
  
  cheatClickCount = 0; // 一旦有正常操作就清零

  // 3. 状态分流判断：防守 vs 攻击
  if (m_gameManager->getIsDefending()) {
    // 玩家正在挨打，需要防守弃牌
    int totalDefendValue = 0;
    for(const Card& c : selectedCards) {
        totalDefendValue += c.playValue();
    }
    
    if (totalDefendValue < m_gameManager->getPendingDamage()) {
        logTextEdit->append(QString("【错误】防守点数不足！需要 %1 点，当前只选了 %2 点。")
                               .arg(m_gameManager->getPendingDamage())
                               .arg(totalDefendValue));
        return;
    }
    
    logTextEdit->append(QString("【防守成功】你丢弃了 %1 张牌，成功抵御了 Boss 的攻击！").arg(selectedCards.size()));
    m_gameManager->defendCards(selectedCards);
    
  } else {
    // 玩家主动出牌攻击
    if (!PlayValidator::isValidPlay(selectedCards)) {
      logTextEdit->append("【错误】" +
                          PlayValidator::getInvalidReason(selectedCards));
      return;
    }

    int damage = PlayValidator::calculateBaseDamage(selectedCards);
    QString logMsg = QString("【合法出牌】你打出了 %1 张牌，基础伤害为: %2")
                         .arg(selectedCards.size())
                         .arg(damage);
    logTextEdit->append(logMsg);

    // 飞行动画（如果是出牌攻击）
    animateCardsFlying(flyingWidgets);
    // 交给 GameManager 结算伤害、发动花色特效和弃牌
    m_gameManager->playCards(selectedCards);
  }

  // 4. 结算完毕后，立刻刷新界面！
  updateUI();
}

void MainWindow::onRulesClicked() {
  QDialog dialog(this);
  dialog.setWindowTitle("游戏规则 (KingSlayer Rules)");
  dialog.resize(600, 700);

  QVBoxLayout layout(&dialog);
  QTextBrowser browser(&dialog);

  QFile file(":/card/rules.md");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QString markdown = QString::fromUtf8(file.readAll());
    browser.setMarkdown(markdown);
  } else {
    browser.setText(
        "无法加载规则文件。请确保 rules.md 已经加入了 "
        "resources.qrc。\n你可以手动打开项目根目录下的 rules.md 阅读。");
  }

  layout.addWidget(&browser);
  dialog.exec();
}

MainWindow::~MainWindow() {
  delete ui;
  delete m_gameManager;
}

void MainWindow::updateUI() {
  // 1. 更新牌堆和弃牌堆的数量
  drawPileBtn->setText(
      QString("抽牌堆\n(%1)").arg(m_gameManager->getDeckSize()));
  discardPileBtn->setText(
      QString("弃牌堆\n(%1)").arg(m_gameManager->getDiscardSize()));

  roundLabel->setText(QString("Round %1").arg(m_gameManager->getRound()));
  shieldLabel->setText(QString("🛡️ 护盾值: %1").arg(m_gameManager->getShield()));
  handCountLabel->setText(QString("手牌: %1/8").arg(m_gameManager->getHand().size()));

  // 根据是否在防守阶段，动态修改按钮样式
  if (m_gameManager->getIsDefending()) {
      playCardBtn->setText(QString("防守弃牌\n(需%1点)").arg(m_gameManager->getPendingDamage()));
      playCardBtn->setStyleSheet("background-color: #F38BA8; color: #11111B; font-weight: bold; font-size: 16px; border-radius: 10px;");
  } else {
      playCardBtn->setText("出牌");
      playCardBtn->setStyleSheet("background-color: #A6E3A1; color: #11111B; font-weight: bold; font-size: 20px; border-radius: 10px;");
  }

  // 2. 清空当前界面上的所有旧手牌控件
  QLayoutItem *child;
  while ((child = handLayout->takeAt(0)) != nullptr) {
    delete child->widget();
    delete child;
  }

  // 3. 遍历 GameManager 里的真实手牌，生成 CardWidget 塞进界面
  const auto &hand = m_gameManager->getHand();
  for (const Card &c : hand) {
    CardWidget *cw = new CardWidget(c, this);
    handLayout->addWidget(cw);
  }

  // 4. 更新 Boss 卡面
  if (m_gameManager->getCurrentBoss().has_value()) {
    Card bossCard = m_gameManager->getCurrentBoss().value();
    QPixmap bossPix(bossCard.imagePath());
    // 让图片按比例缩放填充 Boss 坑位
    bossImageLabel->setPixmap(bossPix.scaled(180, 260, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    bossHpLabel->setText(QString("HP: %1").arg(m_gameManager->getBossHp()));
    bossAtkLabel->setText(QString("ATK: %1").arg(m_gameManager->getBossAtk()));
  }

  // 5. 胜负判定弹窗
  if (m_gameManager->getGameState() == GameState::Win) {
      if (QMessageBox::question(this, "胜利！", "恭喜你击杀了所有的 Boss！你赢了！\n再来一局？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
          m_gameManager->restartGame();
          logTextEdit->clear();
          updateUI();
      } else {
          close();
      }
  } else if (m_gameManager->getGameState() == GameState::Defeat) {
      if (QMessageBox::question(this, "失败！", "很遗憾，你被 Boss 击败了！\n再来一局？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
          m_gameManager->restartGame();
          logTextEdit->clear();
          updateUI();
      } else {
          close();
      }
  }
}

void MainWindow::onDrawPileClicked() {
    QStringList cardsStr;
    for(const Card& c : m_gameManager->getPlayerDeck()) {
        cardsStr << c.toString();
    }
    QMessageBox::information(this, "抽牌堆", "目前抽牌堆还有 " + QString::number(cardsStr.size()) + " 张牌\n\n" + cardsStr.join(", "));
}

void MainWindow::onDiscardPileClicked() {
    QStringList cardsStr;
    for(const Card& c : m_gameManager->getDiscardPile()) {
        cardsStr << c.toString();
    }
    QMessageBox::information(this, "弃牌堆", "目前弃牌堆有 " + QString::number(cardsStr.size()) + " 张牌\n\n" + cardsStr.join(", "));
}

void MainWindow::onRestartClicked() {
    if (QMessageBox::question(this, "重开游戏", "确定要放弃当前局，重新开始吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        m_gameManager->restartGame();
        logTextEdit->clear();
        updateUI();
    }
}

void MainWindow::animateCardsFlying(const QList<CardWidget*>& widgets) {
    if (widgets.isEmpty()) return;
    
    // 获取 Boss 的绝对中心坐标
    QPoint bossCenter = bossImageLabel->mapTo(this, bossImageLabel->rect().center());

    for (CardWidget* cw : widgets) {
        QLabel* dummy = new QLabel(this);
        QPixmap pix(cw->getCard().imagePath());
        dummy->setPixmap(pix.scaled(cw->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        dummy->resize(cw->size());
        
        // 获取卡牌当前的绝对坐标
        QPoint startPos = cw->mapTo(this, QPoint(0,0));
        dummy->move(startPos);
        dummy->show();
        dummy->raise();
        
        QPropertyAnimation* anim = new QPropertyAnimation(dummy, "pos");
        anim->setDuration(400);
        anim->setStartValue(startPos);
        anim->setEndValue(bossCenter - QPoint(dummy->width()/2, dummy->height()/2));
        anim->setEasingCurve(QEasingCurve::InBack);
        
        connect(anim, &QPropertyAnimation::finished, dummy, &QObject::deleteLater);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MainWindow::onBossTookDamage(int damage) {
    if (damage <= 0) return;
    
    // 1. 震动 Boss 图像
    QPropertyAnimation* shake = new QPropertyAnimation(bossImageLabel, "pos");
    shake->setDuration(300);
    QPoint orig = bossImageLabel->pos();
    shake->setStartValue(orig);
    shake->setKeyValueAt(0.2, orig + QPoint(-15, 0));
    shake->setKeyValueAt(0.4, orig + QPoint(15, 0));
    shake->setKeyValueAt(0.6, orig + QPoint(-15, 0));
    shake->setKeyValueAt(0.8, orig + QPoint(15, 0));
    shake->setEndValue(orig);
    shake->start(QAbstractAnimation::DeleteWhenStopped);
    
    // 2. 飘字特效
    QLabel* dmgLabel = new QLabel(QString("-%1").arg(damage), this);
    dmgLabel->setStyleSheet("color: #F38BA8; font-size: 64px; font-weight: bold; font-family: 'Arial Black';");
    dmgLabel->adjustSize();
    
    QPoint startPos = bossImageLabel->mapTo(this, QPoint(bossImageLabel->width()/2 - dmgLabel->width()/2, bossImageLabel->height()/2));
    dmgLabel->move(startPos);
    dmgLabel->show();
    dmgLabel->raise();
    
    QParallelAnimationGroup* group = new QParallelAnimationGroup(dmgLabel);
    
    QPropertyAnimation* moveAnim = new QPropertyAnimation(dmgLabel, "pos");
    moveAnim->setDuration(800);
    moveAnim->setStartValue(startPos);
    moveAnim->setEndValue(startPos - QPoint(0, 150));
    moveAnim->setEasingCurve(QEasingCurve::OutQuad);
    
    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(dmgLabel);
    dmgLabel->setGraphicsEffect(opacity);
    QPropertyAnimation* fadeAnim = new QPropertyAnimation(opacity, "opacity");
    fadeAnim->setDuration(800);
    fadeAnim->setStartValue(1.0);
    fadeAnim->setEndValue(0.0);
    
    group->addAnimation(moveAnim);
    group->addAnimation(fadeAnim);
    
    connect(group, &QParallelAnimationGroup::finished, dmgLabel, &QObject::deleteLater);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}
