//
//  DataReader.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>

#include "FileReader.hpp"
#include "Object.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Light.hpp"
#include "Camera.hpp"

struct DataReader{
    Camera camera;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
};

class DataReaderParser{
public:
    // Reads scene data from a file
    static DataReader readSceneData(const std::string fileName);
    
private:
    static glm::vec3 readVec3(std::istringstream& stream);
    static Camera readCamera(std::istringstream& stream);
    static Plane* readPlane(std::istringstream& stream);
    static Sphere* readSphere(std::istringstream& stream);
    static Light* readLight(std::istringstream& stream);
    static Triangle* readTriangle(std::istringstream& stream);
};
