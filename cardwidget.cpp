#include "cardwidget.h"
#include <QPixmap>
#include <QIcon>
#include "gamemanager.h"

CardWidget::CardWidget(Card c,QWidget* parent):QToolButton(parent),card(c),isSelected(false)
{
    this->setToolButtonStyle(Qt::ToolButtonIconOnly);
    
    // 向肚子里这把牌索要它的图片路径！
    QString imgPath = card.imagePath();
    
    // 读取图片并设置到这个按钮上
    this->setIcon(QIcon(imgPath));
    this->setIconSize(QSize(80, 120)); // 图片大小
    this->setFixedSize(90, 140);       // 按钮本身的大小
    
    // 初始化默认样式：沉在底部
    this->setStyleSheet("margin-top: 20px; margin-bottom: 0px; border: 2px solid #45475A; background-color: rgba(49, 50, 68, 1); border-radius: 12px;");

    // 将按钮自己的 clicked 信号，连接到自己的 onClicked 槽函数上
    connect(this, &QToolButton::clicked, this, &CardWidget::onClicked);
}

Card CardWidget::getCard() const
{
    return card; // 只需返回数据，不要在这里修改游戏逻辑（如 Hand）
}

void CardWidget::onClicked()
{
    isSelected = !isSelected; // 切换选中状态
    
    // 视觉反馈：使用 QSS margin 实现上下移动，避免与布局冲突
    if(isSelected) {
        // margin-bottom: 20px 让图片往上顶
        this->setStyleSheet("margin-top: 0px; margin-bottom: 20px; border: 2px solid #89B4FA; background-color: rgba(49, 50, 68, 1); border-radius: 12px;");
    } else {
        // 恢复默认的沉在底部状态
        this->setStyleSheet("margin-top: 20px; margin-bottom: 0px; border: 2px solid #45475A; background-color: rgba(49, 50, 68, 1); border-radius: 12px;");
    }
}
