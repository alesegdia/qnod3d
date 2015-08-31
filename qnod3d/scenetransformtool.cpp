#include "scenetransformtool.h"

SceneTransformTool::SceneTransformTool(SceneTransform &sceneTransform)
    : m_sceneTransform(sceneTransform)
{

}

void SceneTransformTool::mousePressed(QMouseEvent *e)
{
    if( e->button() == Qt::MouseButton::RightButton )
    {
        m_toolMode = ToolMode::SCN_SCALE;
    }
    else if( e->button() == Qt::MouseButton::LeftButton )
    {
        m_toolMode = ToolMode::SCN_TRANSLATE;
    }
    else if( e->button() == Qt::MouseButton::MidButton )
    {
        m_toolMode = ToolMode::SCN_ROTATE;
    }
}

void SceneTransformTool::mouseReleased(QMouseEvent *e)
{

}

void SceneTransformTool::mouseDragged(QMouseEvent *e)
{
    QVector2D deltaMousePos = QVector2D( e->localPos() ) - m_mousePressPosition;
    deltaMousePos.setY( -deltaMousePos.y() );

    switch( m_toolMode )
    {

    case ToolMode::SCN_ROTATE:
        m_sceneTransform.m_rotation_x *= QQuaternion::fromEulerAngles(
                    QVector3D(   0.f, deltaMousePos.x(), 0.f ) );
        m_sceneTransform.m_rotation_y *= QQuaternion::fromEulerAngles(
                    QVector3D( - deltaMousePos.y(), 0.f, 0.f ) );
        break;

    case ToolMode::SCN_TRANSLATE:
        m_sceneTransform.m_position += deltaMousePos / 40;
        break;

    case ToolMode::SCN_SCALE:
        m_sceneTransform.m_scale += deltaMousePos.y() * m_sceneTransform.m_scale / 100.f;
        m_sceneTransform.m_scale = qMax( 0.f, m_sceneTransform.m_scale );
        break;

    }
}
