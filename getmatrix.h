#ifndef GETMATRIX_H
#define GETMATRIX_H
#include <QTextStream>
#include <QFile>
#include <vector>

class GetMatrix
{
private:
    int siz; //размер
    std::vector<std::vector<int>> col; //матрица смежности
    QString address; //адрес
    std::vector<int> final_path; //финальный путь прохода
    std::vector<bool>visited; //посещённые узлы
    int rasst; //финальное расстояние
public:
    GetMatrix();
    GetMatrix(QString);
    std::vector<std::vector<int>> getFullMatrix(); //возврат основной матрицы
    int checkMatrix(); //открытие матрицы из файла, проверка матрицы
    int get_rasst();
    void create_empty(int k); //сделать пустую матрицу
    //tsp
    void copy_to_final(std::vector<int> cur_p); //сделать временный маршрут финальным
    int first_min(std::vector<std::vector<int>>& v, int i); //нахождение первого минимального ребра от узла i
    int second_min(std::vector<std::vector<int>>& v, int i);//нахождение второго минимального ребра от узла i
    void tsprec(std::vector<std::vector<int>>& v, int cur_bound, int cur_weight, int lvl, std::vector<int> cur_path); //основной цикл задачи коммивояжера
    void tsp(); //приготовления к решению задачи коммивояжера
    //misc
    std::vector<int> get_path();
    GetMatrix& operator=(GetMatrix& m);
    void ad_new_node_to_matr(); //добавить узел
    int ad_new_edge_to_matr(int vert1, int vert2, int weight); //добавить ребро
    int del_a_node(int vert); //удалить узел
    int del_an_edge(int vert1, int vert2); //удалить ребро
};

#endif // GETMATRIX_H
