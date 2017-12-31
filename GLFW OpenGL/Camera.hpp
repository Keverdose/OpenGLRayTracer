//
//  Camera.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>

#include "Ray.hpp"
#include "Object.hpp"
#include "Light.hpp"

struct Camera{
public:
    Camera();
    Camera(glm::vec3 position, float fov, float focal_length, float aspect_ratio);
    ~Camera();
    
    glm::vec2 getDimensions();
    Ray getRay(int x, int y, int aadepth = 1, int aax =0);
    
    glm::vec3 getIntersectionColor(glm::vec3 intersection, glm::vec3 direction, Object* object, std::vector<Object*> objects, std::vector<Light*> lights);
    glm::vec3 position;
    float fov;
    float focal_length;
    float aspect_ratio;
};



