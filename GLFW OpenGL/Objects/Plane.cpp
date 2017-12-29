//
//  Plane.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Plane.hpp"

Plane::Plane(){}

Plane::Plane(glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess) : Object(color, diffuse_color, specular_color,shininess){
    this->normal = glm::normalize(normal);
    this->position = position;
}

Plane::~Plane(){}

float Plane::getIntersection(Ray ray){
    float a = glm::dot(ray.getRayDirection(),normal);
    if(a == 0)
        return -1;
    else{
        float b = glm::dot(normal, ray.getRayDirection() + -(normal*(position -ray.getRayDirection())));
        return -b/a;
    }
}
glm::vec3 Plane::getNormal(glm::vec3 point){
    return normal;
}
