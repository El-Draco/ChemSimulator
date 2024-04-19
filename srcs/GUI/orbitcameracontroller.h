#ifndef ORBITCAMERACONTROLLER_H
#define ORBITCAMERACONTROLLER_H

#include <QAbstractCameraController>
#include <QVector3D>

class OrbitCameraController : public Qt3DExtras::QAbstractCameraController
{
    Q_OBJECT
public:
    explicit OrbitCameraController(Qt3DCore::QNode* parent = nullptr);
    ~OrbitCameraController() = default;

private:
    void moveCamera(const QAbstractCameraController::InputState& state, float dt) override;

    // Center point to orbit around
    QVector3D centerPoint_{0.0f, 0.0f, 1.0f};
};
#endif // ORBITCAMERACONTROLLER_H
