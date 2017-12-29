//
//  Triangle.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Object.hpp"

class Triangle : public Object{
public:
    Triangle();
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess);
    ~Triangle();
    
    glm::vec3 getNormal(glm::vec3 point);
    float getIntersection(Ray);
    
    glm::vec3 v1,v2,v3;
    
private:
    glm::vec3 getTriangleNormal();
    float getDistance(); // Distance from plane to origin
};

