#include "lineitem.h"

Lineitem::Lineitem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    line_id = 0;
    line_weight = 0;
}

Lineitem::~Lineitem()
{

}

QRectF Lineitem::boundingRect() const
{
    return QRectF (-20,-20,50,50);
}


int Lineitem::get_id(){
    return this->line_id;
}

int Lineitem::get_line_weight(){
    return this->line_weight;
}

QPoint Lineitem::get_point(){
    return this->lineitem_point;
}

void Lineitem::set_id(int id){
    this->line_id = id;
}

void Lineitem::set_line_weight(int weight){
    this->line_weight = weight;
}

void Lineitem::set_point(int x, int y){
    this->lineitem_point.setX(x);
    this->lineitem_point.setY(y);
}

void Lineitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    //painter->drawRect(-30,-30,30,30);
    painter->setFont(font);
    painter->drawText(QRect(-30,-30,30,30), Qt::AlignCenter|Qt::AlignVCenter, QString::number(this->line_weight));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void Lineitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() == Qt::LeftButton){
        this->setCursor(QCursor(Qt::ClosedHandCursor));

    }
    if (event->button() == Qt::RightButton){

    }
    Q_UNUSED(event);
}

void Lineitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() == Qt::LeftButton){
        this->setCursor(QCursor(Qt::ArrowCursor));

    }

    Q_UNUSED(event);
}
