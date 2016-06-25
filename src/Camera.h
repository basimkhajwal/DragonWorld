#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Camera {

    mat4 projectionMatrix, viewMatrix, projectionViewMatrix;
    bool dirty;
    vec3 position;
    float vAngle, hAngle;

    void update();

public:
    
    Camera(float aspectRatio, vec3 pos, float vAngle, float hAngle);
    ~Camera();

    void resize(float aspectRatio);
    void resize(int width, int height) { resize((float) width / (float) height); }

    void translate(vec3 amount) { translate(amount.x, amount.y, amount.z); }
    void translate(float x, float y, float z);
    void setPosition(vec3 pos) { setPosition(pos.x, pos.y, pos.z); }
    void setPosition(float x, float y, float z);

    void rotate(float vAngle, float hAngle);
    void setAngle(float vAngle, float hAngle);

    vec3 getPosition() { return position; };
    float getVerticalAngle() { return vAngle; }
    float getHorizontalAngle() { return hAngle; }
    mat4& getProjectionViewMatrix();
};
