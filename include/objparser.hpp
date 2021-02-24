#pragma once

#include "pch.h"
#include "mathhelpers.hpp"

class ObjParser
{
public:
  ObjParser(const std::string& objFile);
  ~ObjParser();

  bool parseFile();

  std::vector<float> m_vertices;
  std::vector<float> m_sortedVertices;
    
  std::vector<float> m_textures;
  std::vector<unsigned int> m_texturesIndices;
  std::vector<float> m_sortedTextures;

  std::vector<float> m_normals;
  std::vector<unsigned int> m_normalIndices;
  std::vector<float> m_sortedNormals;

  std::vector<unsigned int> m_faces;
  std::vector<unsigned int> m_sortedFaces;

protected:

  std::string m_fileName;
  std::ifstream m_objFile;

};
