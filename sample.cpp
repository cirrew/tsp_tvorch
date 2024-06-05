#include "sample.h"
#include <math.h>
TSample::TSample()
{
}

void TSample::setGraph(std::vector<std::vector<int>> s)
{
    graph = s;
}

void TSample::draw(QPainter* p)
{
    count = graph.size();
    QRect r(0,0,500,500);
    qreal cw = 0.5*r.width();
    qreal ch = 0.5*r.height();
    qreal cr = 0.9*(cw>ch?ch:cw);
    qreal a = 2.0*acos(-1.0)/count;
    QPointF *t = new QPointF[count];
    p->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    p->setFont(font);
    std::vector<QPointF> tem;

    for (int i = 0; i<count; ++i)
    {
        QString str;
        t[i] = QPointF(cw+cr*sin(i*a),ch-cr*cos(i*a));
        p->drawEllipse(QPointF(cw+cr*sin(i*a),ch-cr*cos(i*a)),25,25);
        p->drawText(QPointF(cw+cr*sin(i*a)-6,ch-cr*cos(i*a)+6),str.setNum(i+1));
        tem.push_back(QPointF(cw+cr*sin(i*a)-6,ch-cr*cos(i*a)+6));
    }
    for (int i=0; i<count-1; i++)
    {
        for (int j=i+1; j<count; j++)
        {
            int y_offset=0;
            int x_offset=0;
            if (abs(tem[i].x()-tem[j].x())<10)//(tem[i].x()==tem[j].x())
            {
                y_offset=40;
            }
            if (abs(tem[i].y()-tem[j].y())<10)
            {
                x_offset=40;
            }
            if ((graph[i][j]!=0 && graph[j][i]!=0) || (graph[i][j]!=0 && graph[j][i]==0))
            {
                p->drawText(abs(tem[i].x()+tem[j].x())/2+x_offset,abs(tem[i].y()+tem[j].y())/2 - y_offset,QString::number(graph[i][j]));
            }
            if (graph[i][j]==0 && graph[j][i]!=0)
            {
                p->drawText(abs(tem[i].x()+tem[j].x())/2+x_offset,abs(tem[i].y()+tem[j].y())/2 - y_offset,QString::number(graph[j][i]));
            }
        }
    }

    for(int i = 0; i < graph.size(); ++i)
    {
        for(int j = 0; j < graph.size(); ++j)
        {
            if(graph[i][j] > 0)
            {
                if(i == j)
                {
                    p->drawText(QPointF(cw+cr*sin(i*a)+4,ch-cr*cos(i*a)),"*");
                }
                QPoint p1, p2;
                p1.setX(int(t[i].x()));
                p1.setY(int(t[i].y()));
                p2.setX(int(t[j].x()));
                p2.setY(int(t[j].y()));

                if(p1.x() < p2.x())
                {
                    if(p1.y() == p2.y())
                    {
                        p1.setX(t[i].x()+25);
                        p2.setX(t[j].x()-25);
                    }
                    else
                    {
                        p1.setX(t[i].x()+18);
                        p2.setX(t[j].x()-18);
                    }
                }
                if(p1.x() > p2.x())
                {
                    if(p1.y() == p2.y())
                    {
                        p1.setX(t[i].x()-25);
                        p2.setX(t[j].x()+25);
                    }
                    else
                    {
                        p1.setX(t[i].x()-18);
                        p2.setX(t[j].x()+18);
                    }

                }
                if(p1.y() < p2.y())
                {
                    if(p1.x() == p2.x())
                    {
                        p1.setY(t[i].y()+25);
                        p2.setY(t[j].y()-25);
                    }
                    else
                    {
                        p1.setY(t[i].y()+18);
                        p2.setY(t[j].y()-18);
                    }

                }
                if(p1.y() > p2.y())
                {
                    if(p1.x() == p2.x())
                    {
                        p1.setY(t[i].y()-25);
                        p2.setY(t[j].y()+25);
                    }
                    else
                    {
                        p1.setY(t[i].y()-18);
                        p2.setY(t[j].y()+18);
                    }
                }
                QLineF line(p2,p1);

                qreal arrowSize = 10;

                double angle = std::atan2(-line.dy(), line.dx());
                QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                      cos(angle + M_PI / 3) * arrowSize);
                QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                      cos(angle + M_PI - M_PI / 3) * arrowSize);
                QPolygonF arrowHead;
                arrowHead.clear();
                arrowHead << line.p1() << arrowP1 << arrowP2;


                p->drawLine(p1,p2);
                p->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                p->setBrush(QBrush(Qt::black, Qt::SolidPattern));
                if(i!=j)
                {
                p->drawPolygon(arrowHead);
                }
            }
        }
    }

    delete [] t;

}
