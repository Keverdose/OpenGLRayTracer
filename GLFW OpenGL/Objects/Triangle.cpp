//
//  Triangle.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Triangle.hpp"

// Constructors
Triangle::Triangle(){}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 color, glm::vec3 diffuse_color, glm::vec3 specular_color, float shininess) : v1(v1),v2(v2),v3(v3), Object(color,diffuse_color,specular_color,shininess){}

Triangle::~Triangle(){}

float Triangle::getIntersection(Ray ray){
    glm::vec3 normal = getTriangleNormal();
    float distance = getDistance();
    
    float a = glm::dot(ray.getRayDirection(), normal);
    
    if(a == 0) // The ray is parallel to the plane, will never intersect
        return -1;
    else{
        float b = glm::dot(normal, ray.getRayOrigin() + -(normal*distance));
        
        float Qx = (ray.getRayDirection() * distance).x + ray.getRayOrigin().x;
        float Qy = (ray.getRayDirection() * distance).y + ray.getRayOrigin().y;
        float Qz = (ray.getRayDirection() * distance).z + ray.getRayOrigin().z;
        
        glm::vec3 Q(Qx,Qy,Qz);
        
        // CAxQA, n >= 0
        glm::vec3 CA(v3.x - v1.x, v3.y - v1.y, v3.z -v1.z);
        glm::vec3 QA(Q.x - v1.x, Q.y - v1.y, Q.z -v1.z);
        float test1 = glm::dot(glm::cross(CA, QA), normal);
        
        // BCxQC, n >= 0
        glm::vec3 BC(v2.x - v3.x, v2.y - v3.y, v2.z -v3.z);
        glm::vec3 QC(Q.x - v3.x, Q.y - v3.y, Q.z -v3.z);
        float test2 = glm::dot(glm::cross(BC, QC), normal);
        
        // ABxQB
        glm::vec3 AB(v1.x - v2.x, v1.y - v2.y, v1.z -v2.z);
        glm::vec3 QB(Q.x - v2.x, Q.y - v2.y, Q.z -v2.z);
        float test3 = glm::dot(glm::cross(AB, QB), normal);
        
        // If intersection inside of triangle
        if(test1 >= 0 && test2 >= 0 && test3 >= 0){ return -b/a;}
        else{ return -1;}
    }
}


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
