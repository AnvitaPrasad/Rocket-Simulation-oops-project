#ifndef ACCELERATION_H
#define ACCELERATION_H

using namespace std;

class Acceleration {
public:
    float calculate(float previousVelocity, float newVelocity, float deltaTime);
};

#endif
