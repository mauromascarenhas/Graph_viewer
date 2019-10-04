#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>

class GraphViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GraphViewer(QWidget *parent = nullptr);
    ~GraphViewer();

    void createVBOs();
    void destroyVBOs();

    void createShaders();
    void destroyShaders();

    void setBackgroundColour(float r, float g, float b, float a);

private:
    float bgR, bgG, bgB, bgA;

    QOpenGLBuffer *vboColours;
    QOpenGLBuffer *vboIndexes;
    QOpenGLBuffer *vboVertexes;

    QOpenGLVertexArrayObject *vao;

    QVector4D *colours;
    QVector4D *vertexes;
    unsigned int *indexes;

    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // GRAPHVIEWER_H
