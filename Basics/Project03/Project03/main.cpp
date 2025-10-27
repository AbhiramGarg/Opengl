#include <iostream>
#include <SDL3\SDL.h>
#include <glew.h>
#include <vector>
#include <fstream>
#include <string>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

bool quit = false;

GLuint gVertexArrayObject = 0;

GLuint gVertexBufferObject = 0;

GLuint gGraphicsPipelineShaderProgram = 0;

//const std::string gVertexShaderSource = "#version 460 core\n""in vec4 Position;\n""void main()\n""{\n""gl_Position = vec4(Position.x,Position.y,Position.z,Position.w);\n""}\n";
//const std::string gFragmentShaderSource = "#version 460 core\n""out vec4 color;\n""void main()\n""{\n""color = vec4(1.0f,0.5f,0.0f,1.0f);\n""}\n";

std::string LoadShaderAsString(const std::string& filename) {
    std::string result = "";
    std::string line = "";
    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, line))
        {
            result += line + '\n';
        }
        myFile.close();
    }
    else {
        std::cerr << "Error: Could not open shader file " << filename << std::endl;
    }
    return result;
}

GLuint CompileShader(GLuint type, const std::string& source) {
    GLuint shaderObj;
    if(type == GL_VERTEX_SHADER)
    {
        shaderObj = glCreateShader(GL_VERTEX_SHADER);
    }
    else if(type == GL_FRAGMENT_SHADER)
    {
        shaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    const char* src = source.c_str();
    glShaderSource(shaderObj, 1, &src, nullptr);
    glCompileShader(shaderObj);

    return shaderObj;
}

GLuint CreateShaderProgram(const std::string& vertexshadersource, const std::string& fragmentshadersource) 
{
    GLuint programObj = glCreateProgram();

    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);

    glAttachShader(programObj, myVertexShader);
    glAttachShader(programObj, myFragmentShader);
    glLinkProgram(programObj);

    glValidateProgram(programObj);

    return programObj;


}

void CreateGraphicsPipeline() 
{
    std::string vertexShaderSource = LoadShaderAsString("./shaders/vert.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("./shaders/frag.glsl");
    
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void GetopenGLversionInfo() {
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


void InitializeProgram() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != true) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(
        "Empty Window",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL // This flag is crucial for OpenGL
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Now, create the OpenGL context and make it current
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        std::cerr << "Failed to create OpenGL context! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // Now that the context is created and GLEW is initialized, get the OpenGL version info
    GetopenGLversionInfo();

}


void VertexSpecification() {
    
    const std::vector<GLfloat> vertexPosition{
    -0.8f,-0.8f,0.0f,
    0.8f,-0.8f, 0.0f,
    0.0f, 0.8f, 0.0f
    };

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, 
        vertexPosition.size() * sizeof(GLuint), 
        vertexPosition.data(), 
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

}

void Input() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_EVENT_QUIT) {
            quit = true;
        }
    }

};
void PreDraw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glUseProgram(gGraphicsPipelineShaderProgram);
};
void Draw() {

    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);

};


void MainLoop() {
    // Main event loop
    while (!quit)
    {
        Input();
        
        PreDraw();

        Draw();

        SDL_GL_SwapWindow(window);
    }

}

void CleanUp() {

    // Clean up
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int main(int argc, char* argv[])
{
    


    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();

    MainLoop();

    CleanUp();

    return 0;
}