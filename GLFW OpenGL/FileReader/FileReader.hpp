//
//  FileReader.hpp
//  GLFW OpenGL
//
//  Created by Kevin Ye on 2017-12-29.
//  Copyright © 2017 Kevin Ye. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileReader
{
public:
    static std::string getContents(std::string path);
};
