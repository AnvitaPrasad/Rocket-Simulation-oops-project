#ifndef FINANGLES_H
#define FINANGLES_H

#include "EulerAngles.h"

using namespace std;

class FinAngles {
public:
    float finRoll, finPitch, finYaw;
    void adjustFins(const EulerAngles& euler);
};

#endif
