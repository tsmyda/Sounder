#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaDevices>
#include <QAudioDevice>
#include "audio_processor.h"
#include "qtimer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refreshButton_clicked();
    void on_useButton_clicked();
    void on_stopButton_clicked();
    void processAudioIn();
    void on_volumeSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    void samplesUpdated();
    AudioProcessor audioProcessor;
    QList<QAudioDevice> mInputDevices;
    QAudioInput *mAudioIn = nullptr;
    QTimer timer;
    FrequencyMap freqMap;
};
#endif // MAINWINDOW_H
