#ifndef CANVAS_H
#define CANVAS_H

#include <QGLWidget>

#include <GL/gl.h>

class Canvas : public QGLWidget
{

    Q_OBJECT;

public:
    Canvas();


protected:



private:

    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QGLShaderProgram m_shaderProg;

};

#endif // CANVAS_H
