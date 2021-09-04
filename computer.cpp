#include "computer.h"

Computer::Computer(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    set_id(0);
    set_point(15,15);
}

Computer::~Computer()
{

}

QRectF Computer::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

int Computer::get_id(){
    return this->id;
}

QPoint Computer::get_point(){
    return this->circ_point;
}

void Computer::set_id(int id){
    this->id = id;
}

void Computer::set_point(int x, int y){
    this->circ_point.setX(x);
    this->circ_point.setY(y);
}

void Computer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawRect(-30,-30,60,60);
    painter->drawText(QRect(-30,-30,60,60), Qt::AlignCenter|Qt::AlignVCenter, QString::number(this->id));
    painter->drawLine(QPointF(116,71),QPointF(70,190));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Computer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}

void Computer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Computer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
