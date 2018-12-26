#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    //ui->plot->setInteraction(QCPAxisRect::setRangeDragAxes);
    //ui->plot->

    max = 10;
    min = -10;

    ui->rotate90->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->treeCurves->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeCurves,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord()));

    // Подключаем СЛОТ вызова контекстного меню
    connect(ui->treeCurves, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    connect(ui->spravka, SIGNAL(triggered()), this, SLOT(showHelp()));

    FileOpen();
    Plot();
   // ui->plot->setl
}

Poly polinom;

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * addCurve = new QAction(trUtf8("Добавить"), this);
    QAction * deleteCurve = new QAction(trUtf8("Удалить"), this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(addCurve, SIGNAL(triggered()), this, SLOT(slotAddRecord()));     // Обработчик вызова диалога редактирования
    connect(deleteCurve, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи
    /* Устанавливаем действия в меню */
    menu->addAction(addCurve);
    menu->addAction(deleteCurve);
    /* Вызываем контекстное меню */
    menu->popup(ui->treeCurves->viewport()->mapToGlobal(pos));
}

void MainWindow::on_treeCurves_itemClicked(QTreeWidgetItem *item, int column)
{
    int k =ui->treeCurves->indexOfTopLevelItem(ui->treeCurves->currentItem());


    //int k= eq_name.indexOf(str,0);
    qDebug()<<k<<" "<<equals[k];


    ui->equiv_edit->setText(equals[k]);

    polinom = getInput(equals[k]);
    Plot();
}


void MainWindow::showHelp()
{
    f2 = new QDialog(this );
    QFont f;
    f.setItalic(true);
    f.setWeight(12);
    f.setFamily("Comic Sans MS");
    QLabel *l = new QLabel(f2);
    l->setText("Редактор графиков");
    l->setFont(f);
   // f.setStyle("");
    l->move(200,0);
    QTextEdit *l2 = new QTextEdit(f2);
    l2->setReadOnly(true);
    l2->setFont(f);
    l2->setText("Правила ввода: выражение не является калькулятором обычных чиселок, поэтому выражения типа 9*8*7x^2 не возьмет и склеит в 987x^2. "
                "Если прям так хочется посчитать, то вводить рекомендуется со скобками (9)*(8)*(7x^2). "
                "Выражения выше второй степени не принимает и при вводе например x^2*y^2 посчитает как x^2+y^2. "
                "Выражение типа (x^2*y) считается недопустимым и считает аналогично как x^2+y. "
                "В случае некорректного ввода скорее всего ничего не нарисуется, так как передастся нулевое уравнение. "
                "Примечание: выражения типа (5+7)x расцениваются как ошибки, во избежание этой ошибки ограничивайте скобками (5+7)(x)");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(l);
    layout->addWidget(l2);
    f2->setLayout(layout);
    f2->setWindowTitle(QObject::tr("Справка"));
    f2->setMinimumSize(550,100);
    f2->setMaximumSize(550,300);
    f2->show();
}

void MainWindow::slotRemoveRecord()
{

    int index = ui->treeCurves->indexOfTopLevelItem(ui->treeCurves->currentItem());

    if (index!=0)
    {
        delete ui->treeCurves->takeTopLevelItem(index);
         qDebug()<<"До удаления "<<equals<<eq_name;
        equals.remove(index);
        eq_name.remove(index);
    }
    else
    {
        delete ui->treeCurves->takeTopLevelItem(index);
        equals.remove(index);
        eq_name.remove(index);
    }
    qDebug()<<"index="<<index;
    qDebug()<<"После удаления "<<equals;

}

void MainWindow::slotAddRecord()
{
    QTreeWidgetItem *item = new QTreeWidgetItem;



    QString str = QInputDialog::getText(0, "Input", "Введите название текущему уравнению", QLineEdit::Normal);
    item->setText(0, str);

    int count = ui->treeCurves->topLevelItemCount();
    ui->treeCurves->insertTopLevelItem(count,item);
    QString eq = ui->equiv_edit->text();

    qDebug()<<count;

    equals.append(eq);
    eq_name.append(str);
    qDebug()<<"Новая запись "<<equals;

}


void MainWindow::FileOpen()
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        //ui->line->clear();
        QTextStream stream(&file);
        stream.setAutoDetectUnicode(false);
        QString str;
        int i=1;
        while (!stream.atEnd())
        {
            str = stream.readLine();

            if (i%2==1)
               equals.append(str);
            else
               {
                eq_name.append(str);
                QTreeWidgetItem *item = new QTreeWidgetItem;
                item->setText(0, str);

                int count = ui->treeCurves->topLevelItemCount();
                ui->treeCurves->insertTopLevelItem(count,item);
                ui->equiv_edit->setText(equals[count]);
            }

            i++;
        }
        if(stream.status()!= QTextStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }
    else
        ui->textEdit->append("Error opening of file "+QString(file.fileName()));
}

