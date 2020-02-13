#include "PointRenderer.h"
#include "platform.h"

void PointRenderer::init()
{
    const int len = 10000;
    
    char vertexShaderStr[len];
    char fragmentShaderStr[len];
    
    // Compile regular program
    
#if defined PLATFORM_WINDOWS || defined PLATFORM_OSX
    snprintf(vertexShaderStr, len, "#version 330 core\n%s", vertexShaderCodeDesktop);
    snprintf(fragmentShaderStr, len, "#version 330 core\n%s", fragmentShaderCodeDesktop);
#endif
    
    programMain = loadProgram(vertexShaderStr, fragmentShaderStr, false);
    
#if defined PLATFORM_WINDOWS || defined PLATFORM_OSX
    // Generate VAO
    glGenVertexArrays(1, (GLuint *)&vao);
    checkGLError("glGenVertexArrays");
#endif
    
    // Generate VBO
    glGenBuffers(1, (GLuint *)&vbo);
    checkGLError("glGenBuffers");
}

void PointRenderer::tick()
{

}

#pragma optimize ("", 0)
void PointRenderer::draw(int eye, std::vector<Point> points, Object *camera)
{
    // Get aspect
    float width = PLAT_GetWindowWidth();
    float height = PLAT_GetWindowHeight();

#ifdef PLATFORM_OPENVR
    float aspect = 1.0;
#else
    float aspect = width / height;
#endif

    int curProgram = programMain;
    
    glUseProgram(curProgram);
    checkGLError("glUseProgram");
    
    //
    // Set vertex data
    //
    
    int numVerts = points.size();
    int floatsPerVert = 8;
    
    float *data = new float[numVerts * floatsPerVert];
    
    int cursor = 0;
    
    for (int p = 0; p < points.size(); p++)
    {
        Point point = points[p];
        
        data[cursor + 0] = point.pos.x;
        data[cursor + 1] = point.pos.y;
        data[cursor + 2] = point.pos.z;
        data[cursor + 3] = point.pos.w;

        data[cursor + 4] = point.color.r;
        data[cursor + 5] = point.color.g;
        data[cursor + 6] = point.color.b;
        data[cursor + 7] = point.color.a;

        cursor += floatsPerVert;
    }
    
    //
    // Set vertex attribs
    //

    // Bind VAO
#if defined PLATFORM_WINDOWS || defined PLATFORM_OSX
    glBindVertexArray(vao);
    checkGLError("glBindVertexArray");
#endif

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    checkGLError("glBindBuffer");

    // Load data into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatsPerVert * numVerts, data, GL_STATIC_DRAW);
    checkGLError("glBufferData");
    
    // Delete data
    delete data;

    // Set vertex attribs
    int stride = floatsPerVert * sizeof(float);

    setVertexAttrib(curProgram, "vPosition", 4, GL_FLOAT, false, stride, 0);
    setVertexAttrib(curProgram, "vColor", 4, GL_FLOAT, false, stride, 4);

    //
    // Set uniforms
    //
    
    // Set the matrices
    glm::mat4 mvMatrix;
    glm::mat4 projectionMatrix;
    
    glm::mat4 cameraRotate;
    glm::mat4 cameraTranslate;
    glm::mat4 rotate;
    
    glm::mat4 scaleToNDC;
    
    // Modelview matrix
#ifdef PLATFORM_OPENVR
    scaleToNDC = glm::scale(glm::mat4(), glm::vec3(VRSCALE, VRSCALE, VRSCALE));
#else
    scaleToNDC = glm::scale(glm::mat4(), glm::vec3(NDC_SCALE, NDC_SCALE, NDC_SCALE));
#endif
    
    cameraRotate = glm::rotate(glm::mat4(), glm::radians(camera->roll), glm::vec3(0, 0, 1)) // Camera roll
    * glm::rotate(glm::mat4(), -glm::radians(camera->pitch), glm::vec3(1, 0, 0)) // Camera pitch
    * glm::rotate(glm::mat4(), glm::radians(camera->yaw), glm::vec3(0, 1, 0)); // Camera yaw
    
    cameraTranslate = glm::translate(glm::mat4(), glm::vec3(-camera->position.x, -camera->position.y, -camera->position.z)); // Camera translate
    
#ifdef PLATFORM_OPENVR
    mvMatrix =
    glm::make_mat4((const GLfloat *)g_poseEyeMatrix.get())
    * scaleToNDC
    * cameraRotate
    * cameraTranslate
    * glm::translate(glm::mat4(), glm::vec3(object->position.x, object->position.y, object->position.z)) // World translate
    * rotate
    * glm::scale(glm::mat4(), object->scale / glm::vec3(2.0, 2.0, 2.0)); // Scale
#else
    mvMatrix =
    scaleToNDC
    * cameraRotate
    * cameraTranslate;
#endif
    
    setMatrix(curProgram, "mvMatrix", mvMatrix);

    // Projection matrix
    glm::mat4 projMatrix;
    
#if defined PLATFORM_OPENVR
    projMatrix = glm::make_mat4((const GLfloat *)g_projectionMatrix.get());
#else
    projMatrix = glm::perspective(VIEW_FOV, aspect, 0.001f, 1000.0f);
#endif
    
    setMatrix(curProgram, "projectionMatrix", projMatrix);

    // Global color
    setUniform4f(curProgram, "globalColor", globalColor.x, globalColor.y, globalColor.z, globalColor.w);

    //
    // Draw
    //
    
    glDrawArrays(GL_POINTS, 0, numVerts);
    checkGLError("glDrawArrays");
}
#pragma optimize ("", 1)
