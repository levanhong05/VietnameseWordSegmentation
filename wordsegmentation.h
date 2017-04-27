#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

#include <QObject>

class WordSegmentation : public QObject
{
    Q_OBJECT
public:
    explicit WordSegmentation(QObject *parent = 0);
    ~WordSegmentation();

    bool trainingData(QString path);

    void processing(QString path);

private:
    void LLMM(QString text);
    void print(QString token);
    bool checkWord(QString token);

signals:
    void segmentsChanged(QString text);

private:
    QStringList _dictionary;
};

#endif // WORDSEGMENTATION_H
