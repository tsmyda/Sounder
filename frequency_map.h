#ifndef FREQUENCY_MAP_H
#define FREQUENCY_MAP_H

#include <QMap>
#include <QString>

class FrequencyMap
{
public:
    FrequencyMap();
    QMap<double, QString> getFrequencyMap() const;

private:
    void populateFrequencyMap();
    QMap<double, QString> frequencyMap;
};

#endif // FREQUENCY_MAP_H
