#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/gl.h>

using std::cerr;
using std::endl;

static uint32_t readShaders(const std::string& vertexShaderFileName,
                            const std::string& fragmentShaderFilename) {

}

static void glfw_error_callback(int error, const char *description) {
  cerr << "Error " << error << ": " << description << endl;
}

class Application {
 public:
  void setup();
  void run();
  void cleanup();
 private:
  void drawImgui();
  void render();

  GLFWwindow* window;
  GLuint vertexbuffer;
  GLuint indexbuffer;
  ImVec4 bg_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  bool showAnotherWindow = false;
};

static float positions[] {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
};
static uint32_t indices[] {
    0, 1, 2,
    2, 3, 0
};

void Application::setup() {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize glfw");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window = glfwCreateWindow(1280, 720, "ImGui GLFW+OpenGL3 example", NULL, NULL);
  if (window == nullptr) {
    throw std::runtime_error("Failed to greate GLFW window");
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync
  gl3wInit();
  std::cout << "Running OpenGL version: " << glGetString(GL_VERSION) << endl;

  // Setup ImGui binding
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void) io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
  ImGui_ImplGlfwGL3_Init(window, true);

  // Setup style
  ImGui::StyleColorsDark();

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, positions, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  uint32_t shaderProgram = readShaders("shaders/simpleVertex.glsl", "shaders/simpleFragment.glsl");
  glUseProgram(shaderProgram);
}

void Application::run() {
  while (!glfwWindowShouldClose(window)) {

    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Rendering
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);

  }
}

void Application::cleanup() {
  ImGui_ImplGlfwGL3_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
}

void Application::drawImgui() {
  ImGui_ImplGlfwGL3_NewFrame();

  // 1. Show a simple window.
  // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
  {
    static float f = 0.0f;
    static int counter = 0;
    ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float *) &bg_color); // Edit 3 floats representing a color

    ImGui::Checkbox("Another Window", &showAnotherWindow);

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
  }
  if (showAnotherWindow) {
    ImGui::Begin("Another Window", &showAnotherWindow);
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      showAnotherWindow = false;
    ImGui::End();
  }

}

void Application::render() {
  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glDrawArrays(GL_TRIANGLES, 0, 3); // Piirretään kolme verteksiä, joista tulee kolmio
  glDisableVertexAttribArray(0);
  glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

}
int main() {
  Application app;
  app.setup();
  app.run();
  app.cleanup();
  return 0;
}