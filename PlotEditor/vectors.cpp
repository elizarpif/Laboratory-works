#include "vectors.h"

void WholePart(QString &left, bool &minus, double &coef, bool flag)
{
    while(left.length() >= 1)
    {
        int indEqv = -1, ind = -1;
        indEqv = left.indexOf("+");
        ind = left.indexOf("-");
        if(indEqv != -1)
        {
            if (minus == true)
            {
                minus = false;
                coef += left.left(indEqv).toDouble(&flag)*(-1);
            }
            else
                coef += left.left(indEqv).toDouble(&flag);

            left = left.right(left.length()-1-indEqv);
        }

        else if(ind != -1)
        {
            if (ind == 0)
            {
                minus = true;
                left = left.right(left.length()-1);

                if (left.length() == 0)
                    break;
                continue;

            }
            if (minus == true)
            {
                minus = false;
                coef += left.left(ind).toDouble(&flag)*(-1);
            }
            else
                coef += left.left(ind).toDouble(&flag);
            left = left.right(left.length()-ind);
        }
        if (ind == indEqv && ind == -1)
            return;
    }
}

void Poly::Init()
{
    QString mas[]={"x", "y", "x^2", "y^2", "xy", "0"};
    map<QString, double> k;
    for(auto it:vec)
    {
        k[it.second] =it.first;
    }
    for(int i = 0; i < 6; i++)
    {
        if (k.find(mas[i]) == k.end())
            vec.push_back(make_pair(0, mas[i]));
    }
    sort(vec.begin(), vec.end(), [](const pair<double, QString>&a,
         const pair<double, QString>&b)
    {
        return a.second>b.second;
    });

}
void Poly::Rotate90()
{
    double tmp = vec[1].first;
    vec[1].first = vec[4].first;
    vec[4].first=tmp;
    vec[2].first = vec[2].first*(-1);
    tmp = vec[0].first;
    vec[0].first = vec[3].first;
    vec[3].first = tmp;
}
double Poly::getPer(int i)
{
    if (vec.size() != 0)
        return vec[i].first;
    else return 0;

}
QString Poly::getVariable(int i)
{
    if (vec.size() != 0)
        return vec[i].second;
    else return 0;
}

void Poly::Push(pair<double, QString> p)
{
    vec.push_back(p);
}


Poly Poly::operator +(Poly vect)
{
    QString s;
    vector<pair<double, QString>> res = vect.vec;
    int degr = vect.degree;

    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        s = (*it).second;
        auto f = find_if(res.begin(), res.end(), [&s](const pair<double, QString> &a){
            return a.second == s;
        });
        if (f != res.end())
        {
            (*f).first += (*it).first;
        }
        else
        {
            if (((*it).second == "x" || (*it).second == "x") && degr < 1)
                degr = 1;
            if (!((*it).second == "x" || (*it).second == "x") && degr < 2)
                degr = 2;

            res.push_back(*it);
        }

    }
    sort(res.begin(), res.end(), [](const pair<double, QString>&a,
         const pair<double, QString>&b)
    {
        return a.second>b.second;
    });
    Poly Result(res, degr);

    return Result;
}

