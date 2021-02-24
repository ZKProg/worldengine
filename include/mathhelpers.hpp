#pragma once

#include "pch.h"

////////////////////////////////////////////////////////////////////////////////
// Vectors

template<unsigned dim>
struct vec
{
  float d[dim];

  template<typename ...T>
  vec(T&&... args) : d{ args... } {}

  float operator[] (unsigned n) const { return d[n]; }

  auto crossProduct(const vec& b) const
  {
    if constexpr (dim == 2)
    {
      return d[0]*b[1] - d[1]*b[0];
    }
    
    if constexpr (dim == 3)
    {
      vec<3> result {0.f, 0.f, 0.f};
      result[0] = d[1]*b[2] - b[1]*d[2];
      result[1] = d[2]*b[0] - b[2]*d[0];
      result[2] = d[0]*b[1] - b[0]*d[1];
      
      return result;
    }
  }

  auto dotProduct(const vec& b) const
  {
    if constexpr (dim == 2)
    {
      return d[0]*b[0] + d[1]*b[1];
    }

    if constexpr (dim == 3)
    {
      return d[0]*b[0] + d[1]*b[1] + d[2]*b[2];
    }
  }
};


