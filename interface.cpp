#include "interface.h"

GetMatrix curren_matr;

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("TSP");
    setFixedSize(500,400);

    open_file_btn = new QPushButton("открыть граф\nиз файла", this);
    open_file_btn->setGeometry(100,145,100,35);

    create_new_graph = new QPushButton("создать пустой\nграф", this);
    create_new_graph->setGeometry(250, 145, 100, 35);

    open_file_tsp=new QPushButton("коммивояжёр", this);
    open_file_tsp->setGeometry(100,200, 100, 30);
    open_file_tsp->setEnabled(false);

    out_graph=new QPushButton("вывести граф", this);
    out_graph->setGeometry(100, 250, 100, 30);
    out_graph->setEnabled(false);

    add_edge=new QPushButton("добавить ребро", this);
    add_edge->setGeometry(100, 300, 100, 30);
    add_edge->setEnabled(false);

    add_node=new QPushButton("добавить узел", this);
    add_node->setGeometry(250, 200, 100, 30);
    add_node->setEnabled(false);

    del_edge=new QPushButton("удалить ребро", this);
    del_edge->setGeometry(250, 250, 100, 30);
    del_edge->setEnabled(false);

    del_node=new QPushButton("удалить узел", this);
    del_node->setGeometry(250, 300, 100, 30);
    del_node->setEnabled(false);

    sample = new TSample();
    canvas = new TCanvas(sample);
    tsp_lenght=new QLabel(this);
    tsp_lenght->setGeometry(10,100,100,30);
    tsp_result=new QLabel(this);
    tsp_result->setGeometry(10, 50, 200, 60);
    message_thing=new QLabel(this);
    message_thing->setGeometry(10,50, 300, 100);
    canvas->setAttribute( Qt::WA_QuitOnClose, false );

    connect(open_file_btn, SIGNAL(pressed()),this,SLOT(openFile()));
    connect(open_file_tsp, SIGNAL(pressed()), this, SLOT(open_tsp()));
    connect(out_graph, SIGNAL(pressed()),this,SLOT(show_graph()));
    connect(add_node, SIGNAL(pressed()), this, SLOT(ad_nod()));
    connect(add_edge, SIGNAL(pressed()), this, SLOT(ad_ed()));
    connect(del_edge, SIGNAL(pressed()), this, SLOT(de_ed()));
    connect(del_node, SIGNAL(pressed()), this, SLOT(de_nod()));
    connect(create_new_graph, SIGNAL(pressed()), this, SLOT(new_matr()));
}

TInterface::~TInterface()
{
    delete open_file_btn;
    delete sample;
    delete canvas;
    delete open_file_tsp;
    delete tsp_lenght;
    delete tsp_result;
}

void TInterface::openFile()
{
    QString fname = QFileDialog::getOpenFileName(this, "Файл", "C://");
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    GetMatrix matrix(fname);
    int getResult = matrix.checkMatrix();

    if(getResult == 0) //если файл с матрицей корректный
    {
        curren_matr=matrix;
        open_file_tsp->setEnabled(true);
        out_graph->setEnabled(true);
        add_edge->setEnabled(true);
        add_node->setEnabled(true);
        del_edge->setEnabled(true);
        del_node->setEnabled(true);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Неверный формат матрицы");
        messageBox.setFixedSize(500,200);
    }
}

void TInterface::show_graph()
{
    sample->setGraph(curren_matr.getFullMatrix());
    canvas->update();
    canvas->show();
}

void TInterface::open_tsp()
{
    curren_matr.tsp();
    std::vector<int> tmp_path = curren_matr.get_path();
    int tmp_rasst = curren_matr.get_rasst();
    QString res;
    res=res+"Проход по задаче коммивояжёра:\n";
    res+=QString::number(tmp_path[0]+1);
    for (int i=1; i<tmp_path.size();i++)
    {
        res=res+"->"+QString::number(tmp_path[i]+1);
    }
    res=res+"\nВычисленные затраты: "+QString::number(tmp_rasst);
    message_thing->setText(res);
}

void TInterface::ad_nod()
{
    curren_matr.ad_new_node_to_matr();
    message_thing->setText("Добавлен новый узел");
}

void TInterface::ad_ed()
{
    bool ok1, ok2, ok3;
    int vert1 = QInputDialog::getInt(this, "Окно ввода", "Узел 1:", 1, 1, curren_matr.getFullMatrix().size(), 1, &ok1);
    if (ok1)
    {
        int vert2 = QInputDialog::getInt(this, "Окно ввода", "Узел 2:", 1, 1, curren_matr.getFullMatrix().size(), 1, &ok2);
        if (ok2)
        {
            int weight = QInputDialog::getInt(this, "Окно ввода", "Вес ребра:", 0, 0, 10000, 1, &ok3);
            if (ok3)
            {
                int msg = curren_matr.ad_new_edge_to_matr(vert1, vert2, weight);
                switch (msg)
                {
                case 1:
                {
                    message_thing->setText("Новое ребро успешно добавлено");
                    break;
                }
                case 2:
                {
                    message_thing->setText("Рёбра равны");
                    break;
                }
                case 3:
                {
                    message_thing->setText("На указанном месте узел уже существует");
                    break;
                }
                case 4:
                {
                    message_thing->setText("Указан пустой вес ребра");
                    break;
                }
                }
            }
        }
    }
}
void TInterface::de_ed()
{
    bool ok1, ok2;
    int vert1 = QInputDialog::getInt(this, "Окно ввода", "Узел 1:", 1, 1, curren_matr.getFullMatrix().size(), 1, &ok1);
    if (ok1)
    {
        int vert2 = QInputDialog::getInt(this, "Окно ввода", "Узел 2:", 1, 1, curren_matr.getFullMatrix().size(), 1, &ok2);
        if (ok2)
        {
            int msg = curren_matr.del_an_edge(vert1, vert2);
            switch (msg)
            {
            case 1:
            {
                message_thing->setText("Указанное ребро успешно удалено");
                break;
            }
            case 2:
            {
                message_thing->setText("Указанного ребра уже не существует");
                break;
            }
            }
        }
    }
}

void TInterface::de_nod()
{
    bool ok;
    int vert = QInputDialog::getInt(this, "Окно ввода", "Узел:", 1, 1, curren_matr.getFullMatrix().size(), 1, &ok);
    if (ok)
    {
        curren_matr.del_a_node(vert);
        message_thing->setText("Указанный узел успешно удалён");
    }
}

void TInterface::new_matr()
{
    bool ok;
    int new_siz = QInputDialog::getInt(this, "Окно", "Количество узлов:", 2, 2, 13, 1, &ok);
    if (ok)
    {
        curren_matr.create_empty(new_siz);
        message_thing->setText("Создан новый пустой граф");
        open_file_tsp->setEnabled(true);
        out_graph->setEnabled(true);
        add_edge->setEnabled(true);
        add_node->setEnabled(true);
        del_edge->setEnabled(true);
        del_node->setEnabled(true);
    }
}
