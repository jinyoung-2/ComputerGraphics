/*************************************************************************/
/*				       HW#3-1.   Keyboard Callback1                      */
/*													                     */
/*
    문제 정의 :
    Keyboard Callback를 응용하여 아래의 기능이 수행되도록 한다. 
    Event 발생시 Window영역 범위를 넘어가도 문제가 발생하지 않도록 코드를 작성한다. 
    
    • a 또는 A : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
    • f 또는 F : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동
    • r 또는 R : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동하고, 빨간색으로 Polygon 칠함
    • v 또는 V : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
    • b 또는 B : 파란색으로 Polygon 칠함

    조건: 4개의 vertex 좌표가 어디 있든지 상관없이 구동
    
    기능: 
    Keyboard Callback함수를 이용하여 해당 keyboard key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다. 
    glutPostdisplay())를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다. 
    
*/
/**************************************************************************/

#include <GL/glut.h>

// 변수의 값을 변경시켜, 4개의 vertex좌표를 이동시킨다.
GLfloat DeltaX = 0.0;   //x좌표 이동
GLfloat DeltaY = 0.0;   //y좌표 이동

// RGB값을 변경시켜, 도형의 색깔을 바꾼다. Defalut값은 RGB가 0.5,0.5,0.5로 회색이다.  
GLfloat ColorR = 0.5;
GLfloat ColorG = 0.5;
GLfloat ColorB = 0.5;

//Display Callback함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(ColorR, ColorG, ColorB);

    //DeltaX와 DeltaY를  변경시켜 도형 그리기 
    glBegin(GL_POLYGON);    
    glVertex3f(-0.5 + DeltaX, -0.5 + DeltaY, 0.0);
    glVertex3f(0.5 + DeltaX, -0.5 + DeltaY, 0.0);
    glVertex3f(0.5 + DeltaX, 0.5 + DeltaY, 0.0);
    glVertex3f(-0.5 + DeltaX, 0.5 + DeltaY, 0.0);
    glEnd();

    glutSwapBuffers();
    glFlush();
}

// 눌려지는 keyboard key에 따른 event 설정
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    // 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
    case 'a':
    case 'A':
        DeltaX = DeltaX - 0.1;
        break;
    // 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동
    case 'f':
    case 'F':
        DeltaX = DeltaX + 0.1;
        break;
    //4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동하고, 빨간색으로 Polygon 칠함
    case 'r':
    case 'R':   
        DeltaY = DeltaY - 0.1;
        ColorR = 1.0;
        ColorG = 0.0;
        ColorB = 0.0;
        break;
    //4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
    case 'v':
    case 'V':
        DeltaY = DeltaY + 0.1;
        break;
    //파란색으로 Polygon 칠함
    case 'b':
    case 'B':
        ColorR = 0.0;
        ColorG = 0.0;
        ColorB = 1.0;
        break;
    }
    glutPostRedisplay();    //Display Event 강제 발생시킴 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);   
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard Callback");
    MyInit();

    //Callback 함수 등록 
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);   

    glutMainLoop();
    return 0;
}