#ifndef LINEITEM_H
#define LINEITEM_H
#include"moveitem.h"

class Lineitem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Lineitem(QObject *parent = 0);
    ~Lineitem();
    int get_id();
    int get_line_weight();
    QPoint get_point();
    void set_id(int id);
    void set_line_weight(int weight);
    void set_point(int x, int y);



private:
    int line_id;
    int line_weight;
    QPoint lineitem_point;
    QRectF boundingRect() const;

signals:



private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};


#endif // LINEITEM_H
