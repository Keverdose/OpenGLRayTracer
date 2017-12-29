//
//  Sphere.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Sphere.hpp"

Sphere::Sphere(){}

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess): position(pos), radius(rad) ,Object(color, diffuse_color, specular_color, shininess){}

Sphere::~Sphere(){}

// Intersection function for Sphere and ray
float Sphere::getIntersection(Ray ray){
    glm::vec3 diff = ray.getRayOrigin() - position;
    
    float b = 2 * glm::dot(diff, ray.getRayDirection());
    float c = glm::dot(diff, diff) - radius * radius;
    float disc = b*b - 4*c;
    
    // If no intersection
    if(disc < 0)
        return -1;
    
    else{
        float root1 = (-b - glm::sqrt(disc)) / 2.0f;
        if(root1 > 0)
            return root1;
        else
            return (-b + glm::sqrt(disc)) / 2.0f;
    }
}

glm::vec3 Sphere::getNormal(glm::vec3 point){
    return glm::normalize(point + -position);
}
