//
//  Sphere.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Object.hpp"

class Sphere : public Object{
public:
    Sphere();
    Sphere(glm::vec3 pos, float rad, glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess);
    ~Sphere();
    
    glm::vec3 getNormal(glm::vec3 point);
    float getIntersection(Ray);
    
    glm::vec3 position;
    float radius;
};

