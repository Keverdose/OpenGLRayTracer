#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "DataReader.hpp"

#include <glm/glm.hpp>
#include <CImg.h>
using namespace cimg_library;

#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;
int main(){
    string dataName = "scene1";
    const int aadepth = 4;
    
    clock_t time = clock();
    
    cout << "Reading data..";
    DataReader data = DataReaderParser::readSceneData("./data/"+dataName+".txt");
    
    int width = data.camera.getDimensions().x;
    int height = data.camera.getDimensions().y;
    
    CImg<unsigned char> image(width,height,1,3,0);
    
    cout << "Done (" << float(clock() - time) << " ms)" << endl;
    time = clock();
    cout << "Coloring pixels...";
    
    
    cimg_forXY(image, x, y){
        //aa hold colors to average
        float tempRed[aadepth*aadepth];
        float tempGreen[aadepth*aadepth];
        float tempBlue[aadepth*aadepth];
        
        for(int aax = 0; aax < aadepth; aax++){
            for(int aay = 0; aay < aadepth; aay++){
                int aa_index = aay*aadepth + aax;
                
                Ray ray = data.camera.getRay(x, y, aadepth, aax);
                
                //get Intersect
                Object* object = nullptr;
                float intersection_distance = 999999.0f;
                for(vector<Object*>::iterator it = data.objects.begin(); it != data.objects.end(); ++it){
                    float intersect = (*it)->getIntersection(ray);
                    if(intersect > 0 && intersect < intersection_distance){
                        object = *it;
                        intersection_distance = intersect;
                    }
                }
                
                if(object){
                    glm::vec3 intersection = ray.getRayOrigin() + ray.getRayDirection() * intersection_distance;
                    
                    glm::vec3 color = data.camera.getIntersectionColor(intersection, ray.getRayDirection(), object, data.objects, data.lights);
                    
                    //add pixel colour to arrays to average all at end
                    tempRed[aa_index] = color.x;
                    tempGreen[aa_index] = color.y;
                    tempBlue[aa_index] = color.z;
                }
                else{
                    //If there's no object
                    tempRed[aa_index] = 0;
                    tempGreen[aa_index] = 0;
                    tempBlue[aa_index] = 0;
                }
                
            }
        }
        float totalRed = 0;
        float totalGreen = 0;
        float totalBlue = 0;
        for(int i = 0; i < aadepth*aadepth; i++){
            totalRed += tempRed[i];
        }
        for(int i = 0; i < aadepth*aadepth; i++){
            totalGreen += tempGreen[i];
        }
        for(int i = 0; i < aadepth*aadepth; i++){
            totalBlue += tempBlue[i];
        }
        
        float avgRed = totalRed/(aadepth*aadepth);
        float avgGreen = totalGreen/(aadepth*aadepth);
        float avgBlue = totalBlue/(aadepth*aadepth);
        
        //set pixel Colors
        image(x,y,0) = (int)(avgRed * 255);
        image(x,y,1) = (int)(avgGreen * 255);
        image(x,y,2) = (int)(avgBlue * 255);
    }
    
    cout << "Done (" << float(clock() - time) << " ms)" << endl;
    time = clock();
    cout << "Outputting...";
    
    //determine file name
    osstringstream oss;
    if(aadepth > 1){
        oss < dataName << "aa" << aadepth << ".bmp";
    }
    else{
        oss << dataName << ".bmp";
    }
    
    // save image
    image.save_bmp(oss.str().c_str());
    
    // display image
    CImgDisplay display(image, "Render");
    cout << "done (" << float(clock() - time) << " ms)" << endl;
    while(!display.is_closed()){
        display.wait();
    }
    
    return 0;
}


//#include <iostream>
//
//// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//
////GLFW
//#include <GLFW/glfw3.h>
//
//
//// Function Declarations
//void processInput(GLFWwindow*);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//const GLint WIDTH = 800, HEIGHT = 600;
//
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//
//int main(){
//    glfwInit();
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);
//
//    int screenWidth, screenHeight;
//    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//
//    if(nullptr == window){
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glewExperimental = GL_TRUE;
//
//    if(GLEW_OK != glewInit()){
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, screenWidth, screenHeight);
//    while(!glfwWindowShouldClose(window)){
//        processInput(window);
//        glfwPollEvents();
//        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(window);
//    }
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}

