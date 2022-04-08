/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    Mouse Callback를 응용하여 아래의 기능이 수행되도록 한다.

    • 마우스 왼쪽 버튼을 click 
         4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 연속적으로 이동
    • 마우스 오른쪽 버튼을 click
         이동하고 있는 Polygon이 멈춤

    조건:
    • 4개의 vertex 좌표가 어디 있든지 상관없이 구동
    • 모든 경우에서 동일하게 4개의 vertex 좌표가 윈도우 영역을 벗어나지 말 것

    기능:
    Mouse Callback함수를 이용하여 mouse의 button위치와 state에 따라 각각에 맞는 동작이 실행되도록 한다.
    glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
*/
/**************************************************************************/

#include <GL/glut.h>

//변수의 자료형을 배열로 하여, 도형의 꼭짓점의 x좌표를 표현한다. 
GLfloat Cordix[2] = { -0.5,0.5 };

//Display Callback 함수 
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    //polygon 그리기
    glBegin(GL_POLYGON);
    glVertex3f(Cordix[0], -0.5, 0.0);
    glVertex3f(Cordix[1], -0.5, 0.0);
    glVertex3f(Cordix[1], 0.5, 0.0);
    glVertex3f(Cordix[0], 0.5, 0.0);
    glEnd();
    glFlush();
}

//Mouse Callback 함수
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {         //마우스 왼쪽 버튼 click
        //4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 연속적으로 이동
        if (Cordix[1]>=1.0f) {
            Cordix[0] += 0.0;
            Cordix[1] += 0.0;
        }
        else {
            Cordix[0] += 0.1;
            Cordix[1] += 0.1;
        }
    }
    else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {   //마우스 오른쪽 버튼 click
        //이동하고 있는 Polygon이 멈춤
        Cordix[0] += 0.0;
        Cordix[1] += 0.0;
    }

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard Callback");
    MyInit();

    //Callback 등록
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);                  // Mouse의 Click여부에 따른 Callback함수

    glutMainLoop();
    return 0;
}