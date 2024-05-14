#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "Struct_cam.h"

void MoveCamera(Camera& camera) {
    float angle = -camera.zAlfa / 180 * M_PI;
    float speed = 0;
    if (GetKeyState(VK_SPACE) < 0) {
        camera.z -= 5.0f;
    }
    if (GetKeyState(VK_SHIFT) < 0) {
        camera.z += 5.0f;
    }
    if (GetKeyState(VK_UP) < 0) {
        camera.xAlfa = ++camera.xAlfa > 180 ? 180 : camera.xAlfa;
        speed = 2.0;
    }
    if (GetKeyState(VK_DOWN) < 0) {
        camera.xAlfa = --camera.xAlfa < 0 ? 0 : camera.xAlfa;
        speed = -2.0;
    }
    if (GetKeyState(VK_LEFT) < 0) {
        ++camera.zAlfa;
        speed = 2.0;
        angle -= M_PI * 0.5;
    }
    if (GetKeyState(VK_RIGHT) < 0) {
        --camera.zAlfa;
        speed = 2.0;
        angle += M_PI * 0.5;
    }
    if (GetKeyState('W') < 0) {
        speed = 2.0;
    }
    if (GetKeyState('S') < 0) {
        speed = -2.0;
    }
    if (GetKeyState('A') < 0) {
        speed = 2.0;
        angle -= M_PI * 0.5;
    }
    if (GetKeyState('D') < 0) {
        speed = 2.0;
        angle += M_PI * 0.5;
    }

    if (speed != 0) {
        camera.pos.x += sin(angle) * speed;
        camera.pos.y += cos(angle) * speed;
    }

    glRotatef(-camera.xAlfa, 1, 0, 0);
    glRotatef(-camera.zAlfa, 0, 0, 1);
    glTranslatef(-camera.pos.x, -camera.pos.y, camera.z);
}