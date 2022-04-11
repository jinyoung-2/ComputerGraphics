/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    Idle Callback를 응용하여 아래의 기능이 수행되도록 한다.
    • ↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
    • ↓ : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동
    • ← : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
    • → : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동

    조건:
    • 모든 경우에서 동일하게 4개의 vertex 좌표가 윈도우 영역을 벗어나지 말 것

    기능:
    • Idle Callback()는 다른 아무 일도 생기지 않는 동안 display function을 통해 그래픽 기본요소를 계속 생성한다.
    • glutPostRedisplay()를 호출하여 display event를 강제로 발생시킨다.
    • glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
    • glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.
*/
/**************************************************************************/
#include <GL/glut.h>

//도형의 x와 y 좌표를 배열의 원소로 표현
GLfloat Cordix[2] = { -1.0,0.0 };
GLfloat Cordiy[2] = { -0.5,0.5 };

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.5, 0.8);
    //polygon 그리기
    glBegin(GL_POLYGON);
    glVertex3f(Cordix[0], Cordiy[0], 0.0);
    glVertex3f(Cordix[1], Cordiy[0], 0.0);
    glVertex3f(Cordix[1], Cordiy[1], 0.0);
    glVertex3f(Cordix[0], Cordiy[1], 0.0);
    glEnd();
    glutSwapBuffers();  //front buffer와 back buffer를 서로 전환한다. 
}

void MySpecial(int key, int x, int y) {
    switch (key) {

        //↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
        //y좌표 이동
    case GLUT_KEY_UP:
        if (Cordiy[0] >= 1.0f) {    //윈도우 영역을 벗어난 경우
            Cordiy[0] += 0.0;
            Cordiy[1] += 0.0;
            /*Cordiy[0] = 1.0;
            Cordiy[1] = 0.0;*/
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1증가
            Cordiy[0] += 0.1;
            Cordiy[1] += 0.1;
        }
        break;

        //↓ : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동
        //y좌표 이동
    case GLUT_KEY_DOWN:
        if (Cordiy[1] <= -1.0f) {    //윈도우 영역을 벗어난 경우
            Cordiy[0] -= 0.0;
            Cordiy[1] -= 0.0;
            /*Cordiy[0] = 0.0;
            Cordiy[1] = -1.0;*/
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1 감소
            Cordiy[0] -= 0.1;
            Cordiy[1] -= 0.1;
        }
        break;

       // ← : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
       // x좌표 이동
    case GLUT_KEY_LEFT:
        if (Cordix[0] <= -1.0f) {    //윈도우 영역을 벗어난 경우
            Cordix[0] -= 0.0;
            Cordix[1] -= 0.0;
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1 감소
            Cordix[0] -= 0.1;
            Cordix[1] -= 0.1;
        }
        break;

      // → : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동
      //  x좌표 이동
    case GLUT_KEY_RIGHT:
        if (Cordix[1] >= 1.0f) {    //윈도우 영역을 벗어난 경우
            Cordix[0] += 0.0;
            Cordix[1] += 0.0;
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1증가
            Cordix[0] += 0.1;
            Cordix[1] += 0.1;
        }
        break;
    default:
        break;
    }

    //glutPostRedisplay();
}

// Idle Callback
void MyIdle() {
    glutSpecialFunc(MySpecial);     //callback 함수 등록 
    glutPostRedisplay();            //Display Event 강제 발생시킴 
}

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Idle Callback");
    MyInit();
    
    //Callback 등록
    glutDisplayFunc(MyDisplay);
    glutIdleFunc(MyIdle);   //Idle Callback 

    glutMainLoop();
    return 0;
}