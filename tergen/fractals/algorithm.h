#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QImage>

namespace Logic {

class Algorithm
{
public:
    void setImage(const QString& path);
private:
    QImage image;
    QList<QColor> pixels;
};

}

#endif // ALGORITHM_H
