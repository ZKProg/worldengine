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
    std::string current;
    static u_int8_t mainCounter = 0;

    while (std::getline(m_objFile, current))
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

                std::string textureString = tmp.substr(posFirstForwardSlash + 1, posFirstForwardSlash);
                if (!textureString.empty()) m_textures.push_back(std::stof(textureString) - 1);

                std::string normalString = tmp.substr(posLastForwardSlash + 1, tmp.size());
                if (!normalString.empty()) m_normalIndices.push_back(std::stoi(normalString) - 1);

            }

        }
        // reset stringstream counter (duh)
        mainCounter = 0;

    }

    // Now that we have the normals and the indices, let's sort it out
    for (int i = 0; i < m_normalIndices.size(); i++)
    {
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i)));
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i)+1));
        m_sortedNormals.push_back(m_normals.at(m_normalIndices.at(i)+2));
    }

    // TODO remove
    std::cout << "Model loaded with " << m_vertices.size() / 3 << " vertices." << std::endl;
    std::cout << "Normal size: " << m_normals.size() / 3 << std::endl;

    return true;
}