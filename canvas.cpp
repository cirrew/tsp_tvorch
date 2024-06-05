#include "canvas.h"

TCanvas::TCanvas(TSample* f, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("graph");
    s = f;
    setFixedSize(500,500);
}

TCanvas::~TCanvas()
{

}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p);
    p.end();
}
