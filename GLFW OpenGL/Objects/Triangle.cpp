//
//  Triangle.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Triangle.hpp"

glm::vec3 Triangle::getTriangleNormal(){
    glm::vec3 CA(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
    glm::vec3 BA(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
    return glm::normalize(glm::cross(CA,BA));
}

float Triangle::getDistance(){
    glm::vec3 normal = getTriangleNormal();
    return glm::dot(normal, v1);
}

glm::vec3 Triangle::getNormal(glm::vec3 point){
    return getTriangleNormal();
}