Poly Poly::operator *(Poly v)
{
    if (degree + v.degree >2)
    {
        qDebug()<<"невозможно умножить "<<endl;
        return *this;
    }
    vector<pair<double, QString>> res;
    double coef;
    int degr;
    QString tmp1, tmp2;
    int flag;
    QString mas[]={"x", "y", "x^2", "y^2", "xy", "0"};
    for (auto it :vec)
    {
        for(auto ik: v.vec)
        {
            tmp1 = it.second;
            tmp2 = ik.second;

            if ((tmp1 == "x" && tmp2 == "y") ||(tmp1 == "y" && tmp2 == "x"))
                flag = 4;
            else if (tmp1 == "x" && tmp2 == "x")
                flag = 2;
            else if (tmp1 == "y" && tmp2 == "y")
                flag = 3;
            else if ((tmp1 == "x^2" && tmp2 == "0")||(tmp1 == "0" && tmp2 == "x^2"))
                flag = 2;
            else if ((tmp1 == "y^2" && tmp2 == "0")||(tmp1 == "0" && tmp2 == "y^2"))
                flag = 3;
            else if ((tmp1 == "0" && tmp2 == "x")||(tmp1 == "x" && tmp2 == "0"))
                flag = 0;
            else if ((tmp1 == "0" && tmp2 == "y")||(tmp1 == "y" && tmp2 == "0"))
                flag = 1;
            else if ((tmp1 == "0" && tmp2 == "xy")||(tmp1 == "xy" && tmp2 == "0"))
                flag = 4;
            else if (tmp1 == "0" && tmp2 == "0")
                flag = 5;

            QString c = mas[flag];

            auto f = find_if(res.begin(), res.end(), [c](const pair<double, QString> &a){
                return a.second==c;
            });
            coef=it.first*ik.first;

            if ((flag==0 || flag==1) && degr<1)
            {
                degr=1;
            }
            else if ((flag==2 || flag==3 || flag==4) && degr<2)
                degr=2;

            if (f==res.end())
                res.push_back(make_pair(coef, c));
            else
                (*f).first +=coef;

        }
    }
    sort(res.begin(), res.end(), [](const pair<double, QString>&a,
         const pair<double, QString>&b)
    {
        return a.second>b.second;
    });
    Poly Res(res, degr);
    return Res;
}



Poly Poly::operator *(int coef)
{
    for(auto it = this->vec.begin(); it!=vec.end(); ++it)
    {
        (*it).first = (*it).first*coef;
    }

    return *this;
}


Poly toGeneral(QString &input)
{
    input.replace("*","");
    input.replace(" ","");
    input.replace("++","+");
    input.replace("--","-");
    input.replace("+-","-");
    input.replace("-+","-");
    input.replace("xx","x^2");
    input.replace("yy","y^2");
    input.replace("yx","xy");
    input.replace("=", "");

    QString mas[5] = {"x", "y", "x^2", "y^2", "xy"};

    vector<pair<double, QString>> vec;
    int degr = 0;

    try
    {
        while(true)
        {
            int first = -1, i = 0, how = 0, k = 0;

            double coef = 0;
            QString left;

            if (input[0]=="+")
                input = input.right(input.length()-1);

            for(auto it1:mas)
            {
                k = input.indexOf(it1);
                if (first == -1 && k != -1)
                {
                    first = k;
                    how = i;
                }
                else if (k != -1 && k < first)
                {
                    first = k;
                    how = i;
                }
                else if ((k == first) && (k != -1))
                {
                    if (it1.length() > mas[how].length())
                    {
                        how = i;
                    }
                }
                i++;
                if (first == -1 && i == 5) {
                    bool m=false;
                    QString s=input;
                    WholePart(input,m,coef, true);
                    //input - число
                    if (m == true)
                        coef += input.toDouble()*(-1);
                    else
                        coef += input.toDouble();
                    QString c = "0";
                    auto f = find_if(vec.begin(), vec.end(), [c](const pair<double, QString> &a){
                        return a.second == c;

                    });
                    if (f == vec.end())
                        vec.push_back(make_pair(coef, c));
                    else
                        (*f).first += coef;
                    Poly p(vec, degr);
                    return p;
                }
            }
            if ((how == 0 || how == 1) && degr < 1)
            {
                degr=1;
            }
            if (!(how == 0 || how == 1) && degr < 2)
                degr = 2;

            int n = mas[how].length();
            if (first != 0)
            {
                left = input.left(first);
                QString l = mas[how];
                bool flag;
                coef = left.toDouble(&flag);
                bool minus = false;

                n += left.length();

                if (flag == false)
                {

                    WholePart(left,minus,coef, flag);
                    QString c = "0";
                    auto f = find_if(vec.begin(), vec.end(), [c](const pair<double, QString> &a){
                        return a.second == c;
                    });
                    if (f == vec.end())
                        vec.push_back(make_pair(coef, c));
                    else
                        (*f).first +=coef;
                    if (left == "")//-+
                    {
                        if (minus == true)
                            coef = -1;
                        else
                            coef = 1;
                    }
                    else
                    {
                        coef = left.toDouble(&flag);
                        if (flag == false)
                            coef = 1;
                        if (minus == true)
                            coef *= -1;
                    }
                }

                auto f = find_if(vec.begin(), vec.end(), [&l](const pair<double, QString> &a){
                    return a.second==l;
                });
                if (f!=vec.end())
                        (*f).first +=coef;
                else
                    vec.push_back(make_pair(coef, mas[how]));
            }
            else
               vec.push_back(make_pair(1, mas[how]));
            input.remove(0, n);
        }

    }
    catch(const std::exception&)
    {
        Poly p;
        return p;
    }

}


