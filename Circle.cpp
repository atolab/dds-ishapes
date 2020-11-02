/**
 * @file
 */
#include <QtGui/qpainter.h>
#include <vector>
#include "Circle.hpp"

namespace demo { namespace ishapes {

Circle::Circle(const QRect& bounds,
               ShapeDynamics::ref_type dynamics,
               const QPen& pen,
               const QBrush& brush,
               bool targeted)
    :   Shape(bounds, pen, brush, targeted),
        dynamics_(dynamics)
{ }

void
Circle::update()
{
    dynamics_->simulate();
}

void
Circle::paint(QPainter& painter)
{
    painter.setBrush(brush_);
    painter.setPen(pen_);
    std::vector<QPoint> plist = dynamics_->getPositionList();
    std::vector<QPoint>::iterator idx = plist.begin();

    #ifdef TESTBUILD
    std::cout << "Circle plist sz: " << plist.size() << std::endl;
    #endif
    QBrush black( QColor(0x33, 0x33, 0x33), Qt::SolidPattern);
    QBrush white( QColor(0xFF, 0xFF, 0xFF), Qt::SolidPattern);
    QBrush brush;
    while (idx != plist.end())
    {
        painter.drawEllipse(idx->x(),
                            idx->y(),
                            bounds_.width(),
                            bounds_.height());
        if (targeted_)
            brush = black;
        else
            brush = white;

        int X0 = idx->x() + (bounds_.width()/2);
        int Y0 = idx->y() + (bounds_.height()/2);
        int W = bounds_.width()/3;
        int H = bounds_.height()/3;
        painter.setBrush(brush);
        painter.drawEllipse(X0 -W/2,
                            Y0 - H/2,
                            W,
                            H);
        painter.setBrush(brush_);

        ++idx;
    }
    plist.erase(plist.begin(), plist.end());
}
}}
