#include "Header.h"

GLuint displayList;

int** createHeightmap(int heightmapWidth) {
    int** heightmap = new int* [heightmapWidth];
    for (int i = 0; i < heightmapWidth; i++) {
        heightmap[i] = new int[heightmapWidth];
    }
    return heightmap;
}

void createDisplayList(int** heightmap, int heightmapWidth) {
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);

    glBegin(GL_QUADS);
    for (int i = 0; i < heightmapWidth; i++) {
        for (int j = 0; j < heightmapWidth; j++) {
            float height = heightmap[i][j];
            float colorRatio = height / 255.0f;

            float red = 0.5f + 0.5f * colorRatio;
            float green = 1.0f - 0.2f * colorRatio;
            float blue = 0.5f - 0.5f * colorRatio;

            glColor3f(red, green, blue);
            glVertex3f(i, j, height);
            glVertex3f(i + 1, j, height);
            glVertex3f(i + 1, j + 1, height);
            glVertex3f(i, j + 1, height);
        }
    }
    glEnd();

    glEndList();
}

void drawHeightmap() {
    glCallList(displayList);
}

void generateHeightmap(int **heightmap,const int heightmapWidth, int randomness) {
    srand(time(NULL));
    for (int i = 0; i < heightmapWidth; i++) {
        for (int j = 0; j < heightmapWidth; j++) {
            heightmap[i][j] = 0;
        }
    }

    int rand_number = rand() % randomness;
    heightmap[0][0] = rand_number;
    heightmap[heightmapWidth - 1][0] = rand_number;
    heightmap[0][heightmapWidth - 1] = rand_number;
    heightmap[heightmapWidth - 1][heightmapWidth - 1] = rand_number;

    int tileWidth = heightmapWidth - 1;
    while (tileWidth > 1) {
        int halfSide = tileWidth / 2;

        for (int x = 0; x < heightmapWidth - 1; x += tileWidth) {
            for (int y = 0; y < heightmapWidth - 1; y += tileWidth) {
                int cornerSum = heightmap[x][y] + heightmap[x + tileWidth][y] + heightmap[x][y + tileWidth] + heightmap[x + tileWidth][y + tileWidth];
                int avg = cornerSum / 4;
                avg += rand() % randomness;
                heightmap[x + halfSide][y + halfSide] = avg;
            }
        }

        for (int x = 0; x < heightmapWidth - 1; x += halfSide) {
            for (int y = (x + halfSide) % tileWidth; y < heightmapWidth - 1; y += tileWidth) {
                int avg = heightmap[(x - halfSide + heightmapWidth - 1) % (heightmapWidth - 1)][y] + heightmap[(x + halfSide) % (heightmapWidth - 1)][y] + heightmap[x][(y + halfSide) % (heightmapWidth - 1)] + heightmap[x][(y - halfSide + heightmapWidth - 1) % (heightmapWidth - 1)];
                avg /= 4;
                avg += rand() % randomness;
                heightmap[x][y] = avg;

                if (x == 0) {
                    heightmap[heightmapWidth - 1][y] = avg;
                }
                if (y == 0) {
                    heightmap[x][heightmapWidth - 1] = avg;
                }
            }
        }

        randomness = max(randomness / 2, 1);
        tileWidth /= 2;
    }
}


