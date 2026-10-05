#include "Graphics_Manager.hpp"
#include "Define.hpp"
#include "Input_Manager.hpp"
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(0.5f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n\0";
bool Graphics_Manager::Init() const { return glfwInit() == GLFW_TRUE; }

void Graphics_Manager::Terminate() const { glfwTerminate(); }

GLFW_Window &Graphics_Manager::GetWindow() { return m_window; }

void Graphics_Manager::Run() const {
  uint32 vertexShader = 0;
  if (!m_shader.CreateVertexShader(1, &vertexShaderSource, NULL, vertexShader)) {
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << m_shader.GetShaderInfoLog(vertexShader) << std::endl;
  }

  uint32 fragmentShader1 = 0;
  if (!m_shader.CreateFragmentShader(1, &fragmentShaderSource1, NULL, fragmentShader1)) {
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << m_shader.GetShaderInfoLog(fragmentShader1) << std::endl;
  }

  uint32 fragmentShader2 = 0;
  if (!m_shader.CreateFragmentShader(1, &fragmentShaderSource2, NULL, fragmentShader2)) {
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << m_shader.GetShaderInfoLog(fragmentShader2) << std::endl;
  }

  uint32 shaderProgram1 = m_program.CreateProgram();
  m_program.AttachShader(shaderProgram1, vertexShader);
  m_program.AttachShader(shaderProgram1, fragmentShader1);
  m_program.LinkProgram(shaderProgram1);
  if (!m_program.GetProgramiv(shaderProgram1, GL_LINK_STATUS)) {
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << m_program.GetProgramInfoLog(shaderProgram1) << std::endl;
  }
  glDeleteShader(fragmentShader1);
  uint32 shaderProgram2 = m_program.CreateProgram();
  m_program.AttachShader(shaderProgram2, vertexShader);
  m_program.AttachShader(shaderProgram2, fragmentShader2);
  m_program.LinkProgram(shaderProgram2);
  if (!m_program.GetProgramiv(shaderProgram2, GL_LINK_STATUS)) {
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << m_program.GetProgramInfoLog(shaderProgram2) << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader2);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices1[] = {
      -0.8f,
      -0.3f,
      0.0f, // left
      -0.3f,
      -0.3f,
      0.0f, // right
      -0.55f,
      0.2f,
      0.0f, // top
  };
  float vertices2[] = {
      0.2f,
      -0.3f,
      0.0f, // left
      0.7f,
      -0.3f,
      0.0f, // right
      0.45f,
      0.2f,
      0.0f, // top
  };

  unsigned int VBO1, VAO1;
  glGenVertexArrays(1, &VAO1);
  glGenBuffers(1, &VBO1);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO1);

  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int VBO2, VAO2;
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO2);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO2);

  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);
  while (!m_window.ShouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAO1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    HandleInput();
    m_window.SwapBuffers();
    m_window.PollEvents();
  }
}

void Graphics_Manager::HandleInput() const { Input_Manager::GetInstance()->Update(); }
