#include<iostream>
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "utils.h"


int  main (){
    Engine Env ;
    Platform  plat ; 
    Camera cam ;
    Env.Ps() ;
    while (!glfwWindowShouldClose(Env.window)){
        Env.draw();
        cam.Move(Env.window ,Env.ps ) ;
        plat.draw(Env.ps) ;
            
        glfwSwapBuffers(Env.window);
        glfwPollEvents();
    }
}