//
//  Object.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Ray.hpp"

class Object{
public:
    Object();
    Object(glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess);
    ~Object();
    
    virtual glm::vec3 getNormal(glm::vec3) = 0;
    virtual float getIntersection(Ray) = 0;
    
    glm::vec3 color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float shininess;
};
