#include "Acceleration.h"

float Acceleration::calculate(float previousVelocity, float newVelocity, float deltaTime) {
    return (newVelocity - previousVelocity) / deltaTime;
}
