#include "Interface.hpp"

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
  window = glfwCreateWindow(1600, 900, "p_interface_test", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    spdlog::error("Failed to initialize OpenGL context");
    return -1;
  }

  // Initialize ImGui with GLFW & OpenGL && ImPlot
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Show FPS
    showFps(window);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Dockspace
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    // Demo windows
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();

    // Render the window
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}
