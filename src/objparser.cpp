#include "objparser.hpp"

ObjParser::ObjParser(const std::string& objFile)
{
    m_objFile.open(objFile);
    if (!m_objFile.is_open())
    {
        std::cout << "The model file " 
            << objFile.c_str() 
            << " could not be opened." 
            << std::endl;
    }

    if (!this->parseFile())
    {
        std::cout << "Problem parsing " << objFile.c_str() << std::endl;
    }
}


ObjParser::~ObjParser()
{

}

bool ObjParser::parseFile()
{
    std::cout << "Parsing file called!" << std::endl;

    std::string current;
    static u_int8_t mainCounter = 0;

    while (std::getline(m_objFile, current))
    {
        if (current.size() > 0)
        {
            // VERTICES
            if (current.at(0) == 'v' && current.at(1) == ' ')
            {
                // Vertex coord
                std::istringstream ss(current);
                std::string tmp;

                while (ss >> tmp)
                {
                    if (mainCounter > 0) m_vertices.push_back(std::stof(tmp));
                    mainCounter++;
                }
                
            }
            // TEXTURE COORD
            else if (current.at(0) == 'v' && current.at(1) == 't')
            {
                // Texture coord
                std::istringstream ss(current);
                std::string tmp;

                while (ss >> tmp)
                {
                    if (mainCounter > 0)
                    {
                        m_textures.push_back(std::stof(tmp));
                    }

                    mainCounter++;
                }
            }
            // NORMALS
            else if (current.at(0) == 'v' && current.at(1) == 'n')
            {
                // Normal coord
                std::istringstream ss(current);
                std::string tmp;

                while (ss >> tmp)
                {
                    if (mainCounter > 0)
                    {
                        m_normals.push_back(std::stof(tmp));
                    }

                    mainCounter++;
                }

            }
            // FACES
            else if (current.at(0) == 'f' && current.at(1) == ' ')
            {
                std::istringstream ss(current.substr(1, current.size()));
                std::string tmp;

                while (ss >> tmp)
                {

                    int posFirstForwardSlash = tmp.find_first_of('/');
                    int posLastForwardSlash = tmp.find_last_of('/');

                    // All the indices values are minused by 1 to match the OpenGL array indexing
                    std::string indexString = tmp.substr(0, posFirstForwardSlash);
                    if (!indexString.empty()) m_faces.push_back(std::stoi(indexString) - 1);

                    std::string textureString = tmp.substr(posFirstForwardSlash + 1, posFirstForwardSlash - 1);
                    if (!textureString.empty()) m_texturesIndices.push_back(std::stoi(textureString) - 1);

                    std::string normalString = tmp.substr(posLastForwardSlash + 1, tmp.size());
                    if (!normalString.empty()) m_normalIndices.push_back(std::stoi(normalString) - 1);

                }

            }
            // reset stringstream counter (duh)
            mainCounter = 0;
        }

    }

    // Now that we have the indices, let's sort things out
    for (int i = 0; i < m_faces.size(); i++)
    {
        // first the vertices
        m_sortedVertices.push_back(m_vertices.at(m_faces.at(i) * 3));
        m_sortedVertices.push_back(m_vertices.at(m_faces.at(i) * 3 + 1));
        m_sortedVertices.push_back(m_vertices.at(m_faces.at(i) * 3 + 2));
    }

    for (int i = 0; i < m_normalIndices.size(); i++)
    {
        // then the normals
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i) * 3));
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i) * 3 + 1));
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i) * 3 + 2));
    }


    // TODO remove
    std::cout << "Model loaded with " << m_vertices.size() / 3 << " vertices." << std::endl;
    std::cout << "Normal size: " << m_normals.size() / 3 << std::endl;

    return true;
}