#include "core.hpp"
#include "shader.hpp"

#include "noise.hpp"

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
        Color = u_Color * texture(u_Texture, v_TexCoord); // vec4(v_TexCoord, 0, 1);
    }
)";

Mat4 view = Mat4(1);

void keyboard(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        view[3].z -= 0.2f;
    } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        view[3].z += 0.2f;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        view[3].x -= 0.2f;
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        view[3].x += 0.2f;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        view[3].y -= 0.2f;
    } else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        view[3].y += 0.2f;
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        view = glm::rotate(view, glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        view = glm::rotate(view, glm::radians(-2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        view = glm::rotate(view, glm::radians(-2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        view = glm::rotate(view, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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

    srand(time(NULL));

    //Vertex Buffer & Vertex Array & Index Buffer
    std::vector<Cube> cubes;
    for(int x = 0; x < 32; x++) {
        for(int z = 0; z < 32; z++) {
            //float y = rand() % 5;
            cubes.emplace_back(x, perlin::noise((float)(rand() % 9) / 10, (float)(rand() % 9) / 10, (float)(rand() % 9) / 10), z);
        }
    }

    //Shader
    Texture test("test.jpg");

    Shader shader(vertSrc, fragSrc);

    uint u_viewProjection = glGetUniformLocation(shader.GetProgram(), "u_viewProjection");
    uint u_transform = glGetUniformLocation(shader.GetProgram(), "u_transform");

    Mat4 projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f); // camera projection

    view[3].x = 14.6f;
    view[3].y = 7.7f;
    view[3].z = 38.1f;

    //Update
    while(!glfwWindowShouldClose(window)) {
        keyboard(window);

        glClearColor(5.0f / 255.0f, 255.0f / 255.0f, 247.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Begin draw
        test.Bind();
        shader.Bind();
        Mat4 viewProjection = projection * glm::inverse(view);
        glUniformMatrix4fv(u_viewProjection, 1, GL_FALSE, glm::value_ptr(viewProjection));
        
        //Object draw
        {
            for(auto& cube : cubes) {
                cube.render(u_transform);
            }
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}