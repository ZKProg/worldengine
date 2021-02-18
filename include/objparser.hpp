#pragma once

#include "pch.h"
#include "mathhelpers.h"

class ObjParser
{
public:
    ObjParser(const std::string& objFile);
    ~ObjParser();

    bool parseFile();

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_faces;
    
    std::vector<float> m_textures;
    std::vector<unsigned int> m_texturesIndices;

    std::vector<float> m_normals;
    std::vector<float> m_sortedNormals;
    std::vector<unsigned int> m_normalIndices;

protected:

    std::ifstream m_objFile;

};