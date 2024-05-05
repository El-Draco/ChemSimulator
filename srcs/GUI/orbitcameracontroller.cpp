#include "orbitcameracontroller.h"
#include <Qt3DCore/QNode>
#include <Qt3DRender/QCamera>
#include <QtMath>

inline float clampInputs(float input1, float input2)
{
    float axisValue = input1 + input2;
    return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
}


OrbitCameraController::OrbitCameraController(Qt3DCore::QNode* parent)
    : Qt3DExtras::QAbstractCameraController(parent) {}

void OrbitCameraController::moveCamera(const Qt3DExtras::QAbstractCameraController::InputState &state, float dt) {
    auto cam = camera();
    if (!cam) return;

    currentZoom = (centerPoint_ - cam->position()).length();

    if(state.tzAxisValue != 0) {
        if ((state.tzAxisValue > 0) & (currentZoom < 10))
            return;
        if ((state.tzAxisValue < 0) & (currentZoom > 70))
            return;

        float change = state.tzAxisValue * 200 * dt;
        cam->translate(QVector3D(0, 0, change), Qt3DRender::QCamera::DontTranslateViewCenter);
    }

    if(state.rightMouseButtonActive) {
        auto translation = QVector3D(state.rxAxisValue * linearSpeed(),
                                     state.ryAxisValue * linearSpeed(), 0);
        cam->translate(translation * dt, Qt3DRender::QCamera::DontTranslateViewCenter);
        cam->setViewCenter(centerPoint_);
        QVector3D direction = (centerPoint_ - cam->position()).normalized();
        cam->setPosition(centerPoint_ - direction * currentZoom);
        //cam->setUpVector(upVec);
    }
}

void OrbitCameraController::updateCenterPoint(const QVector3D &viewCenter) {
    qDebug() << viewCenter;
    centerPoint_ = QVector3D(viewCenter);
}
