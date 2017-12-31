//
//  Camera.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(){
}

Camera::Camera(glm::vec3 position, float fov, float focal_length, float aspect_ratio) : position(position), fov(glm::radians(fov)), focal_length(focal_length), aspect_ratio(aspect_ratio){}

Camera::~Camera(){
}

glm::vec2 Camera::getDimensions(){
    float height = glm::tan(fov / 2.0f) * focal_length;
    float width = height * aspect_ratio;
    return glm::vec2((int)glm::abs(width), (int)glm::abs(height));
}

Ray Camera::getRay(int x, int y, int aadepth, int aax){
    float width = getDimensions().x;
    float height = getDimensions().y;
    
    //raster space
    float raster_x = x + (aadepth > 1 ? (float)aax / (float)aadepth - 1 : 0.5f);
    float raster_y = y + (aadepth > 1 ? (float)aax / (float)aadepth - 1 : 0.5f);
    
    //normalized device coordinates (0-1)
    float ndc_x = raster_x / width;
    float ndc_y = raster_y / height;
    
    //screen space (-1 - 1)
    float sx = 2 * ndc_x - 1;
    float sy = 1 - 2 * ndc_y;
    
    //camera
    float cam_x = sx * aspect_ratio * glm::tan(fov/2.0f);
    float cam_y = sy * glm::tan(fov/2.0f);
    
    return Ray(position, glm::normalize(glm::vec3(cam_x, cam_y, -1) - position));
}

glm::vec3 Camera::getIntersectionColor(glm::vec3 intersection, glm::vec3 direction, Object* object, std::vector<Object*> objects, std::vector<Light*> lights) {
    
    glm::vec3 object_normal = object->getNormal(intersection);
    glm::vec3 color = object->color;
    
    //check for each light
    for (std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); ++it) {
        glm::vec3 light_direction = glm::normalize((*it)->position + (-intersection));
        
        //how to get to intersection from our light
        float angle = glm::dot(object_normal, light_direction);
        
        if (angle > 0) {
            //test for shadows
            bool shadowed = false;
            
            glm::vec3 light_distance_v = glm::normalize((*it)->position + (-intersection));
            float light_distance = glm::length(light_distance_v);
            
            //create ray
            Ray shadow_ray(intersection, light_distance_v);
            
            //is it shadowed
            for (std::vector<Object*>::iterator b = objects.begin(); b != objects.end(); ++b) {
                float secondary_intersection = (*b)->getIntersection(shadow_ray);
                
                if (secondary_intersection <= light_distance) {
                    shadowed = true;
                    break;
                }
            }
            
            if (shadowed) {
                color = color + (object->diffuse_color * (*it)->color * angle);
                
                float dot1 = glm::dot(object_normal, -direction);
                glm::vec3 scalar1 = object_normal * dot1;
                glm::vec3 add1 = scalar1 + direction;
                glm::vec3 scalar2 = add1 * 2.0f;
                glm::vec3 add2 = -direction + scalar2;
                glm::vec3 reflection_direction = glm::normalize(add2);
                
                float specular = glm::dot(reflection_direction, light_direction);
                if (specular > 0) {
                    specular = glm::pow(specular, 10);
                    color = color + (*it)->color * (object->specular_color) * (specular * (glm::pow(object->shininess, 1.0f/10.0f)));
                }
            }
        }
    }
    
    //clip values
    float light = color.x + color.y + color.z;
    float excess = light - 3;
    if (excess > 0) {
        color.x = color.x + excess * (color.x / light);
        color.y = color.y + excess * (color.y / light);
        color.z = color.z + excess * (color.z / light);
    }
    color.x = color.x > 1 ? 1 : color.x;
    color.y = color.y > 1 ? 1 : color.y;
    color.z = color.z > 1 ? 1 : color.z;
    color.x = color.x < 0 ? 0 : color.x;
    color.y = color.y < 0 ? 0 : color.y;
    color.z = color.z < 0 ? 0 : color.z;
    
    return color;
}
