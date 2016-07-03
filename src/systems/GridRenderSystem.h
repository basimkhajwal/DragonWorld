#pragma once

class GridRenderSystem {

public:

    GridRenderSystem(int width, int height, const char* grid);
    ~GridRenderSystem();

    void render(float delta);
};
