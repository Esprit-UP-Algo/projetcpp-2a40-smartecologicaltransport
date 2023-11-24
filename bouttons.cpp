#include "bouttons.h"

boutton::boutton()
{

}
void boutton :: annimer()
{
    QObject :: connect(&t1,&QTimer :: timeout,[&]()
        {
            if(i<50)i++;
            sh->setBlurRadius(i);
            setGraphicsEffect(sh);
        });
   QObject :: connect(&t2,&QTimer :: timeout,[&]()
   {
      if(i>0)i--;
      sh->setBlurRadius(i);
      setGraphicsEffect(sh);
  });
}
bouttons::bouttons()
{

}
bouttons::bouttons(QLabel *l,QRect pos,QString enter,QString leave,QString text)
{
    QFont font;
    font.setPointSize(14);
    b=new QPushButton(l);
    b->setGeometry(pos);
    b->setStyleSheet("QPushButton {"+enter+"}"
                                           "QPushButton:hover{"+leave+"}");
    b->setFont(font);
    b->setText(text);
}
