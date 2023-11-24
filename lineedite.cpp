#include "lineedite.h"

edite::edite()
{

}
edite::edite(QLabel *l,QRect pos)
{
    QFont font;
    font.setPointSize(14);
    ed=new QLineEdit(l);
    lab=new QLabel (ed);
    ed->setGeometry(pos);
    ed->setStyleSheet("background-color:transparent;border:none;");
    lab->resize(pos.width(),3);
    lab->move(0,pos.height()-3);
    //lab->setStyleSheet("background-color:red;");
    ed->setFont(font);
   // ed->setTextMargins(55,0,0,0);
}
void edite :: set_text(QString ch)
{
    ed->setText(ch);
}

