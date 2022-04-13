/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    Timer Callback를 응용하여 아래의 기능이 수행되도록 한다.
    • 프로그램이 실행되면 도형이 오른쪽으로 0.1씩 연속적으로 움직이게 하고, 오른쪽 경계에 부딪히면 도형의 색깔이 변하게 한 후, 다시 도형이 왼쪽으로 0.1씩 연속적으로 움직이는 과정을 반복함.
    • 마우스 왼쪽 키를 누르면 움직이는 도형이 멈춤.

    조건:
    • 모든 경우에서 동일하게 4개의 vertex 좌표가 윈도우 영역을 벗어나지 말 것
    • 도형의 색깔은 지정하지 않으니 자유롭게 설정함.

    기능:
    • Timer Callback 함수 마지막 부분에 glutTimerFunc()를 호출하여 계속해서 타이머 이벤트를 인의적으로 발생시킨다.
        이유: GLUT 타이머는 단 한번만 타이머 이벤트를 발생시킨다. 
    • glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다. 
    • glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다. 
    • GLfloat trans = 0.1를 통해 경계에 부딪히지 않을 때 현재 trans값(이동중이던 방향)으로 x좌표가 이동함
*/
/**************************************************************************/

#include <GL/glut.h>

GLfloat Cordix[2] = { -1.0,0.0 };   //x좌표를 배열의 원소로 표현
GLfloat Color[3] = { 1.0,0.0,0.0 }; //RGB를 배열의 원소로 표현
GLfloat trans = 0.1;                //경계에 부딪힐 때 변하는 값으로, 경계에 부딪히지 않고 이동하는 중이면 현재 trans값으로 x좌표가 이동함

// Display Callback 
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    //polygon 그리기
    glBegin(GL_POLYGON);
    glColor3f(Color[0], Color[1], Color[2]);
    glVertex3f(Cordix[0], -0.5, 0.0);
    glVertex3f(Cordix[1], -0.5, 0.0);
    glVertex3f(Cordix[1], 0.5, 0.0);
    glVertex3f(Cordix[0], 0.5, 0.0);
    glEnd();
    glutSwapBuffers();  //front buffer와 back buffer를 서로 전환한다. 
}

// Mouse Callback 
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) {     //마우스 왼쪽 키를 누른 경우
        //움직이는 도형 멈춤
        Cordix[0] += 0.0;
        Cordix[1] += 0.0;   //Q. -로 처리 안 해도 괜찮겠지?

        glutPostRedisplay();    //Display Event 강제 발생시킴 
    }
}

// Timer Callback 
void MyTimer(int Value) {
    //오른쪽 경계에 부딪힌 경우 
    if (Cordix[1] >= 1.0f) {        //f기호를 사용하여 float타입의 값을 원한다는 사실을 알려준다. 
        //도형 색깔 변화  -> 초록색으로 변화 
        Color[0] = 0.0;
        Color[1] = 1.0;
        Color[2] = 0.0;

        //왼쪽 경계에 부딪히기 전까지 왼쪽으로 0.1씩 이동하게끔 trans변수에 -0.1 값을 할당한다. 
        trans = -0.1;
    }

    //왼쪽 경계에 부딪힌 경우
    else if (Cordix[0] <= -1.0f) {  //f기호를 사용하여 float타입의 값을 원한다는 사실을 알려준다. 
        //도형 색깔 변화 -> 빨간색으로 변화
        Color[0] = 1.0;
        Color[1] = 0.0;
        Color[2] = 0.0;

        //오른쪽 경계에 부딪히기 전까지 오른쪽으로 0.1씩 이동하게끔 trans변수에 0.1 값을 할당한다.  
        trans = 0.1;
    }

    //경계에 부딪히지 않고, 경계 사이에서 이동하는 경우 => 이동방향을 유지한 채 0.1씩 이동 
    Cordix[0] += trans;
    Cordix[1] += trans;
    
    glutPostRedisplay();                //Display Event 강제 발생시킴 
    glutTimerFunc(120, MyTimer, 1);     //인위적으로  Timer Callback() 호출 
    //120msec 후에 호출 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);    // 2개의 buffer를 이용한다
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Timer Callback");
    MyInit();

    //Callback 등록 
    glutDisplayFunc(MyDisplay);
    glutTimerFunc(40, MyTimer, 1);  //Timer Callback
    glutMouseFunc(MyMouseClick);    //Mouse Callback

    glutMainLoop();
    return 0;
}