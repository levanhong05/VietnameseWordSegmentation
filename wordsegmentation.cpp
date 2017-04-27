#include "wordsegmentation.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

WordSegmentation::WordSegmentation(QObject *parent) :
    QObject(parent)
{
    _dictionary.clear();
}

WordSegmentation::~WordSegmentation()
{
}

bool WordSegmentation::trainingData(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Training data failed";
        return false;
    }

    _dictionary.clear();

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split("\t", QString::SkipEmptyParts);

        if (!parts.isEmpty()) {
            _dictionary.append(parts.first().trimmed());
        }
    }

    file.close();

    return true;
}

void WordSegmentation::LLMM(QString text)
{
    QString word = "";
    QString segmentation;
    QString token = "";

    for (int j = 0; j <= text.length(); j++) {
        if (text[j] == ' ' || text[j] == '\0' || text[j] == ',' || text[j] == '\n' || text[j] == '.') {
            if (checkWord(token)) {
                if (word == "") {
                    word = token;
                } else {
                    segmentation = word + ' ' + token;

                    if (checkWord(segmentation)) {
                        word = segmentation;
                    } else {
                        emit segmentsChanged(word);

                        print(word);
                        word = token;
                    }
                }
            } else {
                if (word == "") {
                    emit segmentsChanged(word);

                    print(word);
                    word = "";
                }
            }

            token = "";
        } else {
            token = token + text[j];
            qDebug() << token;
        }
    }

    emit segmentsChanged(word);

    print(word);
}

void WordSegmentation::print(QString token)
{
    QFile file(QApplication::applicationDirPath() + "/segmentation.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&file);
        out << token << endl;
    }

    file.close();
}

bool WordSegmentation::checkWord(QString token)
{
    return _dictionary.contains(token, Qt::CaseInsensitive);
}

void WordSegmentation::processing(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Load test data failed";

        return;
    }

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine();

        emit segmentsChanged("Sentences: " + line);

        LLMM(line);

        emit segmentsChanged("");
    }
}
