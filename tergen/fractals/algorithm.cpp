#include <QColor>
#include <QDebug>
#include <QImage>

#include "algorithm.h"

void Logic::Algorithm::setImage(const QString& path)
{
    if (!image.load(path))
        return;

    image = image.convertToFormat(QImage::Format_ARGB32);

    /*
     * Learn more:
     * - http://doc.qt.io/qt-5.5/qimage.html#pixel-manipulation
     * - http://doc.qt.io/qt-5.5/qimage.html#scanLine
     */

    pixels.clear();

    // Read line by line, pixel by pixel and store all pixels in list

    for (int i = 0; i < image.height(); i++)
    {
        QRgb *scanLine = (QRgb*)image.scanLine(i);
        for (unsigned int j = 0; j < image.bytesPerLine() / sizeof(QRgb); j += sizeof(QRgb))
        {
            QRgb *pix = scanLine + j;
            pixels.append(QColor(*pix));
        }
    }
}
