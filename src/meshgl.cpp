#include "meshgl.hpp"

MeshGL::MeshGL(const std::string &objFile,
               const std::string &vertex,
               const std::string &fragment) : m_shaderProgram(nullptr)
{
  m_shaderProgram = std::unique_ptr<Shader>(new Shader(vertex.c_str(), fragment.c_str()));
  m_obj = std::unique_ptr<ObjParser>(new ObjParser(objFile));

  if (!this->init(objFile))
  {
    std::cout << "Problem initializing " << objFile << std::endl;
  }

  // model matrix init to identity
  m_model = glm::mat4(1.f);
}

MeshGL::MeshGL(MeshGL &&mesh) : m_vao(mesh.m_vao),
                                m_vbo(mesh.m_vbo),
                                m_vno(mesh.m_vno),
                                m_vto(mesh.m_vto),
                                m_ebo(mesh.m_ebo),
                                m_shaderProgram(std::move(mesh.m_shaderProgram)),
                                m_obj(std::move(mesh.m_obj)),
				m_model(mesh.m_model)
{
  // Move cstr
  std::cout << "Move constructor called." << std::endl;
}

MeshGL::~MeshGL()
{
  //delete m_obj;
}

bool MeshGL::init(const std::string &objFile)
{
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);
  glGenBuffers(1, &m_vno);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * m_obj->m_sortedVertices.size(),
               m_obj->m_sortedVertices.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, m_vno);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * m_obj->m_sortedNormals.size(),
               m_obj->m_sortedNormals.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * m_obj->m_sortedFaces.size(),
               m_obj->m_sortedFaces.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return true;
}

void MeshGL::render(const glm::mat4& VP) const
{
  glm::mat4 MVP = VP * m_model;
  GLint programId = m_shaderProgram->getProgramID();

  // Start using the shader program
  glUseProgram(programId);

  GLint mvpHook = glGetUniformLocation(programId, "MVP");
  glUniformMatrix4fv(mvpHook, 1, GL_FALSE, &MVP[0][0]);
    
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vno);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glDrawElements(GL_TRIANGLES, m_obj->m_faces.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glUseProgram(0);
}
