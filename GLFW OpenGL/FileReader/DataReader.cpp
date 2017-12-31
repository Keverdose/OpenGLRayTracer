//
//  DataReader.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-30.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "DataReader.hpp"

DataReader DataReaderParser::readSceneData(const std::string fileName) {
    std::string contents = FileReader::getContents(fileName);
    
    std::istringstream stream(contents);
    DataReader data;
    
    int count;
    stream >> count;
    
    std::string type;
    for (int i = 0; i < count; i++) {
        stream >> type;
        
        if (type == "camera") {
            data.camera = readCamera(stream);
        }
        else if (type == "plane") {
            data.objects.push_back(readPlane(stream));
        }
        else if (type == "sphere") {
            data.objects.push_back(readSphere(stream));
        }
        else if (type == "light") {
            data.lights.push_back(readLight(stream));
        }
        else if (type == "triangle") {
            data.objects.push_back(readTriangle(stream));
        }
    }
    
    return data;
}

glm::vec3 DataReaderParser::readVec3(std::istringstream& stream) {
    float x, y, z;
    stream >> x >> y >> z;
    return glm::vec3(x, y, z);
}

Camera DataReaderParser::readCamera(std::istringstream& stream){
    std::string skip;
    
    stream >> skip;
    glm::vec3 position = readVec3(stream);
    
    float fov, f, a;
    
    stream >> skip >> fov;
    stream >> skip >> f;
    stream >> skip >> a;
    
    return Camera(position, fov, f, a);
}

Plane* DataReaderParser::readPlane(std::istringstream& stream){
    std::string skip;
    
    stream >> skip;
    glm::vec3 nor = readVec3(stream);
    stream >> skip;
    glm::vec3 pos = readVec3(stream);
    
    stream >> skip;
    glm::vec3 amb = readVec3(stream);
    stream >> skip;
    glm::vec3 dif = readVec3(stream);
    stream >> skip;
    glm::vec3 spe = readVec3(stream);
    float shi;
    stream >> skip >> shi;
    
    return new Plane(nor, pos, amb, dif, spe, shi);
}

Sphere* DataReaderParser::readSphere(std::istringstream& stream) {
    std::string skip;
    
    stream >> skip;
    glm::vec3 pos = readVec3(stream);
    float rad;
    stream >> skip >> rad;
    
    stream >> skip;
    glm::vec3 amb = readVec3(stream);
    stream >> skip;
    glm::vec3 dif = readVec3(stream);
    stream >> skip;
    glm::vec3 spe = readVec3(stream);
    float shi;
    stream >> skip >> shi;
    
    return new Sphere(pos, rad, amb, dif, spe, shi);
}

Light* DataReaderParser::readLight(std::istringstream& stream) {
    std::string skip;
    
    stream >> skip;
    glm::vec3 pos = readVec3(stream);
    stream >> skip;
    glm::vec3 col = readVec3(stream);
    
    return new Light(pos, col);
}

Triangle* DataReaderParser::readTriangle(std::istringstream& stream) {
    std::string skip;
    
    stream >> skip;
    glm::vec3 v1 = readVec3(stream);
    stream >> skip;
    glm::vec3 v2 = readVec3(stream);
    stream >> skip;
    glm::vec3 v3 = readVec3(stream);
    
    stream >> skip;
    glm::vec3 amb = readVec3(stream);
    stream >> skip;
    glm::vec3 dif = readVec3(stream);
    stream >> skip;
    glm::vec3 spe = readVec3(stream);
    float shi;
    stream >> skip >> shi;
    
    return new Triangle(v1, v2, v3, amb, dif, spe, shi);
}
