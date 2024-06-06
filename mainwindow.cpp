#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioProcessor(96000, 48000, 10, 880)
{
    ui->setupUi(this);
    this->setWindowTitle("Sounder");
    this->setFixedSize(1030, 650);
    QList<QAudioDevice> inputDevices =QMediaDevices::audioInputs();
    for (QAudioDevice d : inputDevices) {
        ui->inputDeviceComboBox->addItem(d.description(), QVariant::fromValue(d));
    }
    FrequencyMap freqMap = FrequencyMap();
    QPalette p = this->palette();
    p.setColor(QPalette::Highlight, QColor(Qt::green));
    this->setPalette(p);


    ui->noteLabel->setText("No note detected");
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot->legend->setVisible(false);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setSelectedFont(legendFont);
    ui->plot->legend->setSelectableParts(QCPLegend::spItems);
    ui->plot->yAxis->setLabel("Amplitude");
    ui->plot->xAxis->setLabel("Sample");
    ui->plot->yAxis->setRange(-1.0, 1.0);
    ui->plot->clearGraphs();
    ui->plot->addGraph();

    ui->plot->graph()->setPen(QPen(Qt::black));
    ui->plot->graph()->setName("Audio In");

    /* Setup plot 2 */
    ui->plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot2->legend->setVisible(false);
    ui->plot2->yAxis->setLabel("Magnitude");
    ui->plot2->xAxis->setLabel("Frequency");
    ui->plot2->xAxis->setRange(audioProcessor.getAudibleRangeStart(), audioProcessor.getAudibleRangeEnd());
    ui->plot2->yAxis->setRange(0.0, 200.0);
    ui->plot2->clearGraphs();
    ui->plot2->addGraph();

    ui->plot2->graph()->setPen(QPen(Qt::black));
    ui->plot2->graph()->setName("fft");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_clicked()
{
    QList<QAudioDevice> inputDevices =QMediaDevices::audioInputs();
    for (QAudioDevice d : inputDevices) {
        ui->inputDeviceComboBox->addItem(d.description(), QVariant::fromValue(d));
    }

    ui->inputDeviceComboBox->clear();
    for (QAudioDevice d : inputDevices) {
        ui->inputDeviceComboBox->addItem(d.description(),QVariant::fromValue(d));
    }
}

void MainWindow::on_stopButton_clicked() {
    if (timer.isActive()) timer.stop();
}

void MainWindow::on_useButton_clicked()
{
    if (timer.isActive() && ui->inputDeviceComboBox->currentData().value<QAudioDevice>() == audioProcessor.getAudioDevice()) return;
    QVariant v = ui->inputDeviceComboBox->currentData();
    qDebug()<<v;
    QAudioDevice dev = v.value<QAudioDevice>();

    audioProcessor.setAudioInput(dev);
    audioProcessor.setVolumeOfInputDevice(ui->volumeSlider->value()/1000.0);
    QObject::connect(&timer, &QTimer::timeout, this, &MainWindow::processAudioIn);
    timer.start(100);
    qDebug()<<"Started";
    audioProcessor.openBuffer();
}

void MainWindow::processAudioIn()
{
    audioProcessor.processAudioIn();
    samplesUpdated();
}

void MainWindow::on_volumeSlider_sliderMoved(int position)
{
    audioProcessor.setVolumeOfInputDevice((double) position/1000.0);
}

void MainWindow::samplesUpdated()
{
    ui->plot->graph(0)->setData(audioProcessor.getmIndices(),audioProcessor.getmSamples());
    ui->plot->xAxis->rescale();
    ui->plot->replot();
    QVector<double> fftVec = audioProcessor.getFftValues();
    QVector<double> mFftIndices = audioProcessor.getFftIndices();
    ui->plot2->graph(0)->setData(mFftIndices.mid(0,fftVec.length()),fftVec);
    ui->plot2->replot();
    ui->noteLabel->setText(audioProcessor.getClosestNote());
    double deltaFreq = audioProcessor.getCurrentFrequency()-audioProcessor.getClosestFrequency();
    ui->progressBar->setValue(50+deltaFreq);
    ui->valueProgressBarLabel->setText(QString::number((int)deltaFreq));

}
