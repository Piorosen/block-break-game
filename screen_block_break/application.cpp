#include <iostream>
#include <gl/glut.h>

using namespace std;

#include "application.h"
#include "display.h"


void graphics::keyboardEvent(unsigned char key, int x, int y) {

}

void graphics::renderEvent() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); 

	

	glutSwapBuffers();
}

void graphics::reshapeEvent(int x, int y) {


}

void timerTest(int value) {
	glutTimerFunc(500, timerTest, value + 1);
}

static graphics::size displaySize;
graphics::size graphics::global::getDisplaySize() {
	return displaySize;
}

graphics::point graphics::global::getDisplayPosition() {
	return graphics::info::getPosition();
}

void graphics::initDisplay(int* argc, char** argv, 
						   size display, std::string title) {
	displaySize = display;
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow(title.c_str());

	auto pMonitor = graphics::info::primaryMonitor();
	graphics::info::setPosition(graphics::point{
		pMonitor.size.width / 2 - display.width / 2,
		pMonitor.size.height / 2 - display.height / 2
	});

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, display.width, display.height, 0);

	// â ũ�� �̺�Ʈ ���
	glutReshapeFunc(graphics::reshapeEvent);
	// ������ �̺�Ʈ ���
	glutDisplayFunc(graphics::renderEvent);
	// Test
	glutTimerFunc(500, timerTest, 0);
	// Ű���� �̺�Ʈ ���
	glutKeyboardFunc(graphics::keyboardEvent);

	glutMainLoop();
}
