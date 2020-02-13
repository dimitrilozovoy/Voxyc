#pragma once

#include <vector>
#include "Renderer.h"
#include "GLIncludes.h"

typedef struct Point
{
    glm::vec4 pos;
    glm::vec4 color;
};

class PointRenderer: Renderer
{
public:
	void init();
	void tick();
    void draw(int eye, std::vector<Point> points, Object *camera);

private:
	//
	// VERTEX SHADER DESKTOP
	//

	const char* vertexShaderCodeDesktop =

		"precision highp float;" \

		"in vec4 vPosition;" \
		"out lowp vec4 posOut; " \
        "uniform mat4 mvMatrix; " \
		"uniform mat4 projectionMatrix; " \
		"out float distToCamera; " \
		"in vec4 vColor; " \
		"out vec4 vColorOut;" \

		"void main() {" \
		"  gl_Position = projectionMatrix * mvMatrix * vPosition; "
		"  posOut = gl_Position; " \

        "  vec4 posBeforeProj = mvMatrix * vPosition;" \
		"  distToCamera = -posBeforeProj.z; " \

		"  vColorOut = vColor; " \
		"}\n";


	//
	// FRAGMENT SHADER DESKTOP
	//

	const char* fragmentShaderCodeDesktop =

		"precision highp float;" \

		"uniform lowp vec4 globalColor; " \
		"out lowp vec4 posOut; " \
		"out vec4 finalColor; " \

		"out float distToCamera; " \
		"out vec4 vColorOut; " \

		"void main() {" \
		"   finalColor = vColorOut * globalColor; " \
        "}\n";

	int programMain = -1;
	int vao = -1;
	int vbo = -1;
};
