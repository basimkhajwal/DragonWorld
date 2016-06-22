#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Camera {

    mat4 projectionMatrix, viewMatrix, projectionViewMatrix;
    bool dirty;
    
public:
    
    Camera();
    ~Camera();
    
    
};
