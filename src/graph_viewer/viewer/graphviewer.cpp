#include "graphviewer.h"

GraphViewer::GraphViewer(QWidget *parent) :
    QOpenGLWidget (parent)
{
    vao = nullptr;
    indexes =  nullptr;
    shaderProgram = nullptr;
    colours = vertexes = nullptr;
    fragmentShader = vertexShader = nullptr;
    vboColours = vboIndexes = vboVertexes = nullptr;

    bgR = bgG = bgB = bgA = 0;
}

GraphViewer::~GraphViewer(){
    destroyVBOs();
    destroyShaders();
}

void GraphViewer::createVBOs(){
    makeCurrent();
    destroyVBOs();

    delete [] colours;
    colours = new QVector4D[9];

    delete [] vertexes;
    vertexes = new QVector4D[9];

    delete [] indexes;
    indexes = new unsigned int[8 * 3];

    float sqrt2 = sqrt(2) * 0.25f;

    vertexes[0] = QVector4D(0, 0, 0, 1);
    vertexes[1] = QVector4D(0.5, 0, 0, 1);
    vertexes[2] = QVector4D(sqrt2, sqrt2, 0, 1);
    vertexes[3] = QVector4D(0, 0.5, 0, 1);
    vertexes[4] = QVector4D(-sqrt2, sqrt2, 0, 1);
    vertexes[5] = QVector4D(-0.5, 0, 0, 1);
    vertexes[6] = QVector4D(-sqrt2, -sqrt2, 0, 1);
    vertexes[7] = QVector4D(0, -0.5, 0, 1);
    vertexes[8] = QVector4D(sqrt2, -sqrt2, 0, 1);

    colours[0] = QVector4D(1, 1, 1, 1);
    colours[1] = QVector4D(1, 1, 0, 1);
    colours[2] = QVector4D(1, 1, 0, 1);
    colours[3] = QVector4D(0, 1, 0, 1);
    colours[4] = QVector4D(0, 1, 0, 1);
    colours[5] = QVector4D(0, 1, 1, 1);
    colours[6] = QVector4D(0, 1, 1, 1);
    colours[7] = QVector4D(0, 0, 1, 1);
    colours[8] = QVector4D(0, 0, 1, 1);

    indexes[0] = 0;
    indexes[1] = 1;
    indexes[2] = 2;

    indexes[3] = 0;
    indexes[4] = 2;
    indexes[5] = 3;

    indexes[6] = 0;
    indexes[7] = 3;
    indexes[8] = 4;

    indexes[9] = 0;
    indexes[10] = 4;
    indexes[11] = 5;

    indexes[12] = 0;
    indexes[13] = 5;
    indexes[14] = 6;

    indexes[15] = 0;
    indexes[16] = 6;
    indexes[17] = 7;

    indexes[18] = 0;
    indexes[19] = 7;
    indexes[20] = 8;

    indexes[21] = 0;
    indexes[22] = 8;
    indexes[23] = 1;

    vao = new QOpenGLVertexArrayObject(this);
    vao->create();
    vao->bind();

    vboColours = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboColours->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboColours->create();
    vboColours->bind();
    vboColours->allocate(colours, 9 * sizeof(QVector4D));

    shaderProgram->enableAttributeArray("vColours");
    shaderProgram->setAttributeBuffer("vColours", GL_FLOAT, 0, 4, 0);

    vboColours->release();

    delete [] colours;
    colours = nullptr;

    vboVertexes = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboVertexes->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboVertexes->create();
    vboVertexes->bind();
    vboVertexes->allocate(vertexes, 9 * sizeof(QVector4D));

    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4, 0);

    vboVertexes->release();
    delete [] vertexes;
    vertexes = nullptr;

    vboIndexes = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vboIndexes->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboIndexes->create();
    vboIndexes->bind();
    vboIndexes->allocate(indexes, 8 * 3 * sizeof(unsigned int));

    vboIndexes->release();
    delete [] indexes;
    indexes = nullptr;

    vao->release();
}

void GraphViewer::destroyVBOs(){
    makeCurrent();

    if (vboColours){
        vboColours->release();

        delete vboColours;
        vboColours = nullptr;
    }

    if (vboIndexes){
        vboIndexes->release();

        delete vboIndexes;
        vboIndexes = nullptr;
    }

    if (vboVertexes){
        vboVertexes->release();
        vboVertexes->destroy();

        delete vboVertexes;
        vboVertexes = nullptr;
    }

    if (vao){
        delete vao;
        vao = nullptr;
    }
}

void GraphViewer::createShaders(){
    makeCurrent();
    destroyShaders();

    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!vertexShader->compileSourceFile(QStringLiteral(u":/glsl/vshader1.glsl"))) qWarning() << vertexShader->log();

    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if (!fragmentShader->compileSourceFile(QStringLiteral(u":/glsl/fshader1.glsl"))) qWarning() << fragmentShader->log();

    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);

    if (!shaderProgram->link()) qWarning() << shaderProgram->log() << endl;
}

void GraphViewer::destroyShaders(){
    makeCurrent();

    delete vertexShader;
    vertexShader = nullptr;

    delete fragmentShader;
    fragmentShader = nullptr;

    if (shaderProgram){
        shaderProgram->release();

        delete shaderProgram;
        shaderProgram = nullptr;
    }
}

void GraphViewer::setBackgroundColour(float r, float g, float b, float a){
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;

    makeCurrent();
    update();
}

void GraphViewer::initializeGL(){
    initializeOpenGLFunctions();
    createShaders();
    createVBOs();
}

void GraphViewer::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void GraphViewer::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bgR, bgG, bgB, bgA);

    vao->bind();
    shaderProgram->bind();

    vboIndexes->bind();
    glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr);
    vboIndexes->release();

    vao->release();
    shaderProgram->release();
}
