#include "utils.h"

#include <QUrl>
#include <QStringList>
#include <QFile>

Utils::Utils()
{

}

QString Utils::generateMnemonic(int wordCount)
{
    QFile file(":/data/bip-0039.txt");
    file.open(QIODevice::ReadOnly);
    QString fileData = file.readAll();
    QStringList words = fileData.split('\n', QString::SkipEmptyParts);
    QStringList seed;
    for (int i; i < wordCount; i++) {
        seed.append(words[qrand() % words.length()]);
    }

    return seed.join(' ');
}
