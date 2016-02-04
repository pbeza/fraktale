#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QImage>

namespace Logic {

struct Algorithm
{
    void setImage(const QString& path);
    QImage image;
    QList<QColor> pixels;
};

}

#endif // ALGORITHM_H
