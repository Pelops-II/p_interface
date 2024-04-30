#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void showFps(GLFWwindow *window) {
  static double prevTime = glfwGetTime();
  static int frameCount = 0;
  double currentTime = glfwGetTime();
  double elapsed = currentTime - prevTime;

  if (elapsed > 0.25) {
    prevTime = currentTime;
    double fps = (double)frameCount / elapsed;
    double msPerFrame = 1000.0 / fps;
    char tmp[128];
    sprintf(tmp, "FPS: %.2f, Frame time: %.2f ms", fps, msPerFrame);
    glfwSetWindowTitle(window, tmp);
    frameCount = 0;
  }
  frameCount++;
}

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    showFps(window);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
