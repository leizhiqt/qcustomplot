#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FFTUtil.h"
#include <QtConcurrent>

#define xlength  3800
//#define xlength  190000
#define ylength  225
//#define GB (1024*1024*1024)
//#define readBuffer 1472
//#define BEISHU 1

//#define uchar8_t unsigned char

//union _UStuff_t
//{
//  float  va_float;
//  int  va_int;
//  uchar8_t  ascii[4];
//};

QList<QVector<double> > value_lofar;

QVector<double> cy_data;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CustomPlot = ui->widget_2;

    init_lofar();
    Bars_domain_init();
    T_domain_init();
//    fileread();

    FFT_DISPLAY_init();

    /*
    flushTimer = new QTimer(this);
//    //将定时器的计时信号与updateGL()绑定
    connect(flushTimer, SIGNAL(timeout()), this, SLOT(update()));
    flushTimer->start(50);
    */

    //读取文件
    future = QtConcurrent::run([=]() {
        //在单独进程里执行
        readSampleTXT("D:/log/sample_data_hz1.txt");
        while(1){
            show_lofar(cy_data);
//            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    });
//    future = QtConcurrent::run(this,&MainWindow::read_data_file,"c:/20220802092101.dat");
}

int MainWindow::fileread()
{


    char mp3file[256] = {0};
    qint64 sum = 0;

    QFile file("myplot/myplot/music.wma");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered))
    {
        qDebug() << "Open file failed.";
        return -1;
    } else {

        QFile file2("myplot/myplot/music111.wma");
        if (!file2.open(QIODevice::WriteOnly))
        {
            qDebug() << "Open file failed.";
            return -1;
        } else {
            while (!file.atEnd())
            {
                sum++;
                file.read(mp3file, 256);
                file2.write(mp3file, 256);
                qDebug() << mp3file;
            }
        }
        qDebug() << sum;
        file.close();
        file2.close();
    }
    return 0;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::frame_data(char *buf,int buf_len)
{
    /*
    static long yb_count=0;

//    yb_count +=
    //一帧数据的样本数
    int pack_size = 480;
    //16进制 两字节 默认是5
    //总计帧数
    const int frame_count = buf_len/readBuffer;

//    printf("[%ld %s %d] data_count=%d frame_count=%d yb_count=%ld\n",GetCurrentThreadId(),
//           __FILE__,__LINE__,buf_len,frame_count,yb_count);

//    uchar8_t buf[data_count+1];
//    memcpy(buf,binData.begin(),data_count);

    uchar8_t f_fixed[16]={0x24,0x55,0xAA,0x55,0x7F,0xFF,0xFF,0x10,0x00,0x00,0x7F,0xFF,0xFF,0x10,0x00,0x00};

    int fix_len = 0;//24 修正不去掉文件头

    int buf_fixed_len = 16;
    int buf_pack_len = 1472;//1472
    int buf_pack_head_len = 32;

    uchar8_t buf_pack[buf_pack_len+1];
    uchar8_t buf_fixed[buf_fixed_len+1];

    _UStuff_t UStuff_t;

    for(int i=0;i<frame_count;i++)
    {
        memset(buf_pack,'\0',sizeof(buf_pack));
        memset(buf_fixed,'\0',sizeof(buf_fixed));

        memcpy(buf_pack,buf+(i*buf_pack_len),buf_pack_len);
        memcpy(buf_fixed,buf_pack+fix_len,buf_fixed_len);

//        for(int i=0;i<buf_pack_len;i++){
//            printf(" %02x ",*(buf_pack+i));
//        }
//        printf("\n");

        //验证包头 fixed
        if(strcmp((char *)buf_fixed,(char *)f_fixed))
        {
            printf("[%ld %s %d] fixed\n",GetCurrentThreadId(),__FILE__,__LINE__);
            continue;
        }

        //验证包头 fixed 16->17
        if(!(buf_pack[fix_len+15]==0x00 && buf_pack[fix_len+16]==0xAA))
        {
            printf("[%ld %s %d] fixed 16->17 0x%02x 0x%02x \n",GetCurrentThreadId(),__FILE__,__LINE__,*(buf_pack+fix_len+15),*(buf_pack+fix_len+16));
            continue;
        }

        //数据填充 480
        for(int k=0;k<pack_size+1;k++)
        {
            UStuff_t.ascii[3]=0x00;
            UStuff_t.ascii[2]=*(buf_pack+(fix_len+buf_pack_head_len+k*3));//高位
            UStuff_t.ascii[1]=*(buf_pack+(fix_len+buf_pack_head_len+k*3)+1);
            UStuff_t.ascii[0]=*(buf_pack+(fix_len+buf_pack_head_len+k*3)+2);

            int iValue = UStuff_t.va_int;
            if(iValue>8388608)iValue=iValue-16777216;

            yb_count++;
            //            printf("[%d %s %d] %02x %02x %02x\n",GetCurrentThreadId(),__FILE__,__LINE__,UStuff_t.ascii[2],UStuff_t.ascii[1],UStuff_t.ascii[0]);
            printf("[%ld %s %d] %d \n",GetCurrentThreadId(),__FILE__,__LINE__,iValue);

            cy_data.append(iValue);

            if(yb_count%1024==0){
                T_Show(cy_data);
                cy_data.clear();
//                printf("[%ld %s %d] data_count=%d \n",GetCurrentThreadId(),__FILE__,__LINE__,buf_len);
            }

        }//end frame pack
    }

    free(buf);
    */
}
//"c:/20220802092101.dat"
void MainWindow::read_data_file(QString fileName){
   /*
    QFile *displayFile=new QFile();
    displayFile->setFileName(fileName);

    //读到文件末，关闭文件
    if(!displayFile->isOpen())
        displayFile->open(QIODevice::ReadOnly);

    int fileSize=displayFile->size();

    QDataStream read(displayFile);

    const int rbuf_len = readBuffer*BEISHU;
    char *rbuf = NULL;
//    char rbuf[rbuf_len+1];

    const int file_head_len = 24;

    int count_k = fileSize/rbuf_len;//求总读取
    int last_size = fileSize%rbuf_len;//求最后接收数据长度

    printf("[%ld %s %d] count_k=%d \n",GetCurrentThreadId(),__FILE__,__LINE__,count_k);

    read.skipRawData(file_head_len);
    for(int i=0;i<count_k;i++){
            rbuf =(char *) malloc((sizeof(char)*rbuf_len)+1);
            read.readRawData(rbuf,rbuf_len);

//            for(int i=0;i<rbuf_len;i++){
//                printf(" %02x ",(uchar8_t)*(rbuf+i));
//            }
//            printf("\n");

            frame_data(rbuf,rbuf_len);
            QThread::msleep(100);
    }

    if(last_size>35){
        rbuf =(char *) malloc((sizeof(char)*last_size)+1);
        read.readRawData(rbuf,last_size);
        frame_data(rbuf,last_size);
    }

    //读到文件末，关闭文件
    if(displayFile->isOpen())
        displayFile->close();
*/
}

void MainWindow::readSampleTXT(QString sample_file){

    //读到文件末，关闭文件
    QFile dataFile;
    dataFile.setFileName(sample_file);

    if(!dataFile.isOpen())
        dataFile.open(QIODevice::ReadOnly);

    QTextStream textStream(&dataFile);

    QString lineVal;
    while(!textStream.atEnd())
    {
        lineVal=textStream.readLine();
        cy_data.append(lineVal.toDouble());
    }

    //读到文件末，关闭文件
    if(dataFile.isOpen())
        dataFile.close();
}

void MainWindow::update()
{
    QVector<double> data;
//    static double f = QRandomGenerator::global()->bounded(20)-10;

//    f = f +2;
    int p_dx = 50;
    double dx = M_PI/p_dx;
    double sx=0;
    double A=0;
    double w=0;
    for(int i=0;i<xlength;i++)
    {
        sx = dx*i;
        A = QRandomGenerator::global()->bounded(20)-10;
        w = QRandomGenerator::global()->bounded(20*M_PI);
        data << A*qSin(w*sx);
//        data << A*qSin(sx);
    }

//    for(int i=0;i<xlength;i++)
//    {
//        data << 50+50*sin(2*3.14159*f*i/128);
//    }

//        QVector<double> data;
//        for(int i=0;i<xlength;i++)
//        {
//            double rdVal= QRandomGenerator::global()->bounded(20)-10;
////            printf("rdVal=%lf\n",rdVal);
//            data << rdVal;
//        }
/*
    fft.fft_data.clear();
    fft.fft_calculate(data);

//    F_show(fft.fft_data);

//    F_show(fft.fft_data);

    Bars_show(fft.fft_data);

//    Bars_show(fft.fft_data);

    T_Show(data);

    Complex *outVec = new Complex[data.length()];

    FFTTrans *fftTrans = new FFTTrans();
    fftTrans->fft2(data,data.length(),outVec);

    QVector<double> fft_data;
    for(int i=0;i<xlength;i++)
    {
        fft_data << outVec[i].rl;
    }
    delete[] outVec;

    F_show(fft_data);

    FFT_DISPLAY_show(fft_data);
    */
}

/*
void MainWindow::update()
{
    QVector<double> data;
//    static double f = QRandomGenerator::global()->bounded(20)-10;

//    f = f +2;
    int p_dx = 50;
    double dx = M_PI/p_dx;
    double sx=0;
    double A=0;
    double w=0;
    for(int i=0;i<xlength;i++)
    {
        sx = dx*i;
        A = QRandomGenerator::global()->bounded(20)-10;
        w = QRandomGenerator::global()->bounded(20*M_PI);
        data << A*qSin(w*sx);
//        data << A*qSin(sx);
    }

//    for(int i=0;i<xlength;i++)
//    {
//        data << 50+50*sin(2*3.14159*f*i/128);
//    }

//        QVector<double> data;
//        for(int i=0;i<xlength;i++)
//        {
//            double rdVal= QRandomGenerator::global()->bounded(20)-10;
////            printf("rdVal=%lf\n",rdVal);
//            data << rdVal;
//        }

    fft.fft_data.clear();
    fft.fft_calculate(data);

//    F_show(fft.fft_data);

//    F_show(fft.fft_data);

    Bars_show(fft.fft_data);

//    Bars_show(fft.fft_data);

    T_Show(data);

    Complex *outVec = new Complex[data.length()];

    FFTTrans *fftTrans = new FFTTrans();
    fftTrans->fft2(data,data.length(),outVec);

    QVector<double> fft_data;
    for(int i=0;i<xlength;i++)
    {
        fft_data << outVec[i].rl;
    }
    delete[] outVec;

    F_show(fft_data);

    FFT_DISPLAY_show(fft_data);
}
*/

void MainWindow::init_lofar()
{
    //创建一个画图指针
    fp3 = ui->widget;
    //可拖拽+可滚轮缩放
    fp3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    m_pColorMap = new QCPColorMap(fp3->xAxis,fp3->yAxis);

    //设置整个图（x,y）点数
    m_pColorMap->data()->setSize(xlength+1,ylength+1);
    //setRange是设置X轴以及Y轴的范围
    m_pColorMap->data()->setRange(QCPRange(0,xlength),QCPRange(0,160));

    //设置默认渐进色变化（可在QCPColorGradient中查看）
    m_pColorMap->setGradient(QCPColorGradient::gpGrayscale);
    m_pColorMap->rescaleDataRange(true);
    // 立即刷新图像
    //自适应大小
    fp3->rescaleAxes();
    //ui->widget->replot();
}
void MainWindow::show_lofar(QVector<double> data)   //显示lofar瀑布图
{
    if(value_lofar.size()>ylength)
    {
        value_lofar.removeLast();  //当lofar累积到了50个，删除最后面的数据，防止绘图溢出绘图区域
    }

    value_lofar.prepend(data);//新来的数据一直往前面累加
    for (int i=0;i<value_lofar.size();i++)
    {
        for(int j=0;j<xlength;j++)
        {
            m_pColorMap->data()->setCell(j,i,value_lofar[i][j]);
        }
    }
    m_pColorMap->rescaleDataRange(true);
    fp3->rescaleAxes();//自适应大小

    ui->widget->replot();
}

void MainWindow::Bars_domain_init()
{
    QCPAxis *keyAxis = ui->widget_QCPBars->xAxis;
    QCPAxis *valueAxis = ui->widget_QCPBars->yAxis;
    fossil = new QCPBars(keyAxis, valueAxis);  // 使用xAxis作为柱状图的key轴，yAxis作为value轴

    fossil->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    fossil->setName("Fossil fuels"); // 设置柱状图的名字，可在图例中显示
    fossil->setPen(QPen(QColor(0, 168, 140).lighter(130))); // 设置柱状图的边框颜色
    fossil->setBrush(QColor(0, 168, 140));  // 设置柱状图的画刷颜色


    keyAxis->setRange(0, xlength);               // 设置范围
    keyAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    valueAxis->setRange(0, 100);
}
void MainWindow::Bars_show(QVector<double> fossilData)
{
    QVector<double> ticks;
    for(int i=1;i<=xlength;i++)
    {
        ticks <<  i;
    }
    fossil->setData(ticks,fossilData);
    ui->widget_QCPBars->replot();
}

void MainWindow::T_domain_init()
{
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::red));

    //CustomPlot->xAxis->setLabel("t");
    //CustomPlot->yAxis->setLabel("mV");

    CustomPlot->xAxis->setRange(0,xlength);
    CustomPlot->yAxis->setRange(-2000,2000);
    CustomPlot->replot();
}
void MainWindow::T_Show(QVector<double> data)
{
    QVector<double> xx;
    for(int i=0;i<xlength;i++)
    {
        xx <<i;
    }
    CustomPlot->graph(0)->setData(xx,data);
    CustomPlot->replot();
}

void MainWindow::FFT_DISPLAY_init()
{
    ui->widget_3->setWindowTitle("FFT");

    ui->widget_3->addGraph();
    ui->widget_3->graph(0)->setPen(QPen(Qt::green));

//    ui->widget_3->xAxis->setLabel("t");
//    ui->widget_3->yAxis->setLabel("fft(t)");

    ui->widget_3->xAxis->setRange(0,xlength);
    ui->widget_3->yAxis->setRange(0,100);
    ui->widget_3->replot();
}
void MainWindow::FFT_DISPLAY_show(QVector<double> data)
{
    QVector<double> xx;
    for(int i=0;i<xlength;i++)
    {
        xx <<i;
    }

    ui->widget_3->graph(0)->setData(xx,data);
    ui->widget_3->replot();
}
