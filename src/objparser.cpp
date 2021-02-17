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
    static u_int8_t counter = 0;

    while (std::getline(m_objFile, current))
    {
        // VERTICES
        if (current.at(0) == 'v' && current.at(1) == ' ')
        {
            // Vertex coord
            std::istringstream ss(current);
            std::string tmp;
            vec3 vertex(0, 0, 0);

            while (ss >> tmp)
            {
                if (counter == 1) vertex.m_x = std::stof(tmp);
                if (counter == 2) vertex.m_y = std::stof(tmp);
                if (counter == 3) vertex.m_x = std::stof(tmp);
                counter++;
            }

            m_vertices.push_back(vertex);
            
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
            vec3 normal(0, 0, 0);

            while (ss >> tmp)
            {
                if (counter == 1) normal.m_x = std::stof(tmp);
                if (counter == 2) normal.m_y = std::stof(tmp);
                if (counter == 3) normal.m_z = std::stof(tmp);
                counter++;
            }

            m_normals.push_back(normal);

            //std::cout << normal.m_x << ":" << normal.m_y << ":" << normal.m_z << std::endl;
        }
        // FACES
        else if (current.at(0) == 'f' && current.at(1) == ' ')
        {
            std::istringstream ss(current);
            std::string tmp;

            while (ss >> tmp)
            {

                if (counter >= 1) {
                    // Split first face information
                    std::replace(tmp.begin(), tmp.end(), '/', ' ');
                    std::istringstream first_ss(tmp);
                    std::string first_tmp;
                    static unsigned short face_counter = 0;

                    while (first_ss >> first_tmp) 
                    {
                        if (face_counter == 0) 
                        {
                            m_faces.push_back(std::stoi(first_tmp) - 1);
                        }

                        face_counter++;
                    }

                    face_counter = 0;
                }
                counter++;
            }

        }
        // reset stringstream counter (duh)
        counter = 0;

    }

    // TODO remove
    std::cout << "Model loaded with " << m_vertices.size() << " vertices." << std::endl;
    std::cout << "Normal size: " << m_normals.size() << std::endl;

    return true;
}