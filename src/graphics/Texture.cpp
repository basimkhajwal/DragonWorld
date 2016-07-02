#include <cstdio>
using namespace std;

#include <SOIL.h>

#include <graphics/Texture.h>

Texture::Texture(const char* filePath) {

    /* Load image data*/
    printf("TEXTURE:\tLoading texture %s\n", filePath);
    unsigned char* imageData = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);

    /* Check for error */
    if (imageData == NULL) {
        printf("TEXTURE:\tError loading %s\n", filePath);
        printf("TEXTURE:\t%s\n", SOIL_last_result());
        return;
    }

    /* Create and bind texture object */
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    /* Free the data */
    SOIL_free_image_data(imageData);

    /* Apply texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}
