//
// Created by xXRag on 2021-06-21.
//

#include "Renderer.h"

#include <android_native_app_glue.h>
#include "Shader.h"

Renderer::Renderer(android_app *pState, const uint32_t priority)
    : Task(0)
{}

void Renderer::Initialize()
{
    const EGLint attribs[] =
            {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_NONE
            };
    EGLint format;
    EGLint numConfigs;
    EGLint config;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, NULL, NULL);

    eglChooseConfig(m_display, attribs, reinterpret_cast<EGLConfig *>(&config), 1, &numConfigs);
    eglGetConfigAttrib(m_display, reinterpret_cast<EGLConfig>(config), EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(m_pState->window, 0, 0, format);
    m_surface = eglCreateWindowSurface(m_display, reinterpret_cast<EGLConfig>(config), m_pState->window, NULL);

    EGLint contextAttribs[] =
            {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
            };
    m_context = eglCreateContext(m_display, reinterpret_cast<EGLConfig>(config), NULL, contextAttribs);
    eglMakeCurrent(m_display, m_surface, m_surface, m_context);

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, reinterpret_cast<EGLint *>(&m_width));
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, reinterpret_cast<EGLint *>(&m_height));

    m_initialized = true;
}

void Renderer::Destroy()
{
    m_initialized = false;

    if (m_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(m_display, m_context);
        }
        if (m_surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(m_display, m_surface);
        }
        eglTerminate(m_display);
    }
    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;
}

void Renderer::AddRenderable(Renderable *pRenderable)
{
    m_renderables.push_back(pRenderable);
}

void Renderer::RemoveRenderable(Renderable *pRenderable)
{
    if (auto it = std::find(m_renderables.begin(), m_renderables.end(), pRenderable); it != m_renderables.end())
    {
        m_renderables.erase(it);
    }
}

void Renderer::Draw(Renderable *pRenderable)
{
    assert(pRenderable);
    if (pRenderable)
    {
        Geometry* pGeom = pRenderable->GetGeometry();
        Shader* pShader = pRenderable->GetShader();

        assert(pGeom && pShader);

        pShader->Setup(*pRenderable);

        glDrawElements(GL_TRIANGLES, pGeom->GetNumIndices(), GL_UNSIGNED_SHORT, pGeom->GetIndexBuffer());
    }
}

bool Renderer::Start()
{}

void Renderer::OnSuspend()
{}

void Renderer::Update()
{
    if (m_initialized)
    {
        glClearColor(0.95f, 0.95f, 0.95f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& render : m_renderables)
        {
            Draw(render);
        }

        eglSwapBuffers(m_display, m_surface);
    }
}

void Renderer::OnResume()
{}

void Renderer::Stop()
{}