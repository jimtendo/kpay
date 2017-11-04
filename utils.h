#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QStringList>

class Utils
{
public:
    Utils();

    QString generateMnemonic(int wordCount = 24);
};

#endif // UTILS_H
