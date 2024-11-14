#include "FinAngles.h"

void FinAngles::adjustFins(const EulerAngles& euler) {
    finRoll = -euler.roll * 0.5;
    finPitch = -euler.pitch * 0.5;
    finYaw = -euler.yaw * 0.5;
}
