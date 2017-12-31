//
//  Light.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Light.hpp"

Light::Light(){}

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color){}

Light::~Light(){}
