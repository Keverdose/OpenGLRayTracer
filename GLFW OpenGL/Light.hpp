//
//  Light.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <glm/glm.hpp>

class Light{
public:
    Light();
    Light(glm::vec3 position, glm::vec3 color);
    ~Light();
    
    glm::vec3 position;
    glm::vec3 color;
};

