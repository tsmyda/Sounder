#include "frequency_map.h"
#include "qmath.h"

FrequencyMap::FrequencyMap()
{
    populateFrequencyMap();
}

QMap<double, QString> FrequencyMap::getFrequencyMap() const
{
    return frequencyMap;
}

void FrequencyMap::populateFrequencyMap()
{
    // Definicja częstotliwości i ich nazw
    // Notacja muzyczna dla oktaw 0-8
    QStringList noteNames = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int numOctaves = 9;

    for (int octave = 0; octave < numOctaves; ++octave) {
        for (int noteIndex = 0; noteIndex < noteNames.size(); ++noteIndex) {
            QString noteName = noteNames[noteIndex] + QString::number(octave);
            double frequency = 16.35 * qPow(2.0, octave + noteIndex / 12.0);
            frequencyMap.insert(frequency, noteName);
        }
    }
}
