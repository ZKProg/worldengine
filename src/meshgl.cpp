#include "meshgl.hpp"

MeshGL::MeshGL(const std::string& objFile,
    const std::string& vertex,
    const std::string& fragment) :
    m_shaderProgram(nullptr),
    m_obj(nullptr),
    g_vertex_buffer_data(nullptr),
    elements(nullptr)
{
    m_shaderProgram = new Shader(vertex.c_str(), fragment.c_str());
    m_obj = new ObjParser(objFile);

    g_vertex_buffer_data = new GLfloat[9];
    elements = new GLuint[3];

    g_vertex_buffer_data[0] = -0.5f; g_vertex_buffer_data[1] = -0.5f; g_vertex_buffer_data[2] = 0.0f;
    g_vertex_buffer_data[3] =  0.5f; g_vertex_buffer_data[4] = -0.5f; g_vertex_buffer_data[5] = 0.0f;
    g_vertex_buffer_data[6] =  0.0f; g_vertex_buffer_data[7] =  0.5f; g_vertex_buffer_data[8] = 0.0f;

    elements[0] = 0; elements[1] = 1; elements[2] = 2;

    if (!this->init(objFile))
    {
        std::cout << "Problem initializing " << objFile << std::endl; 
    }

}

//MeshGL::MeshGL(MeshGL&& mesh) :
//    m_vao(mesh.m_vao),
//    m_vbo(mesh.m_vbo),
//    m_vno(mesh.m_vno),
//    m_vto(mesh.m_vto),
//    m_shaderProgram(std::move(mesh.m_shaderProgram)),
//    m_obj(mesh.m_obj),
//    g_vertex_buffer_data(mesh.g_vertex_buffer_data),
//    elements(mesh.elements)
//{
//    // Move cstr
//    std::cout << "Move constructor called." << std::endl;
//    
//}

MeshGL::~MeshGL()
{
    //delete m_obj;
}

bool MeshGL::init(const std::string& objFile)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glGenBuffers(1, &m_vno);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(float) * m_obj->m_vertices.size() * 3,
        m_obj->m_vertices.data(),
        GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vno);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(float) * m_obj->m_normals.size() * 3,
        m_obj->m_normals.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * m_obj->m_faces.size(),
        m_obj->m_faces.data(),
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return true;
}

void MeshGL::render() const
{

    glUseProgram(m_shaderProgram->getProgramID());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vno);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glDrawElements(GL_TRIANGLES, m_obj->m_faces.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}