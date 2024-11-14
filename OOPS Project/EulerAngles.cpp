#include "EulerAngles.h"

EulerAngles::EulerAngles(float r, float p, float y) : roll(r), pitch(p), yaw(y) {}

EulerAngles EulerAngles::operator+(const EulerAngles& other) const {
    return EulerAngles(roll + other.roll, pitch + other.pitch, yaw + other.yaw);
}
