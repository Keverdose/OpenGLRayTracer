//
//  Object.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Object.hpp"

Object::Object(){}

Object::Object(glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess){
    this->color = color;
    this->diffuse_color = diffuse_color;
    this->specular_color = specular_color;
    this->shininess = shininess;
}

Object::~Object(){}
