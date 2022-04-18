/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    시점 좌표계를 Keyboard Callback 함수로 실시간 제어가 가능하도록 구현한다.
    => keyboard의 값에 따라 gluLookAt() 함수의 인자를 변경하여 실시간으로 구현한다.

    기능:
    • Keyboard Callback함수를 이용하여 해당 keyboard key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다.
    • Special Keyboard Callback함수를 이용하여 해당 special key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다.
    • glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
    • glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.       
    • glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.                             

    • glutLookAt()함수를 이용하여 Camera의 위치 및 Camera가 가리키는 초점의 위치를 변경시켜 시점좌표계를 새로 설정한다.
*/
/************************************************************************/
#include <GL/glut.h>

GLfloat cx = 0.0, cy = 0.0, fx = 0.0, fy = 0.0, fz = 0.0;   //glutLookAt()함수의 인자 변화를 위해 정적변수 사용

// Camera의 위치 변화에 따른 기능 수행  => glutLookAt()함수의 인자 중 Camera 위치 부분 좌표 변화
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:   //↑ : Camera의 Y축 좌표가 0.1씩 연속적으로 증가
        cy += 0.1;
        break;

    case GLUT_KEY_DOWN: //↓ : Camera의 Y축 좌표가 0.1씩 연속적으로 감소
        cy -= 0.1;
        break;

    case GLUT_KEY_LEFT: // ← : Camera의 X축 좌표가 0.1씩 연속적으로 감소
        cx -= 0.1;
        break;

    case GLUT_KEY_RIGHT:// → : Camera의 X축 좌표가 0.1씩 연속적으로 증가  
        cx += 0.1;
        break;

    default:
        break;
    }
    glutPostRedisplay();    //Display Event 강제 발생시킴 
}

// Camera가 바라보는 초점의 위치 변화에 따른 기능 수행 => glutLookAt()함수의 인자 중 초점 부분 좌표 변화
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        // 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 증가
    case 'a':
    case 'A':
        fx += 0.1;
        break;

        // 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 감소
    case 'f':
    case 'F':
        fx -= 0.1;
        break;

        // 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 증가
    case 'r':
    case 'R':
        fy += 0.1;
        break;

        // 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 감소
    case 'v':
    case 'V':
        fy -= 0.1;
        break;

        // 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 증가
    case 'z':
    case 'Z':
        fz += 0.1;
        break;

        // 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 감소
    case 't':
    case 'T':
        fz -= 0.1;
        break;

    default:
        break;
    }
        
    glutPostRedisplay();    //Display Event 강제 발생시킴 
}

// 발판 그리는 함수 
void DrawGround() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES);
    for (float x = -2.0; x <= 2.2; x += 0.2) {
        glVertex3f(x, -0.7, -2.0);
        glVertex3f(x, -0.7, 2.0);
    }

    for (float z = -2.0; z <= 2.2; z += 0.2) {
        glVertex3f(-2.0, -0.7, z);
        glVertex3f(2.0, -0.7, z);
    }
    glEnd();
}

// Display Callback 함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // 모델뷰 행렬 스택 사용
    glLoadIdentity();               // 행렬 초기화(CTM을 I로 설정)

    gluLookAt(0.0+cx, 3.5+cy, 3.5, 0.0+fx, 0.0+fy, 0.0+fz, 0.0, 1.0, 0.0);      //Camera 위치 및 Camera가 가리키는 초점의 위치 변화를 위해 변수 사용
    // gluLookAt(-1.0, 0.5, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    DrawGround();

    glColor3f(1.0, 1.0, 0.0);
    glutWireTeapot(1.0);

    glFlush();
}

// Reshape Callback 함수
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);    // 투영 행렬 스택 사용
    glLoadIdentity();               // 행렬 초기화(CTM을 I로 설정)

    gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("VCS (View Coordinate System)");
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Callback 함수 등록 
    glutDisplayFunc(MyDisplay);             //Display Callback 함수
    glutReshapeFunc(MyReshape);             //Reshape Callback 함수
    glutSpecialFunc(MySpecialKeyboard);     //Sepcial KeyBoard Callback 함수 
    glutKeyboardFunc(MyKeyboard);           //KeyBoard Callback 함수

    glutMainLoop();
    return 0;
}