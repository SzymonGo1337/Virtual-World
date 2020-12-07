#include "core.hpp"
#include "shader.hpp"
#include <vector>

Vertex verts[] = {
    //front
    {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f},   {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f},   {0.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f},    {1.0f, 1.0f}},
    
    //right
    {{0.5f, -0.5f, 0.5f},   {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f},    {0.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f},   {1.0f, 1.0f}},

    //back
    {{0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f},   {0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f}},
    
    //left
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f},  {1.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f},  {0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f},   {1.0f, 1.0f}},

    //top
    {{-0.5f, 0.5f, 0.5f},   {0.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f},    {1.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f},  {0.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f},   {1.0f, 1.0f}},

    //bottom
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f},  {0.0f, 1.0f}},
    {{0.5f, -0.5f, 0.5f},   {1.0f, 1.0f}},
};

uint indices[] = {
    0, 2, 1, 1, 2, 3, //front
    4, 6, 5, 5, 6, 7, //right
    8, 10, 9, 9, 10, 11, //back
    12, 14, 13, 13, 14, 15, //left
    16, 18, 17, 17, 18, 19, //top
    20, 22, 21, 21, 22, 23 //bottom 
};

void OpenGLMessageCallback(uint, uint, uint, uint severity, int, const char* message, const void*) {
	std::cout << message << '\n';
}

const char* vertSrc = R"(
    #version 460 core

    layout (location = 0) in vec3 a_Pos;
    layout (location = 1) in vec2 a_TexCoord;

    out vec2 v_TexCoord;

    uniform mat4 u_viewProjection = mat4(1.0);
    uniform mat4 u_transform = mat4(1.0);

    void main()
    {
        v_TexCoord = a_TexCoord;
        gl_Position =  u_viewProjection * u_transform * vec4(a_Pos, 1.0);
    }	
)";

const char* fragSrc = R"(
    #version 460 core

    uniform vec4 u_Color = vec4(1.0, 1.0, 1.0, 1.0);
    uniform sampler2D u_Texture;
                
    out vec4 Color;

    in vec2 v_TexCoord;


    void main()
    {
        Color = vec4(v_TexCoord, 0, 1); //u_Color; //* texture(u_Texture, v_TexCoord);
    }
)";

Mat4 view = Mat4(1);

void input(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        view[3].z -= 0.1f;
    } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        view[3].z += 0.1f;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        view[3].x -= 0.1f;
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        view[3].x += 0.1f;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        view[3].y -= 0.1f;
    } else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        view[3].y += 0.1f;
    }
}

void setup() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback((GLDEBUGPROC)OpenGLMessageCallback, nullptr);
    
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
}

int main(int argv, char** argc) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Virtual World", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    //OpenGL Init
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0.0f, 0.0f, WIDTH, HEIGHT);

    setup();

    //Vertex Buffer & Vertex Array & Index Buffer
    Cube cube(0.0f, 0.0f, 0.0f);
    Cube cube1(1.0f, 0.0f, 0.0f);

    //Shader
    Shader shader(vertSrc, fragSrc);

    uint u_viewProjection = glGetUniformLocation(shader.GetProgram(), "u_viewProjection");
    uint u_trasform = glGetUniformLocation(shader.GetProgram(), "u_transform");

    Mat4 projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f); // camera projection

    Mat4 cubeTransform = glm::translate(Mat4(1), glm::vec3(0, -1, -3)) * glm::rotate(Mat4(1), glm::radians(45.0f), glm::vec3(0, 1, 0));

    //Update
    while(!glfwWindowShouldClose(window)) {
        input(window);

        glClearColor(5.0f / 255.0f, 255.0f / 255.0f, 247.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Begin draw
        shader.Bind();
        Mat4 viewProjection = projection * glm::inverse(view);
        glUniformMatrix4fv(u_viewProjection, 1, GL_FALSE, glm::value_ptr(viewProjection));
        
        //Object draw
        {
            cube.BindVAO();
            glUniformMatrix4fv(u_trasform, 1, GL_FALSE, glm::value_ptr(cubeTransform));
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint), GL_UNSIGNED_INT, 0);
            cube.UnbindVAO();

            cube1.BindVAO();
            glUniformMatrix4fv(u_trasform, 1, GL_FALSE, glm::value_ptr(cubeTransform));
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint), GL_UNSIGNED_INT, 0);
            cube1.UnbindVAO();
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}