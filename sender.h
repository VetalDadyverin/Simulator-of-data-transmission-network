#ifndef SENDER_H
#define SENDER_H

#include "widget.h"
#include "dijkstra_algorithm.h"
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class Sender;
}

class Sender : public QDialog
{
    Q_OBJECT

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();
    void set_graph(int **_graph);
    void set_second_graph(int **_graph);
    void set_graph_size(int _size);
    void set_lines(QVector<line> _lines);
    void work();
    void tcp(int mtu, int mess_size, int start, int end);
    void udp(int mtu, int mess_size, int start, int end);

private:
    Ui::Sender *ui;
    int **graph = 0;
    int **graph2 = 0;
    int graph_size = 0;
    QVector<line> lines;
    QString output;
    QString infobox;

signals:


private slots:


    void on_pushButton_clicked();
};

#endif // SENDER_H
