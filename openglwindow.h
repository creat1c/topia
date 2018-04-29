#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "drawable.h"

class QOpenGLShaderProgram;

class OpenGLWindow :   public QOpenGLWindow,
                       protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
  ~OpenGLWindow();

  void AddDrawable(Drawable* pDrawable);

  virtual void render(QPainter* p);
  virtual void render();


  virtual void Initialize();
  void SetAnimating(bool bIsAnimating);


public slots:

  void renderLater();
  void renderNow();

protected:

  bool event(QEvent* e) override;
  void exposeEvent(QExposeEvent* e) override;

private:

  bool m_bIsAnimating;

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void teardownGL();

protected:

  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

private:

  QOpenGLContext* m_pContext;
  QOpenGLPaintDevice* m_pDevice;

  QList<Drawable*> m_drawables;

  QPointF m_pan;
  float m_fZoom;

};

#endif // MAINWINDOW_H
