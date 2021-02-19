#pragma once

#include "pch.h"

// TODO create a template for the vectors 3 and 2
struct vec3
{

    vec3(float x, float y, float z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    void addVec3(const vec3& v)
    {
        m_x += v.m_x;
        m_y += v.m_y;
        m_z += v.m_z;
    }

    float m_x = 0;
    float m_y = 0;
    float m_z = 0;
};


