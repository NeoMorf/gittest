#include <QtWidgets>
#include <QDebug>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <QRandomGenerator>

// ======================================================================
class PainterPathWidget : public QWidget
{
protected:
    virtual void paintEvent(QPaintEvent*)
      {

        QPainterPath path;

        //QPainter painter1(this);
        //painter1.setPen(QPen(Qt::black, 3));

        int x[3],y[3];
        int xp, yp, xmin, ymin, d, m;

        x[0] = 150; y[0] = 150; //координаты центра 1 окружности
        x[1] = 250; y[1] = 150;
        x[2] = 200; y[2] = 250;

        QPointF ce1(x[0], y[0]);
        QPointF ce2(x[1], y[1]);
        QPointF ce3(x[2], y[2]);

        path.addEllipse(ce1,100,100);   //добавить круг се1 - центр, большая полуось, малая полуось
        path.addEllipse(ce2,100,100);
        path.addEllipse(ce3,100,100);

        int rr = 10000;  //квадрат радиуса окружности
        int n = 10000; //количество случайных бросков

        xmin = x[0]-100;    //описываем квадрат около первой окружности
        ymin = y[0]-100;    //если радиусы разные, то описывать необходимо вокруг самой малой

        qDebug() << xmin << ymin;

        d =100*2;
        m = 0;  // m - число точек, которые попали в зону тройного обзора

        for (int i=0; i<n; i++)     //цикл где n - количество бросков точек
        {
            QPainter painter1(this);
            painter1.setPen(QPen(Qt::black, 3));

            xp = qrand()%d+xmin;    //координаты точки, которую бросаем случайным образом
            yp = qrand()%d+ymin;    //случаную область ограничиваем нашим квадратом

            //qDebug() << xp << yp;
            //qDebug() << qrand()%d;

            for (int j=0; j<3; j++)     //проверка на принадлежность к каждой из трёх окружностей
                {
                if ((pow((xp-x[j]),2)+pow((yp-y[j]),2)) > rr)
                {   painter1.setPen(QPen(Qt::green, 3));
                    painter1.drawPoint(QPointF(xp, yp));
                    goto NotInCircle;}
                }

            painter1.drawPoint(QPointF(xp, yp));
            m++;

            qDebug() << "M=" << m;

            NotInCircle: continue;
        }

        qDebug() << "S = " << pow(d,2)*m/n;     //вывод площади тройного обзора


        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::blue, 6));
        painter.drawPath(path);
    }

public:
    PainterPathWidget(QWidget* pwgt = 0) : QWidget(pwgt)
    {
    }
};

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    PainterPathWidget wgt;

    wgt.resize(400, 400);
    wgt.show();

    return app.exec();
}
