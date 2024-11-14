#ifndef POSITIONVELOCITY_H
#define POSITIONVELOCITY_H

using namespace std;

class PositionVelocity {
public:
    float position;
    float velocity;
    PositionVelocity(float p = 0.0, float v = 0.0);
    void update(float thrust, float deltaTime);
};

#endif
