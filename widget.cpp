#include "widget.h"
#include "ui_widget.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

int randoming(int low, int high){

    return (rand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Косметическая подготовка приложения
    this->resize(1900,900);          // Устанавливаем размеры окна приложения
    this->setFixedSize(1900,900);

    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    ui->graphicsView->resize(800,800);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0,0,500,500); // Устанавливаем размер сцены

    counter = 0;
    id = 0;
    id_line = 0;
    connect = false;
    connect_reg = false;
    connect_duplex = false;
    connect_reg_duplex = false;
    _delete = true;
    draw = false;
    _sender = false;

    ui->comboBox->addItem("Random");
    ui->comboBox->addItem("3");
    ui->comboBox->addItem("5");
    ui->comboBox->addItem("6");
    ui->comboBox->addItem("8");
    ui->comboBox->addItem("10");
    ui->comboBox->addItem("12");
    ui->comboBox->addItem("17");
    ui->comboBox->addItem("19");
    ui->comboBox->addItem("20");
    ui->comboBox->addItem("25");
    ui->comboBox->addItem("27");
    ui->comboBox->addItem("28");


    fill_for_random();
    srand(time(NULL));

}

void Widget::fill_for_random(){
    for_random.push_back(3);
    for_random.push_back(5);
    for_random.push_back(6);
    for_random.push_back(8);
    for_random.push_back(10);
    for_random.push_back(12);
    for_random.push_back(17);
    for_random.push_back(19);
    for_random.push_back(20);
    for_random.push_back(25);
    for_random.push_back(27);
    for_random.push_back(28);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Router *item = new Router(0,0);        // Создаём графический элемент
    item->set_id(id++);
    item->set_point(randomBetween(30, 470),randomBetween(30, 470));// Устанавливаем случайную позицию элемента
    item->setPos(item->get_point());
    scene->addItem(item);   // Добавляем элемент на графическую сцену
    nodes.push_back(item);

    QObject::connect(item,SIGNAL(right_click()),this,SLOT(add_line()));
    QObject::connect(item,SIGNAL(node_move()),this,SLOT(get_new_point()));
    QObject::connect(this,SIGNAL(delete_click_(bool)),item,SLOT(get_delete(bool)));
    QObject::connect(item,SIGNAL(delete_move()),this,SLOT(find_for_del()));
}


void Widget::on_pushButton_2_clicked()
{
    Router *item = new Router(0,1);        // Создаём графический элемент
    item->set_id(id++);
    item->set_point(randomBetween(30, 470),randomBetween(30, 470));// Устанавливаем случайную позицию элемента
    item->setPos(item->get_point());
    scene->addItem(item);   // Добавляем элемент на графическую сцену
    nodes.push_back(item);   // Добавляем элемент на графическую сцену

    QObject::connect(item,SIGNAL(right_click()),this,SLOT(add_line()));
    QObject::connect(item,SIGNAL(node_move()),this,SLOT(get_new_point()));
    QObject::connect(this,SIGNAL(delete_click_(bool)),item,SLOT(get_delete(bool)));
    QObject::connect(item,SIGNAL(delete_move()),this,SLOT(find_for_del()));
}

void Widget::on_pushButton_3_clicked()
{

    connect = true;

}

void Widget::get_new_point(){
    Router *item = dynamic_cast<Router *>(sender());

    if(item->get_conected().size() != 0){

        for(int i = 0; i < item->get_conected().size(); i++){
            for(int j = 0; j < lines.size(); j++){
                if(item->get_conected()[i] == lines[j].get_id()){
                    if(lines[j].get_first() == item->get_id()){
                        lines[j].set_first_point(item->get_point());

                    }
                    else{
                        lines[j].set_second_point(item->get_point());

                    }
                }
            }

            repaintlines();

        }
    }
}

void Widget::repaintlines(){

    int Num = list.count();
    for(int i = 0; i < Num;i++ ){
        delete list.takeAt(0);
    }

    Num = lineitems.size();
    for(int i = 0; i < Num;i++ ){
        scene->removeItem(lineitems[0]);
        lineitems.removeAt(0);
    }

    QPen pen;
    pen.setWidth(2);

    for(int i = 0; i < lines.size();i++ ){
        if(lines[i].get_regular()){
            if(lines[i].get_duplex()){
                pen.setColor(Qt::red);
            }
            else{
                pen.setColor(Qt::magenta);
            }
        }
        else{
            if(lines[i].get_duplex()){
                pen.setColor(Qt::blue);
            }
            else{
                pen.setColor(Qt::cyan);
            }
        }
        list << scene->addLine(lines[i].get_line(),pen);
        Lineitem *item = new Lineitem();        // Создаём графический элемент
        item->set_id(lines[i].get_id());
        item->set_point((lines[i].get_line().p1().x()+ lines[i].get_line().p2().x())/2 , (lines[i].get_line().p1().y() + lines[i].get_line().p2().y())/2);
        item->setPos(item->get_point());
        item->set_line_weight(lines[i].get_weight());
        scene->addItem(item);
        lineitems.push_back(item);
    }
}


