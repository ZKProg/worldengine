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

  vec& operator-(const vec& v)
  {
    for (auto i = 0; i < dim; i++) { d[i] -= v[i]; }
    return *this;
  };

  vec& operator+(const vec& v)
  {
    for (auto i = 0; i < dim; i++) { d[i] += v[i]; }
    return *this;
  };

  vec& operator=(const vec& v)
  {
    for (auto i = 0; i < dim; i++) { d[i] = v[i]; }
    return *this;
  }
  
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

  // TODO review this mess
  void normalize()
  {
    float length = 0.f;
    for (auto i = 0; i < dim; i++) { length += d[i]*d[i]; }
    length = sqrt(length);
    std::cout << "Length: " << length << std::endl;
    for (auto i = 0; i < dim; i++)
    {
      d[i] /= length;
    }
  }

};

// Vector<dim>  stream overload
template<unsigned dim>
std::ostream& operator<<(std::ostream &out, vec<dim>& v)
{
  for (int i = 0; i < dim; i++) { out << v[i] << " "; }
  out << std::endl;
  return out;
}


////////////////////////////////////////////////////////////////////////////////
// Matrices

struct mat3
{
  std::vector<float> m;
  
  mat3(vec<3>&& a, vec<3>&& b, vec<3>&& c)
  {
    for (auto i = 0; i < 3; i++) m.push_back(a[i]);
    for (auto i = 0; i < 3; i++) m.push_back(b[i]);
    for (auto i = 0; i < 3; i++) m.push_back(c[i]);
  };

  float operator[] (unsigned n) const { return m.at(n); };

};

struct mat4
{
  std::vector<float> m;
  
  mat4(vec<4>&& a, vec<4>&& b, vec<4>&& c, vec<4>&& d)
  {
    for (auto i = 0; i < 4; i++) m.push_back(a[i]);
    for (auto i = 0; i < 4; i++) m.push_back(b[i]);
    for (auto i = 0; i < 4; i++) m.push_back(c[i]);
    for (auto i = 0; i < 4; i++) m.push_back(d[i]);
  };

  float operator[] (unsigned n) const { return m.at(n); };

};

////////////////////////////////////////////////////////////////////////////////
// Common types

static mat3 getId3(void)
{
  mat3 id3
  {
    { 1.f, 0.f, 0.f },
    { 0.f, 1.f, 0.f },
    { 0.f, 0.f, 1.f }
  };

  return id3;
}

static mat4 getId4(void)
{
  mat4 id4
  {
    { 1.f, 0.f, 0.f, 0.f },
    { 0.f, 1.f, 0.f, 0.f },
    { 0.f, 0.f, 1.f, 0.f },
    { 0.f, 0.f, 0.f, 1.f }
  };

  return id4;
}

////////////////////////////////////////////////////////////////////////////////
// LookAt, Perspective

static mat4 lookAt(vec<3>&& position, vec<3>&& center, vec<3>&& up)
{


  return getId4();
}

static mat4 perspectiveFOV(float& fov, float& ratio, float& near, float& far)
{

  return getId4();
}
