#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTime>
#include <QTimer>
//#include <QSound>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Graph_Show(QCustomPlot *CustomPlot);

    void init_lofar();
    void show_lofar(QVector<double> data);

    void Bars_domain_init();
    void Bars_show(QVector<double> fossilData);

    void T_domain_init();
    void T_Show(QVector<double> data);

    void FFT_DISPLAY_init();
    void FFT_DISPLAY_show(QVector<double> data);

    int fileread();

    //
    void frame_data(char *buf,int buf_len);
    void read_data_file(QString fileName);
    void readSampleTXT(QString sample_file);
    //

    QCustomPlot * fp3;
    QCPColorMap * m_pColorMap;
    QCPBars *fossil;
    QCustomPlot *CustomPlot;

private:
    Ui::MainWindow *ui;

    QTimer *flushTimer;

    QFuture<void> future;

private slots:
    void update();
};

#endif // MAINWINDOW_H
