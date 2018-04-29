#include "drawable.h"

Drawable::Drawable( size_t nVBufferSize,
                    QString vertexShaderFile,
                    QString fragmentShaderFile)
    : m_nVBufferSize(nVBufferSize)
    , m_vertexShaderFile(vertexShaderFile)
    , m_fragmentShaderFile(fragmentShaderFile)
{
}


QOpenGLBuffer& Drawable::VBuffer()
{
    return m_vbuf;
}

QOpenGLVertexArrayObject& Drawable::VAO()
{
    return m_vao;
}

VtxArray& Drawable::Vertices()
{
    return m_vertices;
}

void Drawable::EnsureInit()
{
    EnsureFree();

//    m_vertices.resize(m_nVBufferSize);

//    if (m_vertices.size() <= 0)
//    {
//        return;
//    }

    m_pShaderProgram = new QOpenGLShaderProgram();
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexShaderFile);
    m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentShaderFile);
    m_pShaderProgram->link();
    m_pShaderProgram->bind();

    m_vbuf.create();
    m_vbuf.bind();
    m_vbuf.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbuf.allocate(m_vertices.data(), sizeof(Vertex) * m_nVBufferSize );

    m_vao.create();
    m_vao.bind();

    m_vao.release();
    m_vbuf.release();
    m_pShaderProgram->release();
}

void Drawable::EnsureFree()
{
    m_vao.destroy();
    m_vbuf.destroy();

    m_vertices.resize(0);
}

void Drawable::Paint()
{
    m_pShaderProgram->bind();

    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(Vertex));
    m_vao.release();

    m_pShaderProgram->release();
}
