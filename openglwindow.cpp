#include "openglwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"

OpenGLWindow::OpenGLWindow(QWindow* parent)
    : QWindow(parent)
    , m_bIsAnimating(false)
    , m_pContext(nullptr)
    , m_pDevice(nullptr)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow()
{  
}

void OpenGLWindow::render(QPainter* p)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::Initialize()
{
}

void OpenGLWindow::render()
{
    if (m_pDevice == nullptr)
    {
        m_pDevice = new QOpenGLPaintDevice;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    m_pDevice->setSize(size());

    QPainter painter(m_pDevice);
    render(&painter);
}

bool OpenGLWindow::event(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::AddDrawable(Drawable* pDrawable)
{
    pDrawable->EnsureInit();

    m_drawables.push_back(pDrawable);
}

void OpenGLWindow::Initialize()
{

}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
    printVersionInformation();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void OpenGLWindow::resizeGL(int w, int h)
{
    // Currently we are not handling width/height changes.
    (void)w;
    (void)h;
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (QList<Drawable*>::iterator it = m_drawables.begin();
         it != m_drawables.end();
         it++)
    {
        (*it)->Paint();
    }

}

void OpenGLWindow::teardownGL()
{    
    QList<Drawable*>::iterator it = m_drawables.begin();
    while (it != m_drawables.end())
    {
        delete( *it);
        it = m_drawables.erase(it);
    }
}



void OpenGLWindow::mouseMoveEvent(QMouseEvent* e)
{
}

void OpenGLWindow::mousePressEvent(QMouseEvent* e)
{
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent* e)
{
}

void OpenGLWindow::printVersionInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
