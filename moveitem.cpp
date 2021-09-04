#include "moveitem.h"


Router::Router(QObject *parent, int type) :
    QObject(parent), QGraphicsItem()
{
    set_id(0);
    set_point(15,15);
    _type = type;
    left_cursor = false;
    _delete = true;


}

Router::~Router()
{

}

QRectF Router::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

int Router::get_id(){
    return this->id;
}

QPoint Router::get_point(){
    return this->circ_point;
}

void Router::set_id(int id){
    this->id = id;
}

void Router::set_point(int x, int y){
    this->circ_point.setX(x);
    this->circ_point.setY(y);
}

void Router::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);
    if(_type == 0){
        painter->setBrush(Qt::green);
        painter->drawEllipse(QRect(-30,-30,60,60));
    }
    else{
        painter->setBrush(Qt::red);
        painter->drawRect(-30,-30,50,50);
    }
    painter->setFont(font);
    painter->drawText(QRect(-40,-40,50,50), Qt::AlignCenter|Qt::AlignVCenter, QString::number(this->id));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Router::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_delete){
        if (left_cursor){
            this->setPos(mapToScene(event->pos()));
            this->set_point(mapToScene(event->pos()).rx(), mapToScene(event->pos()).ry());
            emit node_move();
        }
    }


}

void Router::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(_delete){
        if (event->button() == Qt::LeftButton){
            this->setCursor(QCursor(Qt::ClosedHandCursor));
            left_cursor = true;
        }
        if (event->button() == Qt::RightButton){
            emit right_click();
        }
     }
    else{
        if (event->button() == Qt::LeftButton){
            emit delete_move();
        }
    }
    Q_UNUSED(event);
}

void Router::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(_delete){
        if (event->button() == Qt::LeftButton){
            this->setCursor(QCursor(Qt::ArrowCursor));
            left_cursor = false;
        }
    }


    Q_UNUSED(event);
}


void Router::add_connected(int connection){
    connected_lines.push_back(connection);
}

QVector<int> Router::get_conected(){
    return connected_lines;
}

void Router::get_delete(bool deleter){
    _delete = !_delete;
    qDebug() << _delete;
}


void Router::delete_from_conected(int _id){
    connected_lines.erase(connected_lines.begin() + _id);
}
