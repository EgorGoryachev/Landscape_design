#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

using namespace std;

void generateHeightmap(int **heightmap, int heightmapWidth, int randomness);
int** createHeightmap(int heightmapWidth);
void createDisplayList(int** heightmap, int heightmapWidth);
void drawHeightmap();

