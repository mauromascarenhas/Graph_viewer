#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

#include <QFile>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QTextStream>

#include "graphds.h"

class GraphObject : public QOpenGLExtraFunctions
{
public:
    explicit GraphObject(QOpenGLWidget *parent = nullptr, GraphDS *graph = nullptr);
    ~GraphObject();

    void draw();

    inline uint countFaces(){ return this->facesCount; }
    inline uint countVertexes(){ return this->vertexCount; }

    inline QVector3D& getMidPoint() { return this->midPoint; }
    inline QMatrix4x4& getModelMatrix(){ return this->modelMatrix; }

private:
    void loadFromOff();

    GraphDS *graph;

    double invDiag;
    QVector3D midPoint;
    QMatrix4x4 modelMatrix;

    uint *indexes;
    QVector4D *vertexes;

    QOpenGLWidget *glWidget;

    uint facesCount;
    uint vertexCount;

    GLuint vao;

    GLuint vboIndexes;
    GLuint vboVertexes;

    GLuint shaderProgram;

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();
};

#endif // GRAPHOBJECT_H
