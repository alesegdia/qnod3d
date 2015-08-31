#include "mousedragtool.h"

MouseDragTool::MouseDragTool()
{

}

MouseDragTool::~MouseDragTool()
{

}

void MouseDragTool::mousePressEvent(QMouseEvent *e)
{
    m_pressed = true;
    m_mousePressPosition = QVector2D(e->localPos());
    mousePressed(e);
}

void MouseDragTool::mouseReleaseEvent(QMouseEvent *e)
{
    m_pressed = false;
    mouseReleased(e);
}

void MouseDragTool::mouseMoveEvent(QMouseEvent *e)
{
    if( m_pressed ) {
        mouseDragged(e);
        m_mousePressPosition = QVector2D( e->localPos() );
    }
}

