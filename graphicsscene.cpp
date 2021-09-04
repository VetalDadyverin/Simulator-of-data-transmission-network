#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) :
     QGraphicsScene()
{
    this->counter = 0;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());// it is your clicked item, you can do everything what you want. for example send it somewhere
    //Router *ell = dynamic_cast<Router *>(item);
    Router *ell = qgraphicsitem_cast<Router *>(item);

    if (mouseEvent->button() == Qt::LeftButton && item != nullptr){

        ell->setCursor(QCursor(Qt::ClosedHandCursor));
        left_cursor = true;
    }
    if (mouseEvent->button() == Qt::RightButton && item != nullptr)
    {


        if(counter == 1){
            x2 = ell->get_point().rx();
            y2 = ell->get_point().ry();
            counter = 0;
            lines[lines.size()-1].set_second(ell->get_id());
            lines[lines.size()-1]._line.setLine(x1,y1,x2,y2);
            ell->add_connected(lines[lines.size()-1].get_id());
            qDebug() << "second id = " << lines[lines.size()-1].get_second();
            qDebug() << "second = " << lines[lines.size()-1].get_line();
        }else{
            if(counter == 0){
                line _line;
                _line.id = lines.size();
                _line.first = ell->get_id();
                x1 = ell->get_point().rx();
                y1 = ell->get_point().ry();
                counter ++;
                lines.push_back(_line);
                ell->add_connected(_line.get_id());
                qDebug() << "first id = " << _line.first;
                qDebug() << "first = " << ell->get_point();
            }
        }

    }
    Q_UNUSED(mouseEvent);

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());// it is your clicked item, you can do everything what you want. for example send it somewhere
    Router *ell = qgraphicsitem_cast<Router *>(item);
    if (left_cursor && item != nullptr){
        item->setPos(event->scenePos());
        ell->set_point(item->scenePos().rx(),event->scenePos().ry());
        repaint_lines(ell);

    }
    Q_UNUSED(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());// it is your clicked item, you can do everything what you want. for example send it somewhere
    Router *ell = qgraphicsitem_cast<Router *>(item);
    if (event->button() == Qt::LeftButton && item != nullptr){
        ell->setCursor(QCursor(Qt::ArrowCursor));
        left_cursor = false;

        int Num = list.count();
        for(int i = 0; i < Num;i++ ){
            delete list.takeAt(0);
        }
        for(int i = 0; i < get_lines().size();i++ ){
            list << addLine(get_lines()[i].get_line());
        }

    }

    Q_UNUSED(event);
}

QVector<line> GraphicsScene::get_lines(){
    return lines;
}


void GraphicsScene::repaint_lines(Router *ellement){

    if(ellement->get_conected().size() != 0){
        for(int i = 0;i < ellement->get_conected().size(); i++){
            if(lines[ellement->get_conected()[i]].get_first() == ellement->get_id()){
               lines[ellement->get_conected()[i]].set_first_point(ellement->get_point());
            }
            else{
               lines[ellement->get_conected()[i]].set_second_point(ellement->get_point());
            }
        }
        /*int Num = list.count();
        for(int i = 0; i < Num;i++ ){
            delete list.takeAt(0);
        }
        for(int i = 0; i < get_lines().size();i++ ){
            list << addLine(get_lines()[i].get_line());
        }*/
    }
}


