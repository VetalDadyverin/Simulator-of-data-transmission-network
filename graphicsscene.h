#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>
#include <QCursor>
#include <QList>
#include "moveitem.h"

/*typedef struct line{
    QLine _line;
    int id;
    int first;
    int second;

    void set_id(int _id){
        id = _id;
    };
    void set_first(int _first){
        first = _first;
    };
    void set_second(int _second){
        second = _second;
    };
    void set_line(int x1, int y1, int x2, int y2){
        _line.setLine(x1, y1, x2, y2);
    };

    void set_first_point(QPoint point){
        _line.setP1(point);
    }

    void set_second_point(QPoint point){
        _line.setP2(point);
    }

    int get_id(){
        return id;
    };
    int get_first(){
        return first;
    };
    int get_second(){
        return second;
    }
    QLine get_line(){
        return _line;
    };

}line;*/



class GraphicsScene :  public QGraphicsScene
{
    Q_OBJECT
    public:
        explicit GraphicsScene(QObject *parent = 0);
        void repaint_lines(Router *ellement);
        QVector<line> get_lines();
        QList<QGraphicsItem *> list;




    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


    private:
        bool left_cursor = false;
        int counter;
        QVector<line> lines;
        int x1;
        int y1;
        int x2;
        int y2;
        Router *previous_node;
        Router *current_node;

};


#endif // GRAPHICSSCENE_H
