#include <iostream>
#include <gl/glut.h>

#include "application.h"

void InitCallbackFunc() {
    // â ũ�� �̺�Ʈ ���
    glutReshapeFunc(graphics::ReshapeEvent);

    // ������ �̺�Ʈ ���
    glutDisplayFunc(graphics::RenderEvent);

    // Ű���� �̺�Ʈ ���
    glutKeyboardFunc(graphics::KeyboardEvent);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("����! ��! ����");
    
    InitCallbackFunc();
    glutMainLoop();
}