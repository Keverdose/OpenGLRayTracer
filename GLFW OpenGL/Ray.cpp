//
//  Ray.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-18.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Ray.hpp"

Ray::Ray() {
    origin = glm::vec3(0,0,0);
    direction = glm::vec3(0,0,1);
}

Ray::~Ray(){
}

Ray::Ray(glm::vec3 passedOrigin, glm::vec3 passedDirection){
    origin = passedOrigin;
    direction = passedDirection;
}

void Ray::setRayOrigin(glm::vec3 a){
    this->origin = a;
}

void Ray::setRayDirection(glm::vec3 a){
    this->direction = a;
}

glm::vec3 Ray::getRayOrigin(){
    return this->origin;
}

glm::vec3 Ray::getRayDirection(){
    return this->direction;
}

glm::vec3 Ray::getPoint(float distance){
    return this->origin + (this->direction*distance);
}



