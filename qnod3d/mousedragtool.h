#ifndef MOUSEDRAGTOOL_H
#define MOUSEDRAGTOOL_H

#include "itool.h"

class MouseDragTool : public ITool
{
public:
    MouseDragTool();
    virtual ~MouseDragTool() = 0;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    virtual void mousePressed(QMouseEvent *e) = 0;
    virtual void mouseReleased(QMouseEvent *e) = 0;
    virtual void mouseDragged(QMouseEvent *e) = 0;

protected:
    QVector2D m_mousePressPosition;

private:
    bool m_pressed;


};

#endif // MOUSEDRAGTOOL_H
