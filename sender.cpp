#include "sender.h"
#include "ui_sender.h"

Sender::Sender(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Sender)
{
    ui->setupUi(this);
    this->resize(600,600);
    this->setFixedSize(600,600);

    ui->comboBox_3->addItem("Logical Mode");
    ui->comboBox_3->addItem("Virtual Mode");
    ui->comboBox_3->addItem("Datagram Mode");
}


Sender::~Sender()
{
    delete ui;
}

void Sender::set_graph(int **_graph){
    this->graph = _graph;
}

void Sender::set_second_graph(int **_graph){
    this->graph2 = _graph;
}

void Sender::set_graph_size(int _size){
    this->graph_size = _size;
    for(int i = 0; i < _size; i++){
        ui->comboBox->addItem(QString::number(i));
        ui->comboBox_2->addItem(QString::number(i));
    }
}

void Sender::set_lines(QVector<line> _lines){
    this->lines = _lines;
}

void Sender::work(){
    Dijkstra *dij = new Dijkstra(graph, graph_size);
    dij->_finding(0,4);
}


void Sender::tcp(int mtu , int mess_size, int start, int end){
    Dijkstra *dij = new Dijkstra(graph, graph_size);
    dij->_finding(start, end);
    int head_size = 20;
    int hole_size = mess_size;
    int size_of_packet = mtu - head_size;
    int timer = 0;
    int buff = 0;
    bool last_packet = false;
    vector<int> way = dij->get_way();
    reverse(way.begin(), way.end());
    vector<int> iversive_way = way;
    reverse(way.begin(), way.end());
    vector<int> dist = dij->get_dist();

    QString packets;

    srand(time(NULL));

    for(int i = 0; i < way.size() - 1; i++){
        packets.push_back("Packet sent from ");
        packets.push_back(QString::number(way[i]));
        packets.push_back(" to ");
        packets.push_back(QString::number(way[i + 1]));
        packets.push_back(" at ");
        packets.push_back(QString::number(timer));
        for(int j = 0; j < lines.size(); j++){
            if( ((lines[j].get_first() == way[i]) || (lines[j].get_second() == way[i]))  &&  ((lines[j].get_second() == way[i + 1]) || (lines[j].get_first() == way[i + 1])) ){
                if(lines[j].get_duplex()){
                    timer += lines[j].get_weight();
                    qDebug() << "In_first = " << timer;
                }
                else{
                    timer += lines[j].get_weight() + 5;
                    qDebug() << "In_second = " << timer;

                }
                break;
            }
        }
        packets.push_back(" \n");
    }
    packets.push_back("Packet reason: Сonnection request\n");
    packets.push_back("__________________________________\n");
    packets.push_back("__________________________________\n");


    for(int i = 0; i < way.size() - 1; i++){
        packets.push_back("Packet sent from ");
        packets.push_back(QString::number(iversive_way[i]));
        packets.push_back(" to ");
        packets.push_back(QString::number(iversive_way[i + 1]));
        packets.push_back(" at ");
        packets.push_back(QString::number(timer));
        for(int j = 0; j < lines.size(); j++){
            if( ((lines[j].get_first() == iversive_way[i]) || (lines[j].get_second() == iversive_way[i])) &&  ((lines[j].get_second() == iversive_way[i + 1]) || (lines[j].get_first() == iversive_way[i + 1])) ){
                if(lines[j].get_duplex()){
                    timer += lines[j].get_weight();
                }
                else{
                    timer += lines[j].get_weight() + 5;

                }
                break;
            }
        }
        packets.push_back(" \n");
    }
    packets.push_back("Packet reason: Agree connection\n");
    packets.push_back("__________________________________\n");
    packets.push_back("__________________________________\n");
    qDebug() << packets;

    int counter_pac = 1;
    int reject_count = 0;
    while(hole_size > 0){
        for(int i = 0; i < way.size() - 1; i++){
            packets.push_back("Packet sent from ");
            packets.push_back(QString::number(way[i]));
            packets.push_back(" to ");
            packets.push_back(QString::number(way[i + 1]));
            packets.push_back(" at ");
            packets.push_back(QString::number(timer));
            qDebug() << "Packet sent from " << way[i] << " to " << way[i + 1] << " at " << timer;
            for(int j = 0; j < lines.size(); j++){
                if( ((lines[j].get_first() == way[i]) || (lines[j].get_second() == way[i]))  &&  ((lines[j].get_second() == way[i + 1]) || (lines[j].get_first() == way[i + 1])) ){
                    if(lines[j].get_duplex()){
                        timer += lines[j].get_weight();

                    }
                    else{
                        timer += lines[j].get_weight() + 5;


                    }

                    break;
                }
            }
            packets.push_back(" \n");
        }
        qDebug() << "Info packet " << counter_pac ;
        packets.push_back("Info packet ");
        packets.push_back(QString::number(counter_pac));
        packets.push_back(" \n");
        packets.push_back("__________________________________\n");
        packets.push_back("__________________________________\n");


        for(int i = 0; i < iversive_way.size() - 1; i++){
            packets.push_back("Packet sent from ");
            packets.push_back(QString::number(iversive_way[i]));
            packets.push_back(" to ");
            packets.push_back(QString::number(iversive_way[i + 1]));
            packets.push_back(" at ");
            packets.push_back(QString::number(timer));
            qDebug() << "Packet sent from " << iversive_way[i] << " to " << way[i + 1] << " at " << timer;
            for(int j = 0; j < lines.size(); j++){
                if( ((lines[j].get_first() == iversive_way[i]) || (lines[j].get_second() == iversive_way[i]))  &&  ((lines[j].get_second() == iversive_way[i + 1]) || (lines[j].get_first() == iversive_way[i + 1])) ){
                    if(lines[j].get_duplex()){
                        timer += lines[j].get_weight();

                    }
                    else{
                        timer += lines[j].get_weight() + 5;


                    }

                    break;
                }
            }
            packets.push_back(" \n");
        }


        buff = rand() % ((99 + 1) - 1) + 1;
        //qDebug() << "B_U_F_F_ = " << buff;
        if(buff > 89){
            qDebug() << "Reject packet " << counter_pac ;
            packets.push_back("Reject packet ");
            packets.push_back(QString::number(counter_pac));
            packets.push_back(" \n");
            packets.push_back("__________________________________\n");
            packets.push_back("__________________________________\n");
            reject_count++;
        }
        else{
            qDebug() << "Accept packet " << counter_pac ;
            packets.push_back("Accept packet ");
            packets.push_back(QString::number(counter_pac));
            packets.push_back(" \n");
            packets.push_back("__________________________________\n");
            packets.push_back("__________________________________\n");
            counter_pac++;
            hole_size -= size_of_packet;
        }
        qDebug() << "hole_size = " << hole_size;

    }

    for(int i = 0; i < way.size() - 1; i++){
        packets.push_back("Packet sent from ");
        packets.push_back(QString::number(way[i]));
        packets.push_back(" to ");
        packets.push_back(QString::number(way[i + 1]));
        packets.push_back(" at ");
        packets.push_back(QString::number(timer));
        for(int j = 0; j < lines.size(); j++){
            if( ((lines[j].get_first() == way[i]) || (lines[j].get_second() == way[i]))  &&  ((lines[j].get_second() == way[i + 1]) || (lines[j].get_first() == way[i + 1])) ){
                if(lines[j].get_duplex()){
                    timer += lines[j].get_weight();
                    //qDebug() << "In_first = " << timer;
                }
                else{
                    timer += lines[j].get_weight() + 5;
                    //qDebug() << "In_second = " << timer;

                }

                break;
            }
        }
        packets.push_back(" \n");
    }
    packets.push_back("Packet reason: Disconnect request\n");
    packets.push_back("__________________________________\n");
    packets.push_back("__________________________________\n");


    for(int i = 0; i < way.size() - 1; i++){
        packets.push_back("Packet sent from ");
        packets.push_back(QString::number(iversive_way[i]));
        packets.push_back(" to ");
        packets.push_back(QString::number(iversive_way[i + 1]));
        packets.push_back(" at ");
        packets.push_back(QString::number(timer));
        for(int j = 0; j < lines.size(); j++){
            if( ((lines[j].get_first() == iversive_way[i]) || (lines[j].get_second() == iversive_way[i])) &&  ((lines[j].get_second() == iversive_way[i + 1]) || (lines[j].get_first() == iversive_way[i + 1])) ){
                if(lines[j].get_duplex()){
                    timer += lines[j].get_weight();
                }
                else{
                    timer += lines[j].get_weight() + 5;

                }

                break;
            }
        }
        packets.push_back(" \n");
    }
    packets.push_back("Packet reason: Agree disconnect\n");
    packets.push_back("__________________________________\n");
    packets.push_back("__________________________________\n");
    this->output = packets;
    QString _infobox;
    _infobox.push_back("Message from ");
    _infobox.push_back(QString::number(start));
    _infobox.push_back(" to ");
    _infobox.push_back(QString::number(end));
    _infobox.push_back("\n");
    _infobox.push_back("Length of the way: ");
    _infobox.push_back(QString::number(dist[end]));
    _infobox.push_back("\n");
    _infobox.push_back("Way: ");
    for(int i = 0; i < way.size(); i++){
        _infobox.push_back(QString::number(way[i]));
        if(i != way.size() - 1){
            _infobox.push_back("->");
        }
    }
    _infobox.push_back("\n");
    _infobox.push_back("Mtu: ");
    _infobox.push_back(QString::number(mtu));
    _infobox.push_back("\n");
    _infobox.push_back("Header size: 20 \n");
    _infobox.push_back("Max info size : ");
    _infobox.push_back(QString::number(mtu - 20));
    _infobox.push_back("\n");
    _infobox.push_back("System packet size : 70(for requests)\n");
    _infobox.push_back("Eror ability : 90\n");
    _infobox.push_back("System packets count : ");
    _infobox.push_back(QString::number(counter_pac + reject_count + 3));
    _infobox.push_back("\n");
    _infobox.push_back("Info packets count : ");
    _infobox.push_back(QString::number(counter_pac - 1 + reject_count));
    _infobox.push_back("\n");
    _infobox.push_back("Reject packet count : ");
    _infobox.push_back(QString::number(reject_count));
    _infobox.push_back("\n");
    _infobox.push_back("System packets size : ");
    _infobox.push_back(QString::number((counter_pac + reject_count - 1) * 90 + 280));
    _infobox.push_back("\n");
    _infobox.push_back("Info packets size : ");
    _infobox.push_back(QString::number(mess_size + reject_count * size_of_packet));
    _infobox.push_back("\n");
    _infobox.push_back("Time : ");
    _infobox.push_back(QString::number(timer));
    _infobox.push_back("\n");

    this->infobox = _infobox;
    qDebug() << packets;
}


