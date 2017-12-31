//
//  Plane.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Object.hpp"

class Plane : public Object{
public:
    Plane();
    Plane(glm::vec3 normal, glm::vec3 position, glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess);
    ~Plane();
    
    glm::vec3 getNormal(glm::vec3 point);
    float getIntersection(Ray);
    
    glm::vec3 normal;
    glm::vec3 position;
};
