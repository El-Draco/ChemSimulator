#include "orbitcameracontroller.h"
#include <Qt3DCore/QNode>
#include <QtMath>
#include <QCamera>

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

    cam->translate(QVector3D(clampInputs(state.rightMouseButtonActive ? state.rxAxisValue : 0, state.txAxisValue) * linearSpeed(),
                                   clampInputs(state.rightMouseButtonActive ? state.ryAxisValue : 0, state.tyAxisValue) * linearSpeed(),
                                   state.tzAxisValue * 3 * linearSpeed()) * dt,
                    Qt3DRender::QCamera::DontTranslateViewCenter);
    cam->setViewCenter(centerPoint_);
    //cam->rollAboutViewCenter(0.0f);
}
