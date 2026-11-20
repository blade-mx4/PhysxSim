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
        uniform model , proj , view ;
        void main (){
        
            gl_Position = vec4(Pos,1.0f) ;
        }
    
    )" ;

    const char *frag_shader = R"(
        #version 330 core 
        out vec4 Color ;

        void main (){
            Color = vec4(0.05f, 0.05f, 0.05f, 0.7f);
        }
    
    )" ;
    
    Engine() ;

    GLuint Ps() ; // compilin of all shaders from program shader to vertex and frag shader 

    void draw() ;

} ;

// struct Platform {
//     Platform() ;
//     void draw() ;
// } Ground ;

// struct Camera {

// } Cam ;


