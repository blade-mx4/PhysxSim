#include<iostream>
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "utils.h"

Engine::Engine(){
    glfwInit(); 
    window = glfwCreateWindow(W,H,"SIM WINDOW ",NULL,NULL);

    if (window == nullptr || !window){
        std::cerr<<"Window Init "<<"\n" ;
        glfwTerminate();

    }
    glfwMakeContextCurrent(window);
    if (glewInit()!=GLEW_OK){
        std::cout<<"GLEW INIT ERROR"<<"\n" ;
        glfwTerminate();
    }
    std::cout<<"Window SuccessFull Init "<<"\n" ;
    ps = glCreateProgram() ;

}

GLuint Engine::Ps(){
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vertex_shader,NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fs,1,&frag_shader,NULL);
    glCompileShader(fs);

    glAttachShader(ps,vs);
    glAttachShader(ps,fs) ;
    glLinkProgram(ps);    
    return ps ;
}

void Engine::draw(){
    // glClearColor(.2f,.2f,.2f,1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(ps);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

// ================== Platform / Ground ================== //

