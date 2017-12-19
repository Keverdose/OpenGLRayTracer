//
//  Ray.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-18.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp


#include <stdio.h>
#include <glm/glm.hpp>

class Ray{
public:
    
    // Constructors, Destructor
    Ray();
    ~Ray();
    Ray(glm::vec3, glm::vec3);
    
    // Setters, Getters
    void setRayOrigin(glm::vec3);
    void setRayDirection(glm::vec3);
    glm::vec3 getRayOrigin();
    glm::vec3 getRayDirection();
    glm::vec3 getPoint(float);
    
    
private:
    glm::vec3 origin;       // Origin Vector
    glm::vec3 direction;    // Directional Vector (Through z)
};

#endif /* Ray_hpp */
