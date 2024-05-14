#pragma once
#include "Header.h"

struct Camera {
    float xAlfa = 100;
    float zAlfa = 0;
    float z = -500;
    POINTFLOAT pos = { 0, 0 };
};

void MoveCamera(Camera& camera);