Poly BracketDel(QString input)
{
    input = "(" + input + ")";
    vector<QString> opers;
    vector<QString> equiv;

    //Poly Res;
    int op = input.count(")");
    int cl = input.count("(");

    int flag = -1, tmp1, tmp2, len, newbrac;
    QString bracket, tempstr, c, f, osn="";
    vector<Poly> res;
    Poly result;
    if (cl != op)
    {
        qDebug()<<"brackets";
        return result;
    }


    for(int i = 0; i!=input.length(); i++)
    {
        len = equiv.size() - 1;
        if (input[i] == "+" || input[i] == "-")
        {
            flag = i;

            c = input[i];
            equiv[len] += c;
            continue;
        }
        else if (input[i] == "(")
        {
            if (c == "*")
                bracket = c;
            else if (flag >= 0)
            {

                if (i-flag == 1)
                {
                    bracket = c;
                    reverse(equiv[len].begin(), equiv[len].end());
                    int k = equiv[len].indexOf(c);
                    reverse(equiv[len].begin(), equiv[len].end());
                    equiv[len] = equiv[len].left(equiv[len].length()-k-1);
                }
                else
                {
                    if (c == "-")
                        bracket = c;
                    bracket += input.mid(flag+1, i-flag-1);
                    reverse(equiv[len].begin(), equiv[len].end());

                    int k = equiv[len].indexOf(c);
                    reverse(equiv[len].begin(), equiv[len].end());

                    equiv[len] = equiv[len].left(equiv[len].length()-k-1);
                }
                if (bracket == "+")
                    bracket = "+1";
                if (bracket == "-")
                    bracket = "-1";
                flag = -1;
            }
            else
                bracket = "+1";

            opers.push_back(bracket);
            equiv.push_back("");
            tempstr = "";
            bracket = "";

            c = "";
        }
        else if (input[i]==")")
        {

            tmp1 = opers.size()-1;
            tempstr = opers[tmp1];

            if (tempstr=="*")
            {
                Poly t = toGeneral(equiv[len]);
                res[res.size()-1] = res[res.size()-1]*t;
            }
            else
            {
                Poly k = toGeneral(tempstr);
                Poly t = toGeneral(equiv[len]);
                res.push_back(k*t);
            }

            opers.resize(tmp1);
            equiv.resize(len);
            flag = -1;

            if (i+1 != input.length() && input[i+1] == "(")
                c = "*";
            else
                c = "";
        }
        else
        {
            equiv[len] += input[i];
        }

    }
    if (opers.size() > 0 || equiv.size() > 0)
        qDebug()<<"Что-то не так со скобками!!!";

    for (auto it = res.begin(); it != res.end(); ++it)
    {
        result = result + (*it);
    }
    return result;
}




Poly func(QString input)
{

    int indEqv = input.indexOf("=");

    if (indEqv!=-1)
    {
        QString right = input.right(input.length()-indEqv-1);
        QString left = input.left(indEqv);

        right = "-("+right+")";
        input=left+right;
        input.replace("*","");
        input.replace(" ","");
        input.replace("++","+");
        input.replace("--","-");
        input.replace("+-","-");
        input.replace("-+","-");
        input.replace("xx","x^2");
        input.replace("yy","y^2");
        input.replace("yx","xy");

        Poly res = BracketDel(input);

        return res;

    }
    else
    {
        Poly vec = toGeneral(input);
        return vec;
    }

}
