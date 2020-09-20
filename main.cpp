#include <iostream>
#include <fstream>
#include <algorithm>

#define way '*'
#define emp '.'
#define wall '#'
#define start 's'
#define finish 'f'

using namespace std;

ifstream fin("task3.txt");

struct tree {
    int bomb = 0;
    int step = 0;
    int x = 0, y = 0;
    tree* child1 = nullptr, *child2 = nullptr, *child3 = nullptr, *child4 = nullptr;
    tree* parent = nullptr;
};

tree* stop = new tree;

int  xf, yf,xs, ys, mx, my, bomb;

tree* backToTheRoots(int **a, int x, int y, int bomb, tree *tr) {
    tree* child = new tree;
    child->x = x;
    child->y = y;
    child->step = tr->step + 1;
    child->bomb = bomb;
    child->parent = tr;
    return child;
}

bool isParent(tree* tr, int x, int y){
    if (tr->x == x && tr->y == y) return false;
    if (!tr->parent ) return true;
    return isParent(tr->parent, x, y);
}

void search(int** a, tree* tr){
    if (tr->x - 1 >= 0 && a[tr->x - 1][tr->y] == 0 && isParent(tr, tr->x-1, tr->y))
        tr->child1 = backToTheRoots(a, tr->x - 1, tr->y, tr->bomb, tr);
    if (tr->x + 1 < mx && a[tr->x + 1][tr->y] == 0 && isParent(tr, tr->x + 1, tr->y))
        tr->child2 = backToTheRoots(a, tr->x + 1, tr->y, tr->bomb, tr);
    if (tr->y - 1 >= 0 && a[tr->x][tr->y - 1] == 0 && isParent(tr, tr->x, tr->y - 1))
        tr->child3 = backToTheRoots(a, tr->x, tr->y - 1, tr->bomb, tr);
    if (tr->y + 1 < my && a[tr->x][tr->y + 1] == 0 && isParent(tr, tr->x, tr->y + 1))
        tr->child4 = backToTheRoots(a, tr->x, tr->y + 1, tr->bomb, tr);
    if (tr->x - 1 >= 0 && a[tr->x - 1][tr->y] == 1 && tr->bomb > 0 && isParent(tr, tr->x - 1, tr->y))
        tr->child1 = backToTheRoots(a, tr->x - 1, tr->y, tr->bomb - 1, tr);
    if (tr->x + 1 < mx && a[tr->x + 1][tr->y] == 1 && tr->bomb > 0 && isParent(tr, tr->x + 1, tr->y))
        tr->child2 = backToTheRoots(a, tr->x + 1, tr->y, tr->bomb - 1, tr);
    if (tr->y - 1 >= 0 && a[tr->x][tr->y - 1] == 1 && tr->bomb > 0 && isParent(tr, tr->x, tr->y - 1))
        tr->child3 = backToTheRoots(a, tr->x, tr->y - 1, tr->bomb - 1, tr);
    if (tr->y + 1 < my && a[tr->x][tr->y + 1] == 1 && tr->bomb > 0 && isParent(tr, tr->x , tr->y + 1))
        tr->child4 = backToTheRoots(a, tr->x, tr->y + 1, tr->bomb - 1, tr);

    if (tr->child1 != nullptr)
        search(a, tr->child1);
    if (tr->child2 != nullptr)
        search(a, tr->child2);
    if (tr->child3 != nullptr)
        search(a, tr->child3);
    if (tr->child4 != nullptr)
        search(a, tr->child4);
}

void upToParents(tree* tr){
    if (tr->x == xf && tr->y == yf && tr->step < stop->step){
        stop->parent = tr->parent;
        stop->step = tr->step;
        stop->x = tr->x;
        stop->y = tr->y;
        stop->bomb = tr->bomb;
    }
}

void searchParents(tree *tr){
    if (tr->child1 != nullptr){
        upToParents(tr->child1);
        searchParents(tr->child1);
    }
    if (tr->child2 != nullptr){
        upToParents(tr->child2);
        searchParents(tr->child2);
    }
    if (tr->child3 != nullptr){
        upToParents(tr->child3);
        searchParents(tr->child3);
    }
    if (tr->child4 != nullptr){
        upToParents(tr->child4);
        searchParents(tr->child4);
    }
}

void printMaze(int** a, tree *tr){
    stop->step = INT_MAX;
    searchParents(tr);
    if (stop->parent == nullptr){
        cout << "ERROR\nAh shit, here we go again!\nNo way!!! Dude... No way!!!";
        return;
    }
    cout << "Easy-peasy, lemon squeezy!\nShortest way takes:  " << stop->step << " steps and " <<bomb - stop->bomb << " bombs\n";
    while (!(stop->x == xs && stop->y == ys)){
        a[stop->x][stop->y] = -2;
        stop = stop->parent;
    }
    a[xs][ys] = -2;
    for (int i = 0; i < mx; i++){
        for (int j = 0; j < my; j++){
            if (a[i][j] == 0)
                cout << emp;
            if (a[i][j] == 1)
                cout << wall;
            if (a[i][j] == -2)
                cout << way;
        }
        cout << '\n';
    }
}

int stupid_warning(){
    cout << "ERROR\nAh shit, here we go again!\nAre U dumb, stupid or dumb, huh! ©6IX9INE";
    return 2;
}

int main(){
    int rows, cols;
    char c;
    tree maze;
    fin >> rows >> cols >> maze.bomb;
    mx = rows;
    my = cols;
    bomb = maze.bomb;
    if (maze.bomb > rows * cols)
        maze.bomb = rows * cols;
    int** ptrarr = new int* [rows];
    for (int i = 0; i < rows; i++)
        ptrarr[i] = new int[cols];
    xf = rows-1;
    yf = cols-1;
    int st = 0;
    int fn = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            fin >> c;
            if (c == emp)
                ptrarr[i][j] = 0;
            else if (c == wall)
                ptrarr[i][j] = 1;
            else if (c != wall || c!= emp || c != start || c != finish)
                stupid_warning();
            else if (c == start){
                maze.x = i;
                maze.y = j;
                maze.step = 1;
                xs = i;
                ys = j;
                st++;
            }
            else if (c == finish){
                xf = i;
                yf = j;
                ptrarr[i][j] = 0;
                fn++;
            }
        }
    if (st == 0){
        maze.x = 0;
        maze.y = 0;
        maze.step = 1;
        xs = 0;
        ys = 0;
    } else if (st > 1)
        stupid_warning();
    if (fn == 0){
        xf = --rows;
        yf = --cols;
        ptrarr[--rows][--cols] = 0;
    } else if (fn > 1)
        stupid_warning();
    search(ptrarr, &maze);
    printMaze(ptrarr, &maze);
    fin.close();
    for (int i = 0; i < rows; i++)
        delete[] ptrarr[i];
    delete[] ptrarr;
    return 0;
}