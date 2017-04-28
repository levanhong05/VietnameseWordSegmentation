#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>

#include "configure.h"

class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(int window_length, QString path, StrMapReference ref, QObject *parent = 0);
    virtual ~Machine();

    void extract(QString sentence, StrMapReference ref);
    void getProblem();
    void delProblem();

    /* Learner */
    void training();
    void print();

    double closeTest();
    void featuresSelection();

    /* Predictor */
    bool load();
    QString segment(QString sentence);

private:
    size_t getByteOfUTF8(unsigned char c);
    QString itostr(int x);
    void convert(QString sentence);

private:
    size_t index_SPACE;
    size_t index_UNDER;
    size_t reference;

    Feats* 		feats;
    DicMap		dicmap;
    StrMap		strmap;
    model*		_model;
    problem   _problem;

    QList<featuresOfSyllabel>* vfeats;

    int  WINDOW_LENGTH;
    QString PATH;

};

#endif // MACHINE_H
