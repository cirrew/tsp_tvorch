#include "getmatrix.h"
GetMatrix::GetMatrix()
{
    address="";
    siz=0;
    rasst=1000000;
}
GetMatrix::GetMatrix(QString t)
{
    address = t;
    siz=0;
    rasst=100000;
}

int GetMatrix::checkMatrix()
{
    col.clear();
    QFile file(address);
    if (!file.open(QIODevice::ReadOnly)) //если файл не открыть
    {
        qWarning("fail failed to open");
        return 1;//файл не открылся
    }
    else
    {
        QTextStream in(&file);
        int columnCount = 0;
        int rowCount = 0;
        int total_amount = in.readLine().toInt();
        while (!in.atEnd()) //пока не конец файл
        {
             //читать по строкам
            QString temp = in.readLine();
            temp=temp+"|";
            std::vector<int> rows;
            QString num="";
             //выделение чисел из строки, числа разделены вертикальной чертой
            for (int i=0; i<temp.size(); i++)
            {
                if (temp.at(i)!="|")
                {
                    num+=temp.at(i);
                }
                else
                {
                    rows.push_back(num.toInt());
                    num="";
                }
            }
            col.push_back(rows);
            final_path.push_back(-1);
            rowCount++;
        }
        if (rowCount!=0)
            columnCount=total_amount/rowCount;
        if (rowCount!=columnCount)
        {
            qWarning("not square");
            col.clear();
            return 3;//матрица не симметрична
        }
        siz = rowCount;
    }
    for (int i=0; i<siz-1; i++)
    {
        for (int j=i+1; j<siz; j++)
        {
            if (col[i][j]!=0 && col[j][i]!=0)
            {
                if (col[i][j]!=col[j][i])
                {
                    qWarning("different paths");
                    col.clear();
                    return 4; //расстояния из A в B и из B в A разные
                }
            }
        }
    }
    final_path.push_back(-1);
    return 0;
}

std::vector<std::vector<int>> GetMatrix::getFullMatrix()
{
    return col;
}


int GetMatrix::first_min(std::vector<std::vector<int>> &v, int i)
{
    int mi = 1000000;
    for (int k=0; k<siz; k++)
    {
        if (v[i][k]<mi && i!=k)
            mi=v[i][k];
    }
    return mi;
}
int GetMatrix::second_min(std::vector<std::vector<int>> &v, int i)
{
    int f=100000, s=100000;
    for (int j=0; j<siz; j++)
    {
        if (i!=j)
        {
            if (v[i][j]<=f)
            {
                s=f;
                f=v[i][j];
            }
            else
            {
                if (v[i][j]<=s && v[i][j]!=f)
                    s=v[i][j];
            }
        }
    }
    return s;
}
//аргументы:
//cur_bound - нижняя граница исходного узла
//cur_weight - хранит текущий вес пути
//cur_path - текущий путь
//lvl - уровень итерации
void GetMatrix::tsprec(std::vector<std::vector<int>> &v, int cur_bound, int cur_weight, int lvl, std::vector<int> cur_path)
{
    //если достигнут последний уровень итерации - конец матрицы
    if (lvl==siz)
    {
        //если есть ребро из последнего узла в пути назад к первому узлу
        if (v[cur_path[lvl-1]][cur_path[0]]!=0)
        {
            //вычисляется суммарный вес
            int cur_res=cur_weight+v[cur_path[lvl-1]][cur_path[0]];
            //если результат лучше, то его надо обновить
            if (cur_res<rasst)
            {
                copy_to_final(cur_path);
                rasst=cur_res;
            }
        }
        return;
    }
    //для всех остальных уровней итерации
    for (int i=0; i<siz; i++)
    {
        //если следующий узел не он же сам
        if (v[cur_path[lvl-1]][i]!=0 && visited[i]==false)
        {
            int tmp = cur_bound;
            cur_weight+=v[cur_path[lvl-1]][i];
            //разные вычисления границы для разных уровней итерации
            if (lvl==1)
                cur_bound-=((first_min(v, cur_path[lvl-1])+first_min(v,i))/2);
            else
                cur_bound-=((second_min(v, cur_path[lvl-1])+first_min(v,i))/2);
            //cur_bound+cur_weight - действительная нижняя граница для узла
            //на котором алгоритм сейчас находится
            //если она меньше конечного пути, надо исследовать узел дальше
            if (cur_bound+cur_weight<rasst)
            {
                cur_path[lvl]=i;
                visited[i]=true;//пометка, что узел посещён
                //рекурсивный вызов следующего уровня
                tsprec(v, cur_bound, cur_weight, lvl+1, cur_path);
            }
            //иначе надо отменить изменения к cur_weight и cur_bound
            cur_weight-=v[cur_path[lvl-1]][i];
            cur_bound=tmp;
            //в том числе отменить изменения к вектору посещённых узлов
            for (unsigned int k=0;k<visited.size();k++)
            {
                visited[k]=false;
            }
            for (int j=0;j<=lvl-1;j++)
            {
                visited[cur_path[j]]=true;
            }
        }
    }
}
void GetMatrix::tsp()
{
    //текущий путь
    std::vector<int> cur_path;
    int cur_bound = 0;
    //начальная инициализация используемых векторов
    for (int i=0; i<=siz;i++)
    {
        final_path[i]=-1;
        cur_path.push_back(-1);
    }
    for (int i=0;i<siz;i++)
    {
        visited.push_back(false);
    }
    //вычисление исходной нижней границы для начального узла
    for (int i=0;i<siz;i++)
    {
        cur_bound+=(first_min(col,i)+second_min(col,i));
    }
    //округление до целого числа
    cur_bound=(cur_bound&1)?cur_bound/2+1:cur_bound/2;
    //начало - самый первый узел
    visited[0]=true;
    cur_path[0]=0;
    tsprec(col, cur_bound, 0, 1, cur_path);
}
//копирование пути в final_path
void GetMatrix::copy_to_final(std::vector<int> cur_p)
{
    for (unsigned int i=0; i<cur_p.size(); i++)
    {
        final_path[i]=cur_p[i];
    }
    final_path[siz]=cur_p[0];
}
int GetMatrix::get_rasst()
{
    return rasst;
}
std::vector<int> GetMatrix::get_path()
{
    return final_path;
}

