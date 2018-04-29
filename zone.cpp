#include "zone.h"

Zone::Zone()
    : Drawable( 3,
                ":/shaders/simple.vert",
                ":/shaders/simple.frag")
{
    m_vertices.clear();
    m_vertices.resize(3);

    m_vertices[0] = Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) );
    m_vertices[1] = Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) );
    m_vertices[2] = Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) );

}
