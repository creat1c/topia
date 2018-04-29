#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "vertex.h"

class Drawable : public QObject
{

    Q_OBJECT;

public:
    Drawable( size_t nVBufferSize,
              QString vertexShaderFile,
              QString fragShaderFile);


    QOpenGLVertexArrayObject& VAO();
    QOpenGLBuffer& VBuffer();

    VtxArray& Vertices();

    void EnsureInit();
    void EnsureFree();

    void Paint();

private:

    size_t m_nVBufferSize;
    QString m_vertexShaderFile;
    QString m_fragmentShaderFile;

    QOpenGLShaderProgram* m_pShaderProgram;
    QOpenGLBuffer m_vbuf;
    QOpenGLVertexArrayObject m_vao;

protected:

    VtxArray m_vertices;

};

#endif // DRAWABLE_H
