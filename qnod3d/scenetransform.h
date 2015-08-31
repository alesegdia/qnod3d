#ifndef CAMERA_H
#define CAMERA_H

#include <QQuaternion>
#include <QVector3D>

class SceneTransform
{
public:
    SceneTransform();

    QQuaternion m_rotation_x;
    QQuaternion m_rotation_y;
    QVector3D m_position;
    float m_scale = 1;

};

#endif // CAMERA_H
