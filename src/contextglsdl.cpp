#include "contextglsdl.hpp"

ContextGLSDL::ContextGLSDL(std::unique_ptr<SettingsMixin> mixin) : m_mainWindow(nullptr),
                                                                   m_mixin(std::move(mixin))
{
  //mixin.reset();

  if (this->initGLSDL())
  {
  }
  else
  {
    // Something went wrong
  }

  // Linear algebra (camera & projection)
  // TODO replace width and height by mixin values
  m_perspective = glm::perspectiveFov(glm::radians(70.f), 800.f, 600.f, 0.1f, 1000.f);

  m_cameraPosition = glm::vec3(1.f, 1.f, 1.f);
  m_cameraCenter = glm::vec3(0.f, 0.f, 0.f);
  m_cameraUp = glm::vec3(0.f, 1.f, 0.f);

  m_lookAt = glm::lookAt(m_cameraPosition, m_cameraCenter, m_cameraUp);
  m_currentVP = m_perspective * m_lookAt;
}

ContextGLSDL::~ContextGLSDL()
{
}

bool ContextGLSDL::initGLSDL()
{
  std::cout << "Initializing GLSDL Context..." << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  
  m_mainWindow = SDL_CreateWindow(m_mixin->m_applicationName.c_str(),
				  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				  m_mixin->m_width,
				  m_mixin->m_height,
				  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if (m_mainWindow == nullptr)
  {
    std::cout << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  m_glContext = SDL_GL_CreateContext(m_mainWindow);

  // Initialize OpenGL API
  GLenum glew = glewInit();
  if (glew != GLEW_OK)
  {
    std::cout << glewGetString(glew) << std::endl;
    return false;
  }

  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);
  glEnable(GL_MULTISAMPLE);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glPointSize(4.);
  //glLineWidth(2.);

  return true;
}

void ContextGLSDL::paintGL()
{
  glClearColor(0.0, 0.0, 0.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render assets
  for (const auto &mesh : m_meshes)
  {
    mesh.render(m_currentVP);
  }

  SDL_GL_SwapWindow(m_mainWindow);
}

void ContextGLSDL::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void ContextGLSDL::run(float fps)
{

  for (int i = 0; i < m_mixin->m_meshesGL.size(); i++)
  {
    //MeshGL mesh(modelFile);
    //m_meshes.push_back(std::move(mesh));
  }
    
  bool wireframe = true;
  bool isRunning = true;
  
  while (isRunning)
  {
    while (SDL_PollEvent(&m_event) > 0)
    {
      if (m_event.type == SDL_QUIT)
      {
	isRunning = false;
      }
    
      if (m_event.type == SDL_KEYDOWN)
      {
	int k = m_event.key.keysym.sym;
    
	switch (k)
	{
	case SDLK_ESCAPE:
	  isRunning = false;
	  break;
	case SDLK_SPACE:
	  wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  wireframe = !wireframe;
	  break;
	}
      }
    }
    
    // Update the viewport
    this->paintGL();
  }

  // The engine is about to exit.
  this->exitSDL();
}

void ContextGLSDL::exitSDL()
{
  std::cout << "Exiting GLSDL Context..." << std::endl;

  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_mainWindow);

  SDL_Quit();
}
