//
//  FileReader.cpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#include "FileReader.hpp"

std::string FileReader::getContents(std::string path){
    std::string str;
    std::ifstream file;
    
    //ensures ifstreamobject can throw exceptions
    file.exceptions(std::ifstream::badbit);
    
    try{
        file.open(path);
        std::stringstream stream;
        
        // Read file into stream
        stream << file.rdbuf();
        
        //close file handler
        file.close();
        
        //convert stream into string
        str = stream.str();
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::FILEREADER::\\" << path << "\""<< std::endl;
    }
    return str;
}
