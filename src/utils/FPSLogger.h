#pragma once

class FPSLogger {

    float frameTime = 0;
    int framesCounted = 0;

public:

    FPSLogger();
    ~FPSLogger();

    void log(float delta);
};
