#include <cstdio>
using namespace std;

#include <utils/FPSLogger.h>

FPSLogger::FPSLogger() : frameTime(0), framesCounted(0) {  }
FPSLogger::~FPSLogger() {  }

void FPSLogger::log(float delta) {
    frameTime += delta;
    framesCounted++;

    if (frameTime >= 1) {
        printf("FPS-LOG:\t%d\n", framesCounted);
        frameTime = framesCounted = 0;
    }
}
