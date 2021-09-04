#ifndef COMPUTER_H
#define COMPUTER_H
#include "moveitem.h"

class Computer : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Computer(QObject *parent = 0);
    ~Computer();
    int get_id();
    QPoint get_point();
    void set_id(int id);
    void set_point(int x, int y);

private:
    int id;
    QPoint circ_point;
    QRectF boundingRect() const;
signals:

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};

#endif // COMPUTER_H
