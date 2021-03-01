#pragma once

#include "pch.h"

using namespace tinyxml2;

namespace z {
  enum projectionType {
    PERSPECTIVE,
    ORTHOGRAPHIC
  };
}

class Camera
{
public:
  explicit Camera(const float& fovDegrees,
		  const float& width,
		  const float& height,
		  const float& near,
		  const float& far,
		  const z::projectionType& type = z::PERSPECTIVE);
  virtual ~Camera();
  
  glm::mat4 getLookAt();
  glm::mat4 getPerspective();

  void translate(const glm::vec3& direction,
		 const float& distance);
  void rotate(const glm::vec3& axis,
	      const float& angle);

  void updateFOV(const float& fov);

protected:

  float m_fovDegrees, m_width, m_height, m_ratioAspect, m_near, m_far;
  
  glm::vec3 m_cameraPosition;
  glm::vec3 m_cameraCenter;
  glm::vec3 m_cameraUp;

  glm::mat4 m_lookAt;
  glm::mat4 m_projection;
  z::projectionType m_projectionType;
};

