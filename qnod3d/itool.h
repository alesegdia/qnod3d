#ifndef ITOOL_H
#define ITOOL_H

#include <QMouseEvent>

/**
 * @brief The ITool interface represents a tool
 * to perform some action on the scene
 */

class ITool
{
public:
    ITool();
    virtual ~ITool() = 0;

    virtual void mousePressEvent(QMouseEvent *e) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *e) = 0;
    virtual void mouseMoveEvent(QMouseEvent *e) = 0;

};

#endif // ITOOL_H
