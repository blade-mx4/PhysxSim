#pragma  once 

#include<iostream>
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

struct Engine {
    const GLuint W = 640 ; 
    const GLuint H =  480 ; 
    GLFWwindow *window = nullptr ;
    GLuint ps ;
    const char *vertex_shader = R"(
        #version 330 core 
        layout(location=0) in vec3 Pos ;
        uniform mat4 model , proj , view ;
        void main (){
        
            gl_Position = proj*view*model*vec4(Pos,1.0f) ;
        }
    
    )" ;

    const char *frag_shader = R"(
        #version 330 core 
        out vec4 Color ;
        uniform vec4 grid_color ; // using uniform wont kill me 
        void main (){
            Color = grid_color ;
        }
    
    )" ;
    
    Engine() ;

    GLuint Ps() ; // compilin of all shaders from program shader to vertex and frag shader 

    void draw() ;
    
} ;

struct Platform {
    GLuint VAO, VBO;
    int vertexCount;
    GLuint lineVAO, lineVBO;
    int lineVertexCount;

    Platform() ;
    void draw(GLuint ps) ;
} ;


struct Camera {
    // Everythin with movement  
    glm::vec3 camPos = glm::vec3(.0f,5.0f,5.0f) ;
    glm::vec3 camFront = glm::vec3(.0f,.0f,-3.0f);
    glm::vec3 camUp = glm::vec3(.0f,1.f,0.0f);
    
    glm::mat4 view = glm::mat4(1.0f);

    GLfloat deltaTime = 0.0f ;
    GLfloat lastFrame = 0.0f ;

    bool Mouse = true ;
    float yaw = -90.0f ;
    float pitch = 0.f ;
    float lastX = 800.0f / 2.0 ;
    float lastY = 600.0f /2.0f ;
    float fov = 75.0f ; 

    
    void Move(GLFWwindow *window , GLuint ps ) ;
} ;

