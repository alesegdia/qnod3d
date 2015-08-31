#ifndef CAMERATRANSFORMTOOL_H
#define CAMERATRANSFORMTOOL_H

#include <QVector2D>

#include "itool.h"
#include "scenetransform.h"

enum ToolMode {
    SCN_TRANSLATE,
    SCN_ROTATE,
    SCN_SCALE
};

class SceneTransformTool : public ITool
{
public:
    SceneTransformTool( SceneTransform& sceneTransform );

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    SceneTransform& m_sceneTransform;
    bool m_pressed;
    ToolMode m_toolMode;
    QVector2D m_mousePressPosition;

};


#endif // CAMERATRANSFORMTOOL_H
