#include "widget.h"
#include <QApplication>
#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    if(w.sender_()){
        qDebug() << "SSTTAARRTTEEDD";
        Sender s;
        //s.set_graph(w.form_graph());
        //s.set_graph_size(w.node_size());
        //s.work();
        //s.show();
    }
    /*Sender s;
    s.show();*/
    return a.exec();
}
