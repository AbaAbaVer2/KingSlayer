#ifndef CARDWIDGET_H
#define CARDWIDGET_H
#include <QPushButton>
#include <QToolButton>
#include "card.h"

class CardWidget:public QToolButton
{
    Q_OBJECT
public:
    explicit CardWidget(Card c, QWidget* parent = nullptr);
    Card getCard() const;
    bool getIsSelected() const { return isSelected; }
private:
    bool isSelected; // 是否被选中
    Card card; // 牌的信息
private slots:
    void onClicked(); // 点击事件处理函数
};

#endif // CARDWIDGET_H
