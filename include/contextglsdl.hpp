#pragma once
 
#include "pch.h"
#include "settingsmixin.hpp"
#include "meshgl.hpp"

class ContextGLSDL
{
public:
    explicit ContextGLSDL(std::unique_ptr<SettingsMixin> mixin);
    ~ContextGLSDL();

    bool initGLSDL();
    void paintGL();
    void resizeGL(int w, int y);

    void run(float fps = 1./60.);
    void exitSDL();

protected:

    SDL_Window *m_mainWindow;
    SDL_Surface *m_mainSurface;
    SDL_GLContext m_glContext;
    SDL_Event m_event;
    std::unique_ptr<SettingsMixin> m_mixin;
    std::vector<MeshGL> m_meshes;
};
