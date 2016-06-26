#include <cmath>
using namespace std;

#include <Camera.h>
#include <Constants.h>

Camera::Camera(float aspectRatio, vec3 pos, float vAngle, float hAngle) {
    setPosition(pos);
    setAngle(vAngle, hAngle);
    resize(aspectRatio);
}

Camera::~Camera() { }

void Camera::resize(float aspectRatio) {
    projectionMatrix = perspective(radians(constants::FOV), aspectRatio, constants::NEAR, constants::FAR);
    dirty = true;
}

void Camera::translate(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
    dirty = true;
}

void Camera::setPosition(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    dirty = true;
}

void Camera::rotate(float vAngle, float hAngle) {
    this->vAngle += vAngle;
    this->hAngle += hAngle;
    dirty = true;
}

void Camera::setAngle(float vAngle, float hAngle) {
    this->vAngle = vAngle;
    this->hAngle = hAngle;
    dirty = true;
}

void Camera::update() {
    dirty = false;

    vec3 direction(
        cos(vAngle) * sin(hAngle),
        sin(vAngle),
        cos(vAngle) * cos(hAngle)
    );

    vec3 right = normalize(cross(constants::UP, direction));
    vec3 up = cross(direction, right);

    viewMatrix = lookAt(position, position+direction, up);
    projectionViewMatrix = projectionMatrix * viewMatrix;
}

mat4& Camera::getProjectionViewMatrix() {
    if (dirty) update();
    return projectionViewMatrix;
}
