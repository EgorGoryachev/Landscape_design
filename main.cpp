#include "Header.h"
#include "Struct_cam.h"



int main(void)
{
    Camera camera;
    int randomness = 0;
    int heightmapWidth = 0;
    

    cout << "Enter size fro map: ";
    cin >> heightmapWidth;
    cout << "Enter the randomness: ";
    cin >> randomness;
    heightmapWidth += 1;

    int** heightmap = createHeightmap(heightmapWidth);

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1200, 800, "3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glFrustum(-1.5, 1.5, -1.5, 1.5, 2, 1500);
    glEnable(GL_DEPTH_TEST);
    generateHeightmap(heightmap, heightmapWidth, randomness);
    createDisplayList(heightmap, heightmapWidth);
    while (!glfwWindowShouldClose(window))
    {
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        MoveCamera(camera);
        drawHeightmap();
        glPopMatrix();
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
            generateHeightmap(heightmap, heightmapWidth, randomness);
            createDisplayList(heightmap, heightmapWidth);
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            cout << "Enter the randomness: ";
            cin >> randomness;
            generateHeightmap(heightmap, heightmapWidth, randomness);
            createDisplayList(heightmap, heightmapWidth);
        }
    }

    glfwTerminate();
    return 0;
}