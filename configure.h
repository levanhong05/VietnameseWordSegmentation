#ifndef CONFIGURE
#define CONFIGURE

#include <QSet>
#include <QPair>
#include <QObject>

const int MAX_WORD_LENGTH = 3;

const char SPACE = ' ';
const char UNDER = '_';
const size_t LEARN   = 0;
const size_t PREDICT = 1;
const QString SYMBOLS = "@`#$%&~|[]<>'(){}*+-=;,?.!:\"/";

typedef QPair<size_t, QSet<size_t>* > Feat;
typedef size_t StrMapReference;
typedef size_t FeatsReference;

#endif // CONFIGURE

