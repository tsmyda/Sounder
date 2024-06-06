#include "audio_processor.h"
#include "qdebug.h"

AudioProcessor::AudioProcessor(int numSamples, int sampleFreq, int audibleRangeStart, int audibleRangeEnd)
    : numSamples(numSamples), sampleFreq(sampleFreq), audibleRangeStart(audibleRangeStart), audibleRangeEnd(audibleRangeEnd)
{
    format.setSampleRate(sampleFreq);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    frequencyMap = FrequencyMap();

    mFftIn = fftw_alloc_real(numSamples);
    mFftOut = fftw_alloc_real(numSamples);
    mFftPlan = fftw_plan_r2r_1d(numSamples, mFftIn, mFftOut, FFTW_R2HC, FFTW_MEASURE);

    for (int i = 0; i < numSamples; i ++) {
        mIndices.append((double)i);
        mSamples.append(0);
    }

    double freqStep = (double)sampleFreq / (double)numSamples;
    double f = audibleRangeStart;
    while (f < audibleRangeEnd) {
        mFftIndices.append(f);
        f += freqStep;
    }
}

AudioProcessor::~AudioProcessor()
{
    free(audioInput);
    fftw_free(mFftIn);
    fftw_free(mFftOut);
    fftw_destroy_plan(mFftPlan);
}

void AudioProcessor::processAudioIn()
{
    mInputBuffer.seek(0);
    QByteArray ba = mInputBuffer.readAll();

    int num_samples = ba.length() / 2;
    int b_pos = 0;
    for (int i = 0; i < num_samples; i ++) {
        int16_t s;
        s = ba.at(b_pos++);
        s |= ba.at(b_pos++) << 8;
        if (s != 0) {
            mSamples.append((double)s / 32768.0);
        } else {
            mSamples.append(0);
        }
    }
    mInputBuffer.buffer().clear();
    mInputBuffer.seek(0);

    int n = mSamples.length();
    if (n > numSamples) mSamples = mSamples.mid(n - numSamples,-1);

    memcpy(mFftIn, mSamples.data(), numSamples*sizeof(double));

    fftw_execute(mFftPlan);

    QVector<double> fftVec;

    for (int i = (numSamples/sampleFreq)*audibleRangeStart;
         i < (numSamples/sampleFreq)*audibleRangeEnd;
         i ++) {
        fftVec.append(abs(mFftOut[i]));
    }
    mFftValues = fftVec;

    int maxIndex = 0;
    double maxValue = fftVec[0];

    for (int i = 1; i < fftVec.size(); ++i) {
        if (fftVec[i] > maxValue) {
            maxValue = fftVec[i];
            maxIndex = i;
        }
    }

    currentFrequency = audibleRangeStart+maxIndex*sampleFreq/numSamples;
    closestFrequency = calculateClosestFrequency();
}

double AudioProcessor::getClosestFrequency() const {
    return closestFrequency;
}

QString AudioProcessor::getClosestNote() const {
    return frequencyMap.getFrequencyMap().value(closestFrequency);
}

double AudioProcessor::calculateClosestFrequency() {
    double closestFreq = -1;
    double minDiff = std::numeric_limits<double>::max();

    QMap<double, QString> map = frequencyMap.getFrequencyMap();

    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        double diff = std::abs(it.key() - currentFrequency);
        if (diff < minDiff) {
            minDiff = diff;
            closestFreq=it.key();
        }
    }
    return closestFreq;
}

int AudioProcessor::getAudibleRangeStart() const {
    return this->audibleRangeStart;
}

int AudioProcessor::getAudibleRangeEnd() const {
    return this->audibleRangeEnd;
}

double AudioProcessor::getCurrentFrequency() const {
    return currentFrequency;
}


QVector<double> AudioProcessor::getFftValues() const {
    return mFftValues;
}

QVector<double> AudioProcessor::getFftIndices() const {
    return mFftIndices;
}

void AudioProcessor::openBuffer() {
    mInputBuffer.open(QBuffer::ReadWrite);
    audioInput->start(&mInputBuffer);
}

void AudioProcessor::setAudioInput(QAudioDevice dev) {
    if (audioInput) delete audioInput;
    audioInput = nullptr;
    audioInput = new QAudioSource(dev, format);
    device = dev;
}

QAudioDevice AudioProcessor::getAudioDevice() const {
    return device;
}

void AudioProcessor::setVolumeOfInputDevice(double value) {
    if (this->audioInput) {
        this->audioInput->setVolume(value);
    }
}

QVector<double> AudioProcessor::getmIndices() const {
    return mIndices;
}

QVector<double> AudioProcessor::getmSamples() const {
    return mSamples;
}
