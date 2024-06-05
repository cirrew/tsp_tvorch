#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "sample.h"

class TCanvas : public QWidget
{
    Q_OBJECT

    TSample* s;
public:
    TCanvas(TSample*,QWidget *parent = 0);
    ~TCanvas();

protected:
    void paintEvent(QPaintEvent*); //вызов события рисования
};

#endif // VIEWER_H
