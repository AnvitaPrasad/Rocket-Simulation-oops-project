#ifndef EULERANGLES_H
#define EULERANGLES_H

using namespace std;

class EulerAngles {
public:
    float roll, pitch, yaw;
    EulerAngles(float r = 0, float p = 0, float y = 0);
    EulerAngles operator+(const EulerAngles& other) const;
};

#endif
