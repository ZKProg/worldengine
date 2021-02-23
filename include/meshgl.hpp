#pragma once

#include "pch.h"
#include "objparser.hpp"
#include "shader.hpp"

class MeshGL
{
public:
  MeshGL(const std::string& objFile,
	 const std::string& vertex = "shaders/vertex.glsl",
	 const std::string& fragment = "shaders/fragment.glsl");
  MeshGL(MeshGL&& mesh);
  ~MeshGL();

  bool init(const std::string& objFile);
  void render() const;

protected:

  GLuint m_vao, m_vbo, m_vno, m_vto, m_ebo;
  std::unique_ptr<Shader> m_shaderProgram;
  std::unique_ptr<ObjParser> m_obj;

};
