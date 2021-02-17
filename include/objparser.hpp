#pragma once

#include "pch.h"
#include "mathhelpers.h"

class ObjParser
{
public:
    ObjParser(const std::string& objFile);
    ~ObjParser();

    bool parseFile();
    std::vector<vec3> m_vertices;
    std::vector<vec3> m_normals;
    std::vector<unsigned int> m_faces;

protected:

    std::ifstream m_objFile;

};