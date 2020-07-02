#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int **a; // матрица кратчайших расстояний
int *e;  // множество экцентриситетов
int *c;  // центр графа, множество радиусов
string f_name;
string f_center = "center.txt";

void get_matrix(int &n)
{
    ifstream fin(f_name);
    fin >> n;
    a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
            fin >> a[i][j];
    }
    fin.close();
}

// вывод матрицы на экран
void show_matrix(int &n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

// Нахождение кратчайших расстояний
void floyd(int &n)
{
    for (int i = 0; i < n; i++)
        a[i][i] = 0;

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][k] + a[k][j] < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
}

// множество эксцентриситетов
void ex_center(int &n)
{
    int max;
    e = new int[n];
    for (int i = 0; i < n; i++)
    {
        max = a[i][0];
        for (int j = 0; j < n; j++)
            if (a[i][j] > max)
                max = a[i][j];
        e[i] = max;
    }
}

// центр графа
void center(int &n)
{
    ofstream fout(f_center);
    int min;                // радиус
    int k = 0;              // количество радиусов
    int min_end_index = -1; // позиция крайнего радиуса
    min = e[0];

    for (int i = 1; i < n; i++)
        if (e[i] < min)
            min = e[i];

    // получение позиции крайнего радиуса
    for (int i = n - 1; i >= 0 && min_end_index == -1; i--)
        if (e[i] == min)
            min_end_index = i;

    for (int i = 0; i < n; i++)
        if (e[i] == min)
        {
            if (i != min_end_index)
                fout << i << endl;
            else
                fout << i;
            k++;
        }
    fout.close();

    ifstream fin(f_center);
    c = new int[k];
    k = 0;

    while (!fin.eof())
    {
        fin >> c[k];
        k++;
    }
    fin.close();

    cout << "\nGraph center:\n";

    for (int i = 0; i < k; i++)
        cout << c[i] << "\t";
}

int main()
{
    system("cls");
    int n;
    cout << "File name: ";
    cin >> f_name;

    get_matrix(n);
    floyd(n);

    cout << "\nMatrix:\n\n";
    show_matrix(n);

    ex_center(n);
    center(n);
}