MainWindow::~MainWindow()
{
    QFile file(filename);
    try{
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.setAutoDetectUnicode(false);
            QString str;
            for (int i=0; i<equals.length(); i++)
            {
                stream<<equals[i]<<"\n";
                stream<<eq_name[i]<<"\n";
                qDebug()<<equals[i];
            }
            file.close();
        }

    }
    catch(const std::exception&)
    {
        qDebug()<<"ошибка при закрытии";
    }

    delete ui;
}

void MainWindow::GraphInit(int i)
{
    ui->plot->graph(i)->setPen(QColor(92, 0, 228, 255));//задаем цвет точки

    ui->plot->graph(i)->setLineStyle(QCPGraph::lsNone);

    ui->plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
}

Poly MainWindow::getInput()
{
    QString input = ui->equiv_edit->text();
    Poly p = func(input);
    p.Init();
    return p;
}

Poly MainWindow::getInput(QString s)
{
    Poly p = func(s);
    p.Init();
    return p;
}

void MainWindow::Plot()
{

    double h = 0.0005; //Шаг, с которым будем пробегать по оси Ox

    //int N=(max+abs(min))/h + 2; //Вычисляем количество точек, которые будем отрисовывать
    double b = polinom.getPer(0);
    double e = polinom.getPer(1)/2;
    double c = polinom.getPer(2)/2;
    double a = polinom.getPer(3);
    double d = polinom.getPer(4)/2;
    double f = polinom.getPer(5);
    QString l;
    ui->text_invar->clear();
    ui->text_invar->append(l.number(a)+"x^2 + "+l.number(c)+"xy + "+l.number(b)+"y^2 + "+l.number(d)+"x +" + l.number(e)+"y + " + l.number(f));



//    a=StrToFloat(Edit1->Text); // a11

//    b=StrToFloat(Edit2->Text);	// a22

//    c=StrToFloat(Edit3->Text);	// a12

//    d=StrToFloat(Edit4->Text);	// a13

//    e=StrToFloat(Edit5->Text);	// a23

//    f=StrToFloat(Edit6->Text);	// a33

    ui->textEdit->clear();


    for( int i=0; i<6; i++)
    {
        ui->textEdit->append(l.number(polinom.getPer(i))+" " +polinom.getVariable(i));
    }

    double Delta = a*b*f+2*c*e*d - d*d*b - a*e*e - f*c*c;
    double D1 = a*b-c*c;
    double I = a+b;
    double K =a*f-d*d + b*f-e*e;



    ui->text_invar->append("инвариант 1 (определитель 3*3) Delta = "+l.number(Delta));

    ui->text_invar->append("инвариант 2 (определитель 2*2) D ="+l.number(D1));
    ui->text_invar->append("инвариант 3 (сумма коэффициентов при квадратах) I ="+l.number(I));

    ui->text_invar->append("инвариант 4 (сумма определителей) K = "+l.number(K));

    //корни хар уравнения
    //l^2-I*l+D1=0
    double lambda_1 = (I+sqrt(I*I-4*Delta))/2;
    double lambda_2 = (I-sqrt(I*I-4*Delta))/2;
    if (abs(lambda_1)>abs(lambda_2))
    {
        double tmp = lambda_1;
        lambda_1 = lambda_2;
        lambda_2 = tmp;
    }


    if (D1>0)
    {
        if (I*Delta<0)
        {
            ui->text_invar->append("Эллиптический тип, эллипс");
           // ui->text_invar->append("канонический вид уравнения (x^2)/("+l.number(-Delta/(lambda_1*D1))+
                                  // ") + (y^2)/("+l.number(-Delta/(lambda_2*D1))+") = 1");
        }
        else if (I*Delta>0)
        {
            ui->text_invar->append("Эллиптический тип, мнимый эллипс");
          //  ui->text_invar->append("канонический вид уравнения (x^2)/("+l.number(Delta/(lambda_1*D1))+
                                  // ") + (y^2)/("+l.number(Delta/(lambda_2*D1))+") = -1");
        }
        else if (Delta==0) //I*Delta=0
        {
            ui->text_invar->append("Эллиптический тип, пара мнимых пересекающихся прямых");
            //ui->text_invar->append("канонический вид уравнения (x^2)/("+l.number(1/abs(lambda_1))+
                                  // ") + (y^2)/("+l.number(1/abs(lambda_2))+") = 0");
        }
    }

    else if (D1<0)
    {

        if (Delta != 0)
        {
            ui->text_invar->append("Гиперболический тип, гипербола");
            //ui->text_invar->append("канонический вид уравнения (x^2)/("+l.number(-Delta/(lambda_1*D1))+
                                  // ") - (y^2)/("+l.number(-Delta/(lambda_2*D1))+") = 1");
        }
        else
        {
            ui->text_invar->append("Гиперболический тип, пара пересекающихся прямых");
            //ui->text_invar->append("канонический вид уравнения (x^2)/("+l.number(1/(lambda_1))+
                                  // ") - (y^2)/("+l.number(-1/lambda_2)+") = 0");
        }
    }

    else if (D1==0)
    {
        if (Delta!=0)
        {
            ui->text_invar->append("Параболический тип, парабола");
            //ui->uravnenie->setText();
            //ui->text_invar->append("канонический вид уравнения y^2 = "+l.number(2*sqrt(-Delta/(I*I*I)))+"x");
        }
        else if (Delta==0)
        {
            if (K<0)
            {
                ui->text_invar->append("Параболический тип, пара параллельных прямых");
                //ui->text_invar->append("канонический вид уравнения y^2 - "+l.number(- K/(I*I))+" = 0");
            }
            else if (K>0)
            {
                ui->text_invar->append("Параболический тип, пара мнимых параллельных прямых");
                //ui->text_invar->append("канонический вид уравнения y^2 + "+l.number(K/(I*I))+" = 0");
            }
            else
            {
                ui->text_invar->append("Параболический тип, пара совпадающих прямых");
                //ui->text_invar->append("канонический вид уравнения y^2 = 0 ");
            }
        }
    }



    polinom.print();

    ui->plot->xAxis->setRange(min, max);
    ui->plot->yAxis->setRange(min, max);

    ui->plot->addGraph();

    GraphInit(0);
    ui->plot->addGraph();

    GraphInit(1);


    double D;
    QVector<pair<double, double>> XY;
    QVector<double> YY, XX;



    double x = min;

    while(x <= max)//Пробегаем по всем точкам
    {
        if (b==0)
        {
            XY.append(make_pair(x,(-(a*x*x+2*d*x+f) / 2*(c*x+e))));
        }

        else
        {

        // a*x*x+b*y*y+2*c*x*y+2*d*x+2*e*y+f=0;

            D=(c*x+e)*(c*x+e)-b*(a*x*x+2*d*x+f);

            if (D==0)
            {
                XY.append(make_pair(x,-(c*x+e)/b));
            }

            if (D>0)
            {
                XY.append(make_pair(x,(-(c*x+e)+sqrt(D))/b));

                XY.append(make_pair(x,(-(c*x+e)-sqrt(D))/b));
            }


     }

        //qDebug()<<x;
        if(h-h/2 == 0) h == 0.01;
        x+=h;
    }


    for (int i = 0; i < XY.size(); i++)
    {
        XX.append(XY[i].first);
        YY.append(XY[i].second);
    }


    ui->plot->graph(0)->setData(XX, YY);
    ui->plot->replot();
}


void MainWindow::on_equiv_edit_textEdited(const QString &arg1)
{
    qDebug()<<arg1;
}



void MainWindow::on_pushButton_clicked()
{
    polinom = getInput();
    Plot();

}

void MainWindow::on_spin_min_valueChanged(int arg1)
{
    min = arg1;
    Plot();
}

void MainWindow::on_spin_max_valueChanged(int arg1)
{
    max = arg1;
    Plot();
}



void MainWindow::on_treeCurves_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
//    QString str =item->text(column);

//    int k= eq_name.indexOf(str,0);

//    ui->equiv_edit->setText(equals[k]);

//    Plot();

}

void MainWindow::on_pushButton_2_clicked()
{
    //QCPRange mX = ui->plot->xAxis->
    Plot();
}

void MainWindow::on_rotate90_clicked()
{
    if (!(polinom.getPer(2)==0 && polinom.getPer(1)==0 && polinom.getPer(4)==0))
    polinom.Rotate90();
    qDebug()<<ui->plot->xAxis->axisRect();
    qDebug()<<ui->plot->yAxis->axisRect();
    Plot();
}
