#include "wordsegmentation.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#define MAX_WORD_LENGTH 4

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
    QStringList segmentation;

    QStringList tokens = text.split(QRegExp("\\ |\\,|\\.|\\;|\\!"), QString::SkipEmptyParts);

    while (!tokens.isEmpty()) {
        segmentation.append(tokens[0]);

        int length = 1;

        QString token = segmentation.join(" ");

        if (checkWord(token)) {
            word = token;
        }

        while (length <= MAX_WORD_LENGTH) {
            if (tokens.size() >= (length + 1)) {
                segmentation.append(tokens[length]);

                token = segmentation.join(" ");

                if (checkWord(token)) {
                    word = token;
                }
            }

            length++;
        }

        if (word == "") {
            emit segmentsChanged(tokens[0] + ": Not found in directory.");

            tokens.takeFirst();
        } else {
            emit segmentsChanged(word);

            print(word);

            segmentation = word.split(" ", QString::SkipEmptyParts);

            tokens = removeTokens(tokens, segmentation.size());
        }

        word = "";
        segmentation.clear();
    }
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

QStringList WordSegmentation::removeTokens(QStringList tokens, int length)
{
    while (length > 0 && !tokens.isEmpty()) {
        tokens.takeFirst();

        length--;
    }

    return tokens;
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
