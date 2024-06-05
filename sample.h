#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>

class TSample
{
    int count;
     std::vector <std::vector<int>> graph;
public:
    void setGraph(std::vector <std::vector<int>>);
    TSample();
    void draw(QPainter*);
};

#endif // SAMPLE_H