void Sender::udp(int mtu, int mess_size, int start, int end){
    Dijkstra *dij = new Dijkstra(graph, graph_size);
    dij->_finding(start, end);

    Dijkstra *dij2 = new Dijkstra(graph2, graph_size);
    dij2->_finding(start, end);

    int head_size = 8;
    int hole_size = mess_size;
    int size_of_packet = mtu - head_size;
    int timer = 0;
    int timer2 = 0;


    vector<int> way = dij->get_way();
    vector<int> way2 = dij2->get_way();


    vector<int> dist = dij->get_dist();

    QString packets;

    int counter_pac = 1;
    if(way != way2){


        while(hole_size > 0){
            if(timer > timer2){
                timer2 = timer;
            }
            else{
                timer = timer2;
            }

            for(int i = 0; i < way.size() - 1; i++){
                packets.push_back("Packet sent from ");
                packets.push_back(QString::number(way[i]));
                packets.push_back(" to ");
                packets.push_back(QString::number(way[i + 1]));
                packets.push_back(" at ");
                packets.push_back(QString::number(timer));
                qDebug() << "Packet sent from " << way[i] << " to " << way[i + 1] << " at " << timer;
                for(int j = 0; j < lines.size(); j++){
                    if( ((lines[j].get_first() == way[i]) || (lines[j].get_second() == way[i]))  &&  ((lines[j].get_second() == way[i + 1]) || (lines[j].get_first() == way[i + 1])) ){
                        if(lines[j].get_duplex()){
                            timer += lines[j].get_weight();

                        }
                        else{
                            timer += lines[j].get_weight() + 5;

                        }
                        break;
                    }
                }
                packets.push_back(" \n");
            }
            qDebug() << "Info packet " << counter_pac ;
            packets.push_back("Info packet ");
            packets.push_back(QString::number(counter_pac++));
            hole_size -= size_of_packet;
            packets.push_back(" \n");
            packets.push_back("__________________________________\n");
            packets.push_back("__________________________________\n");
            if(hole_size < 0){
                break;
            }


            for(int i = 0; i < way2.size() - 1; i++){
                packets.push_back("Packet sent from ");
                packets.push_back(QString::number(way2[i]));
                packets.push_back(" to ");
                packets.push_back(QString::number(way2[i + 1]));
                packets.push_back(" at ");
                packets.push_back(QString::number(timer2));
                qDebug() << "Packet sent from " << way2[i] << " to " << way2[i + 1] << " at " << timer2;
                for(int j = 0; j < lines.size(); j++){
                    if( ((lines[j].get_first() == way2[i]) || (lines[j].get_second() == way2[i]))  &&  ((lines[j].get_second() == way2[i + 1]) || (lines[j].get_first() == way2[i + 1])) ){
                        if(lines[j].get_duplex()){
                            timer2 += lines[j].get_weight();

                        }
                        else{
                            timer2 += lines[j].get_weight() + 5;


                        }
                        break;
                    }
                }
                packets.push_back(" \n");
            }

            qDebug() << "Info packet " << counter_pac ;
            packets.push_back("Info packet ");
            packets.push_back(QString::number(counter_pac++));
            packets.push_back(" \n");
            packets.push_back("__________________________________\n");
            packets.push_back("__________________________________\n");
            hole_size -= size_of_packet;



        }
    }
    else{

        int counter_pac = 1;
        while(hole_size > 0){
            if(timer > timer2){
                timer2 = timer;
            }
            else{
                timer = timer2;
            }

            for(int i = 0; i < way.size() - 1; i++){
                packets.push_back("Packet sent from ");
                packets.push_back(QString::number(way[i]));
                packets.push_back(" to ");
                packets.push_back(QString::number(way[i + 1]));
                packets.push_back(" at ");
                packets.push_back(QString::number(timer));
                qDebug() << "Packet sent from " << way[i] << " to " << way[i + 1] << " at " << timer;
                for(int j = 0; j < lines.size(); j++){
                    if( ((lines[j].get_first() == way[i]) || (lines[j].get_second() == way[i]))  &&  ((lines[j].get_second() == way[i + 1]) || (lines[j].get_first() == way[i + 1])) ){
                        if(lines[j].get_duplex()){
                            timer += lines[j].get_weight();

                        }
                        else{
                            timer += lines[j].get_weight() + 5;

                        }
                        break;
                    }
                }
                packets.push_back(" \n");
            }
            qDebug() << "Info packet " << counter_pac ;
            packets.push_back("Info packet ");
            packets.push_back(QString::number(counter_pac++));
            packets.push_back(" \n");
            packets.push_back("__________________________________\n");
            packets.push_back("__________________________________\n");
            hole_size -= size_of_packet;
        }
    }
    this->output = packets;

    QString _infobox;
    _infobox.push_back("Message from ");
    _infobox.push_back(QString::number(start));
    _infobox.push_back(" to ");
    _infobox.push_back(QString::number(end));
    _infobox.push_back("\n");
    _infobox.push_back("Way: ");
    for(int i = 0; i < way.size(); i++){
        _infobox.push_back(QString::number(way[i]));
        if(i != way.size() - 1){
            _infobox.push_back("->");
        }
    }
    _infobox.push_back("\n");
    if(way != way2){
        _infobox.push_back("Way_2: ");
        for(int i = 0; i < way2.size(); i++){
            _infobox.push_back(QString::number(way2[i]));
            if(i != way2.size() - 1){
                _infobox.push_back("->");
            }
        }
        _infobox.push_back("\n");
    }
    _infobox.push_back("Mtu: ");
    _infobox.push_back(QString::number(mtu));
    _infobox.push_back("\n");
    _infobox.push_back("Header size: 8 \n");
    _infobox.push_back("Max info size : ");
    _infobox.push_back(QString::number(size_of_packet));
    _infobox.push_back("\n");
    _infobox.push_back("Eror ability : 90\n");
    _infobox.push_back("System packets count : ");
    _infobox.push_back(QString::number(counter_pac - 1));
    _infobox.push_back("\n");
    _infobox.push_back("Info packets count : ");
    _infobox.push_back(QString::number(counter_pac - 1));
    _infobox.push_back("\n");
    _infobox.push_back("System packets size : ");
    _infobox.push_back(QString::number((counter_pac - 1) * 66));
    _infobox.push_back("\n");
    _infobox.push_back("Info packets size : ");
    _infobox.push_back(QString::number(mess_size));
    _infobox.push_back("\n");
    if(timer2 > timer){
        timer = timer2;
    }
    _infobox.push_back("Time : ");
    _infobox.push_back(QString::number(timer));
    _infobox.push_back("\n");

    this->infobox = _infobox;
}

void Sender::on_pushButton_clicked()
{
    int mtu = ui->lineEdit_6->text().toInt();
    int message = ui->lineEdit_4->text().toInt();
    int start = ui->comboBox->currentText().toInt();
    int end = ui->comboBox_2->currentText().toInt();
    if(ui->comboBox_3->currentText() == "Datagram Mode"){
        udp(mtu,message,start,end);
        ui->textEdit->setText(this->output);
        ui->textEdit_2->setText(this->infobox);
    }
    else{
        tcp(mtu,message,start,end);
        ui->textEdit->setText(this->output);
        ui->textEdit_2->setText(this->infobox);
    }
}
