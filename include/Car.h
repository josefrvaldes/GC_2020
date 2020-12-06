
#pragma once

#include "../Objects.h"

class Car : public TPrimitiva
{
    public:
        Car(int DL, int tipo);
        ~Car();

        /*float acceleration = 0.05f;
        float speedWheelRotation = 0.5f;
        float speed = 0.1f;
        float wheelRotation = 0.0f;
        const float MAX_SPEED = 1.5f;
        const float MAX_SPEED_BACKWARDS = -0.75f;
        const float MAX_WHEEL_ROTATION = 3.0f;*/
};