GetMatrix& GetMatrix::operator=(GetMatrix &m)
{
    this->siz=m.siz;
    this->col=m.col;
    this->address=m.address;
    this->final_path=m.final_path;
    this->visited=m.visited;
    this->rasst=m.rasst;
    return *this;
}


void GetMatrix::ad_new_node_to_matr() //добавить новый узел
{
    std::vector<int> temp_v;
    for (int i=0; i<siz; i++)
    {
        col[i].push_back(0);
        temp_v.push_back(0);
    }
    temp_v.push_back(0);
    col.push_back(temp_v);
    siz++;
}

int GetMatrix::ad_new_edge_to_matr(int vert1, int vert2, int weight) //добавить новое ребро
{
    if (vert1==vert2)
    {
        return 2; //если они равны
    }
    if (col[vert1-1][vert2-1]!=0)
    {
        return 3; //если уже есть узел на этом месте
    }
    if (weight==0)
    {
        return 4; //если новое ребро равно нулю
    }
    col[vert1-1][vert2-1]=weight;
    return 1;
}

int GetMatrix::del_a_node(int vert) //удаление узла
{
    int ind = vert-1;
    for (int i=ind; i<siz-1; i++)
    {
        for (int j=0; j<siz; j++)
        {
            col[i][j]=col[i+1][j];
        }
    }
    for (int j=ind; j<siz-1; j++)
    {
        for (int i=0; i<siz-1; i++)
        {
            col[i][j]=col[i][j+1];
        }
    }
    col.pop_back();
    for (int i=0; i<siz-1; i++)
    {
        col[i].pop_back();
    }
    siz-=1;
    return 1;
}

int GetMatrix::del_an_edge(int vert1, int vert2) //удаление ребра
{
    if (col[vert1-1][vert2-1]==0)
    {
        return 2; //нет ребра
    }
    col[vert1-1][vert2-1]=0;
    return 1;
}

void GetMatrix::create_empty(int k)
{
    //создать пустую матрицу смежности размером k
    col.clear();
    siz=k;
    final_path.clear();
    rasst=0;
    std::vector<int> tmp;
    for (int i=0; i<k; i++)
    {
        tmp.clear();
        for (int j=0; j<k; j++)
        {
            tmp.push_back(0);
        }
        col.push_back(tmp);
        final_path.push_back(-1);
    }
    final_path.push_back(-1);
}


