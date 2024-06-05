#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "getmatrix.h"
#include "sample.h"
#include "canvas.h"

class TInterface : public QWidget
{
    Q_OBJECT

    QPushButton* open_file_btn;
    QPushButton* open_file_tsp;
    QPushButton* create_new_graph;
    QLabel* tsp_result;
    QLabel* tsp_lenght;
    QLabel* message_thing;
    TSample* sample;
    TCanvas* canvas;
    QPushButton* out_graph;
    QPushButton* add_edge;
    QPushButton* add_node;
    QPushButton* del_edge;
    QPushButton* del_node;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void openFile(); //открыть файл с графом
    void new_matr(); //создать пустой граф
    void open_tsp(); //вычислить задачу коммивояжера
    void show_graph(); //вывести граф
    void ad_nod(); //добавить узел
    void ad_ed(); //добавить ребро
    void de_nod(); //удалить узел
    void de_ed(); //удалить ребро
};
#endif // TINTERFACE_H
