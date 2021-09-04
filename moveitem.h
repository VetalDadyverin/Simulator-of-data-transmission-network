#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QPoint>
#include <QString>
#include <QPen>
#include <QFont>



class Router : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Router(QObject *parent = 0,int type = 0);
    ~Router();
    int get_id();
    QVector<int> get_conected();
    QPoint get_point();
    void set_id(int id);
    void set_point(int x, int y);
    void add_connected(int connection);
    void delete_from_conected(int _id);


private:
    int id;
    int _type;
    bool left_cursor;
    bool _delete;
    QVector<int> connected_lines;
    QPoint circ_point;
    QRectF boundingRect() const;

signals:
    void right_click();
    void node_move();
    void delete_move();


private slots:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void get_delete(bool deleter);
};


typedef struct line{
    QLine _line;
    int id;
    int first;
    int second;
    int weight;
    bool regular = true;
    bool duplex = true;

    void set_regular(bool reg){
        regular = reg;
    }

    void set_duplex(bool dup){
        duplex = dup;
    }

    void set_weight(int _weight){
        weight = _weight;
    }

    void set_id(int _id){
        id = _id;
    }
    void set_first(int _first){
        first = _first;
    }
    void set_second(int _second){
        second = _second;
    }
    void set_line(int x1, int y1, int x2, int y2){
        _line.setLine(x1, y1, x2, y2);
    }

    void set_first_point(QPoint point){
        _line.setP1(point);
    }

    void set_second_point(QPoint point){
        _line.setP2(point);
    }

    bool get_regular(){
        return regular;
    }

    bool get_duplex(){
        return duplex;
    }

    int get_weight(){
        return weight;
    }

    int get_id(){
        return id;
    }
    int get_first(){
        return first;
    }
    int get_second(){
        return second;
    }
    QLine get_line(){
        return _line;
    }

}line;

#endif // MOVEITEM_H
