#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLine>
#include <QVector>
#include <moveitem.h>
#include <lineitem.h>
#include <QGraphicsScene>
#include <QObject>
#include <cstdlib>
#include <ctime>
#include<sender.h>

namespace Ui {
class Widget;
}

 int randoming(int low, int high);

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void repaintlines();
    void fill_for_random();
    int** form_graph(bool flug);
    bool sender_();
    int node_size();
    QVector<line> get_lines();




signals:
    void delete_click_(bool deleter);

public slots:
    void openNewWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void add_line();

    void get_new_point();

    void find_for_del();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

protected:

    void paintEvent(QPaintEvent *event) ;

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QVector<Router*> nodes;
    QVector<Lineitem *> lineitems;
    QVector<line> lines;
    QVector<int> for_random;
    QList<QGraphicsItem *> list;
    int id;
    int id_line;
    int counter;
    bool connect;
    bool connect_reg;
    bool connect_duplex;
    bool connect_reg_duplex;
    bool _delete;
    bool draw;
    int x1;
    int y1;
    int x2;
    int y2;
    int **graph;
    bool _sender;
};

#endif // WIDGET_H
