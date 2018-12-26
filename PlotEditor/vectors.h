#ifndef VECTORS_H
#define VECTORS_H
#include <iostream>
#include <vector>
#include <QString>
#include <algorithm>
#include <iterator>
#include <QDebug>
#include <map>
using namespace std;

void WholePart(QString &left, bool &minus, double &coef, bool flag);

class Poly
{
    int degree=-1;
    vector<pair<double, QString>> vec;
public:
    Poly operator+(Poly vect);
    Poly operator* (Poly vect);
    Poly operator*(int coef);
    friend Poly toGeneral(QString &input);
    void print();
    void Init();
    void Rotate90();
    double getPer(int i);
    QString getVariable(int i);
    friend ostream&operator<<(ostream&os, Poly&p);
    void Push(pair<double, QString> p);
    Poly( vector<pair<double, QString>> v, int d): vec(v), degree(d) {}
    Poly(){}

};

Poly func(QString input);
Poly BracketDel(QString input);
Poly toGeneral(QString &input);




#endif // VECTORS_H
