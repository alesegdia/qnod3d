#ifndef CAMERATRANSFORMTOOL_H
#define CAMERATRANSFORMTOOL_H

#include <QVector2D>

#include "mousedragtool.h"
#include "scenetransform.h"

enum ToolMode {
    SCN_TRANSLATE,
    SCN_ROTATE,
    SCN_SCALE
};

class SceneTransformTool : public MouseDragTool
{
public:
    SceneTransformTool( SceneTransform& sceneTransform );

    void mousePressed(QMouseEvent *e) override;
    void mouseReleased(QMouseEvent *e) override;
    void mouseDragged(QMouseEvent *e) override;

private:
    SceneTransform& m_sceneTransform;
    ToolMode m_toolMode;

};


#endif // CAMERATRANSFORMTOOL_H
