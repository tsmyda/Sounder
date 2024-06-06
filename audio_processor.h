#ifndef AUDIO_PROCESSOR_H
#define AUDIO_PROCESSOR_H

#include "frequency_map.h"
#include "qaudioinput.h"
#include "qbuffer.h"
#include <QVector>
#include <fftw3.h>
#include <QtMultimedia/QAudioDevice>
#include <QAudioSource>

class AudioProcessor
{
public:
    AudioProcessor(int numSamples, int sampleFreq, int audibleRangeStart, int audibleRangeEnd);
    ~AudioProcessor();

    void processSamples();
    void processAudioIn();


    QVector<double> getSamples() const;
    QVector<double> getFftValues() const;
    int getNumSapmles() const;
    int getSampleFreq() const;
    int getAudibleRangeStart() const;
    int getAudibleRangeEnd() const;
    void openBuffer();
    void setAudioInput(QAudioDevice d);
    void setVolumeOfInputDevice(double value);
    QVector<double> getmIndices() const;
    QVector<double> getmSamples() const;
    QVector<double> getFftIndices() const;
    QAudioDevice getAudioDevice() const;
    double getCurrentFrequency() const;
    double calculateClosestFrequency();
    double getClosestFrequency() const;
    QString getClosestNote() const;
private:
    int numSamples;
    int sampleFreq;
    int audibleRangeStart;
    int audibleRangeEnd;
    double closestFrequency;
    double currentFrequency;
    QAudioDevice device;
    QAudioSource* audioInput = nullptr;
    QAudioFormat format;
    QBuffer mInputBuffer;
    QVector<double> mIndices;
    QVector<double> mFftIndices;
    QVector<double> mSamples;
    QVector<double> mFftValues;
    FrequencyMap frequencyMap;
    fftw_plan mFftPlan;
    double* mFftIn;
    double* mFftOut;
};

#endif // AUDIO_PROCESSOR_H
