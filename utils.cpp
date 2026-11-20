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
    glViewport(0,0,W,H) ;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    std::cout<<"Window SuccessFull Init "<<"\n" ;
    ps = glCreateProgram() ;

}

GLuint Engine::Ps(){
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vertex_shader,NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,&frag_shader,NULL);
    glCompileShader(fs);

    glAttachShader(ps,vs);
    glAttachShader(ps,fs) ;
    glLinkProgram(ps);    
    return ps ;
}

void Engine::draw(){
    // glClearColor(.2f,.2f,.2f,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram(ps);
    glm::mat4 proj = glm::mat4(1.0f) ;
    proj = glm::perspective(glm::radians(75.0f) ,static_cast<float>(640)  / static_cast<float>(480), 0.1f,100.0f);
    glUniformMatrix4fv(glGetUniformLocation(ps,"proj"),1,GL_FALSE,glm::value_ptr(proj)) ;
}

// ================== Platform / Ground ================== //


Platform::Platform() {
        float size = 20.0f ;
        int divisions = 40 ;
        float half = size / 2.0f;
        std::vector<float> vertices = {
            -half, 0, -half,   half, 0, -half,   half, 0, half,
            -half, 0, -half,   half, 0, half,    -half, 0, half,
        };
        // engine.createVAO(VAO, VBO, vertices.data(), vertices.size());
        vertexCount =vertices.size() / 3 ;
        glGenBuffers(1,&VBO);
        glGenVertexArrays(1,&VAO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO) ;
        glBufferData(GL_ARRAY_BUFFER ,vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        std::vector<float> lines;
        float step = size / divisions;
        for (int i = 0; i <= divisions; ++i) {
            float x = -half + i * step, z = -half + i * step;
            lines.insert(lines.end(), {x, 0, -half, x, 0, half});
            lines.insert(lines.end(), {-half, 0, z, half, 0, z});
        }
        lineVertexCount = lines.size() / 3;
        // engine.createVAO(lineVAO, lineVBO, lines.data(), lines.size());
        glGenBuffers(1,&lineVBO);
        glGenVertexArrays(1,&lineVAO);

        glBindVertexArray(lineVAO);

        glBindBuffer(GL_ARRAY_BUFFER ,lineVBO);
        glBufferData(GL_ARRAY_BUFFER,lines.size()*sizeof(float),lines.data(),GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0); 

}

void Platform::draw(GLuint ps){
    glm::mat4 model = glm::mat4(1.0f) ;
    glUniformMatrix4fv(glGetUniformLocation(ps,"model"),1,GL_FALSE,glm::value_ptr(model)) ;
    glDepthMask(GL_FALSE);

    glUniform4f(glGetUniformLocation(ps,"grid_color"),0.05f, 0.05f, 0.05f, 0.7f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glUniform4f(glGetUniformLocation(ps,"grid_color"), 1.0f, 1.0f, 1.0f, 0.15f);
    glBindVertexArray(lineVAO);
    glDrawArrays(GL_LINES, 0, lineVertexCount);

    glDepthMask(GL_TRUE);
}


void Camera::Move(GLFWwindow *window ,GLuint ps ){
        GLfloat currentTime = static_cast<float>(glfwGetTime()) ;
        deltaTime = currentTime - lastFrame ;
        lastFrame = currentTime ;
        GLfloat camSpeed = static_cast<float>(2.5*deltaTime);
    
        if (glfwGetKey(window ,GLFW_KEY_ESCAPE) == GLFW_PRESS){glfwSetWindowShouldClose(window,true);} 
        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){camPos += camSpeed * camFront ; } 
        if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){camPos -= camSpeed * camFront ; }
        if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){ camPos-=glm::normalize(glm::cross(camFront,camUp))*camSpeed ;}
        if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){ camPos+=glm::normalize(glm::cross(camFront,camUp))*camSpeed ;}
        view = glm::lookAt(camPos,camPos+camFront,camUp);
        glUniformMatrix4fv(glGetUniformLocation(ps,"view"),1,GL_FALSE,glm::value_ptr(view));
}