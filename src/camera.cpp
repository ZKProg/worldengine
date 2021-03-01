#include "camera.hpp"

Camera::Camera(const float& fovDegrees,
	       const float& width,
	       const float& height,
	       const float& near,
	       const float& far,
	       const z::projectionType& type)
  : m_fovDegrees(glm::radians(fovDegrees)),
    m_width(width),
    m_height(height),
    m_ratioAspect(width / height),
    m_near(near),
    m_far(far),
    m_projectionType(type)
{
  if (m_projectionType == z::PERSPECTIVE)
  {
    this->m_projection = glm::perspectiveFov(m_fovDegrees, m_width, m_height, m_near, m_far);
  }
  else
  {
    // TODO implement orthographic specifics

  }

}

Camera::~Camera()
{


}

glm::mat4 Camera::getLookAt()
{
  return this->m_lookAt;
}

glm::mat4 Camera::getPerspective()
{
  return this->m_projection;
}

// TODO implement camera translation
void Camera::translate(const glm::vec3& direction,
	       const float& distance)
{

}

// TODO implement camera rotation
void Camera::rotate(const glm::vec3& axis,
	    const float& angle)
{


}

void Camera::updateFOV(const float& fov)
{
  if (this->m_projectionType == z::PERSPECTIVE)
  {
    this->m_projection = glm::perspectiveFov(m_fovDegrees, m_width, m_height, m_near, m_far);
  }
  else
  {
    // TODO implement orthographic updating
  }
}