void Widget::add_line()
{

     Router *item = dynamic_cast<Router *>(sender());


     if(counter == 1){
         x2 = item->get_point().rx();
         y2 = item->get_point().ry();
         counter = 0;
         lines[lines.size()-1].set_second(item->get_id());
         lines[lines.size()-1]._line.setLine(x1,y1,x2,y2);
         item->add_connected(lines[lines.size()-1].get_id());
         if(lines[lines.size()-1].first == lines[lines.size()-1].second){
            lines.removeAt(lines.size()-1);
         }
         qDebug() << "second id = " << lines[lines.size()-1].get_second();
         qDebug() << "second = " << lines[lines.size()-1].get_line();
     }else{
         if(counter == 0){
             line _line;
             _line.id = id_line;
             _line.first = item->get_id();
             x1 = item->get_point().rx();
             y1 = item->get_point().ry();
             counter ++;
             lines.push_back(_line);
             item->add_connected(_line.get_id());
             id_line++;
             qDebug() << "first id = " << _line.first;
             qDebug() << "first = " << item->get_point();
         }
     }
}

void Widget::find_for_del(){
    Router *item = dynamic_cast<Router *>(sender());

    QVector<int> buff = item->get_conected();


    for(int i = 0; i < buff.size(); i++){
        for(int j = 0; j < lines.size(); j++){
            if(buff[i] == lines[j].get_id()){

                for(int k = 0; k < nodes.size(); k++){
                    for(int z = 0; z < nodes[k]->get_conected().size(); z++){
                        if(nodes[k]->get_conected()[z] == lines[j].get_id()){
                            nodes[k]->delete_from_conected(z);
                            break;
                        }
                    }
                }
                lines.erase(lines.begin() + j);
                break;
            }
        }

    }

    repaintlines();

    int del = 0;
    for(int j = 0; j < nodes.size(); j++){
        if(item->get_id() == nodes[j]->get_id()){
            del = j;
            break;
        }
    }
    nodes.erase(nodes.begin() + del);
    scene->removeItem(item);

}


void Widget::paintEvent(QPaintEvent *event){
    QPen pen;
    pen.setWidth(2);

    if(connect){
        lines[lines.size()-1].set_regular(true);
        lines[lines.size()-1].set_duplex(true);
        pen.setColor(Qt::red);
        connect = false;
        draw = true;
    }

    if(connect_reg){
        lines[lines.size()-1].set_regular(false);
        lines[lines.size()-1].set_duplex(true);
        pen.setColor(Qt::blue);
        draw = true;
        connect_reg = false;
    }

    if(connect_duplex){

        lines[lines.size()-1].set_regular(true);
        lines[lines.size()-1].set_duplex(false);
        pen.setColor(Qt::magenta);
        connect_duplex = false;
        draw = true;

    }

    if(connect_reg_duplex){
        lines[lines.size()-1].set_regular(false);
        lines[lines.size()-1].set_duplex(false);
        pen.setColor(Qt::cyan);
        draw = true;
        connect_reg_duplex = false;
    }

    if(draw){
        int weight = 0;
        if(ui->comboBox->currentText() == "Random"){
            weight = for_random[randoming(0,11)];
            qDebug() << "Random = " << weight;
        }
        else{
            weight = ui->comboBox->currentText().toInt();
        }

        if(!lines[lines.size()-1].get_regular()){
            weight *= 3;
        }
        lines[lines.size()-1].set_weight(weight);
        list << scene->addLine(lines[lines.size()-1].get_line(),pen);
        Lineitem *item = new Lineitem();        // Создаём графический элемент
        item->set_id(lines[lines.size()-1].get_id());
        item->set_point((lines[lines.size()-1].get_line().p1().x() + lines[lines.size()-1].get_line().p2().x())/2 , (lines[lines.size()-1].get_line().p1().y() + lines[lines.size()-1].get_line().p2().y())/2);
        item->setPos(item->get_point());
        item->set_line_weight(weight);
        scene->addItem(item);
        lineitems.push_back(item);
        draw = false;
    }



}

void Widget::on_pushButton_5_clicked()
{
    emit delete_click_(_delete);
}



void Widget::on_pushButton_6_clicked()
{
    nodes.erase(nodes.begin(), nodes.end());
    lines.erase(lines.begin(), lines.end());
    scene->clear();
    id = 0;
    id_line = 0;
}

void Widget::on_pushButton_4_clicked()
{
    connect_reg = true;
}

void Widget::on_pushButton_7_clicked()
{
    connect_duplex = true;
}

void Widget::on_pushButton_8_clicked()
{
    connect_reg_duplex = true;
}


int** Widget::form_graph(bool flug){

    graph = new int *[nodes.size()];


    for(int i = 0; i < nodes.size(); i++){
        graph[i] = new int[nodes.size()]();
    }
    if(flug){
        for(int i = 0; i < lines.size(); i++){
            graph[lines[i].get_first()][lines[i].get_second()] = lines[i].get_weight();
            graph[lines[i].get_second()][lines[i].get_first()] = lines[i].get_weight();
        }
    }
    else{
        for(int i = 0; i < lines.size(); i++){
            graph[lines[i].get_first()][lines[i].get_second()] = 7;
            graph[lines[i].get_second()][lines[i].get_first()] = 7;
        }
    }


    for(int i = 0; i < nodes.size(); i++){
        for(int j = 0; j < nodes.size(); j++){
         qDebug() << "arr[" << i << "][" << j << "] = " << graph[i][j];
        }
        qDebug() << "_____________________________________";
    }
    return graph;
}



bool Widget::sender_(){
    return _sender;
}

int Widget::node_size(){
    return nodes.size();
}

QVector<line> Widget::get_lines(){
    return lines;
}

void Widget::openNewWindow(){
    Sender s;
    s.set_graph(form_graph(true));
    s.set_second_graph(form_graph(false));
    s.set_graph_size(node_size());
    s.set_lines(get_lines());
    //s.tcp(576, 5000, 0 , 4);
    //s.udp(576, 5000, 0 , 4);
    s.exec();

}

void Widget::on_pushButton_9_clicked()
{

    openNewWindow();

}


