#include "PositionVelocity.h"

PositionVelocity::PositionVelocity(float p, float v) : position(p), velocity(v) {}

void PositionVelocity::update(float thrust, float deltaTime) {
    velocity += thrust * deltaTime; // Update velocity
    position += velocity * deltaTime; // Update position
}
