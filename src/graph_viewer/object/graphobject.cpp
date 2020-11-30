#include "graphobject.h"

GraphObject::GraphObject(QOpenGLWidget *parent, GraphDS *graph)
{
    vao = 0;
    shaderProgram = 0;
    vboVertexes = vboIndexes = 0;

    this->graph = graph;

    glWidget = parent;
    glWidget->makeCurrent();
    initializeOpenGLFunctions();
}

GraphObject::~GraphObject(){
    destroyVBOs();
    destroyShaders();

    if (vertexes){
        delete[] vertexes;
        vertexes = nullptr;
    }

    if (indexes){
        delete[] indexes;
        indexes = nullptr;
    }
}

void GraphObject::createVBOs(){
    glWidget->makeCurrent();
    destroyVBOs();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertexes);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertexes);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(QVector4D), vertexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboIndexes);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexes);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesCount * 3 * sizeof(uint), indexes, GL_STATIC_DRAW);
}

void GraphObject::createShaders(){
    destroyShaders();
    QString vertexShaderFile(":/shaders/vshader.vert");
    QString fragmentShaderFile(":/shaders/fshader.frag");

    QFile vs(vertexShaderFile);
    QFile fs(fragmentShaderFile);

    vs.open(QFile::ReadOnly | QFile::Text);
    fs.open(QFile::ReadOnly | QFile::Text);

    QTextStream streamVs(&vs), streamFs(&fs);

    std::string stdStringVs = streamVs.readAll().toStdString();
    std::string stdStringFs = streamFs.readAll().toStdString();

    GLuint vertexShader = 0;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar * source = stdStringVs.c_str();
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar>infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = stdStringFs.c_str();
    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar>infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *) &isLinked);

    if(isLinked == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar>infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vs.close();
    fs.close();
}

void GraphObject::destroyVBOs(){
    glDeleteBuffers(1, &vboIndexes);
    glDeleteBuffers(1, &vboVertexes);
    glDeleteVertexArrays(1, &vao);

    vboIndexes = vboVertexes = vao = 0;
}

void GraphObject::destroyShaders(){
    glDeleteProgram(shaderProgram);
}

void GraphObject::loadFromOff(){
    QFile model(":/models/off_resources/sphere.off");

    if (model.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream reader(&model);
        QString line;

        reader >> line;
        reader >> vertexCount >> facesCount >> line;

        indexes = new uint[3 * facesCount];
        vertexes = new QVector4D[vertexCount];

        if (vertexCount > 0){
            float maxLim = std::numeric_limits<float>::max();
            float minLim = std::numeric_limits<float>::lowest();

            QVector4D min(maxLim, maxLim, maxLim, 1.0);
            QVector4D max(minLim, minLim, minLim, 1.0);

            for (uint i = 0; i < vertexCount; ++i){
                float x, y, z;
                reader >> x >> y >> z;

                max.setX(std::max(max.x(), x));
                max.setY(std::max(max.y(), y));
                max.setZ(std::max(max.z(), z));

                min.setX(std::min(min.x(), x));
                min.setY(std::min(min.y(), y));
                min.setZ(std::min(min.z(), z));

                vertexes[i] = QVector4D(x, y, z, 1.0);
            }

            this->invDiag = 2.0 / (max - min).length();
            this->midPoint = QVector3D((min + max) * 0.5);

            for (uint i = 0; i < facesCount; ++i){
                uint a, b, c;
                reader >> line >> a >> b >> c;

                indexes[i * 3] = a;
                indexes[i * 3 + 1] = b;
                indexes[i * 3 + 2] = c;
            }

            model.close();

            createShaders();
            createVBOs();
        }
    }
}

void GraphObject::draw(){
    modelMatrix.setToIdentity();
    modelMatrix.scale(invDiag, invDiag, invDiag);
    modelMatrix.translate(-midPoint);

    glBindVertexArray(vao);
    glUseProgram(shaderProgram);

    GLint locModelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, modelMatrix.data());

    glDrawElements(GL_TRIANGLES, facesCount * 3, GL_UNSIGNED_INT, nullptr);
}
