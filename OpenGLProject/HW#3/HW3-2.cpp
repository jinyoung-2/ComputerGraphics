/*************************************************************************/
/*				       HW#3-2.   Keyboard Callback2                      */
/*
    문제 정의 :
    Keyboard Callback를 응용하여 아래의 기능이 수행되도록 한다.

    • ↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
    • ↓ : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동
    • ← : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
    • → : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동
    • PageUp : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩 연속적으로 확대(Zoom In)
    • PageDown : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩 연속적으로 축소(Zoom Out)

    조건: 
    • Polygon의 크기가 가시적으로 최대/최소일 때 더 이상 확대/축소가 되지 않도록 고정
    • 4개의 vertex 좌표가 어디 있든지 상관없이 구동
    • 모든 경우에서 동일하게 4개의 vertex 좌표가 윈도우 영역을 벗어나지 않도록 함

    기능:
    Keyboard Callback함수를 이용하여 해당 special key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다.
    glutPostdisplay())를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
*/
/**************************************************************************/


#include <GL/glut.h>

//변수의 자료형을 배열로 하여, polygon의 꼭짓점의 위치를 표현한다. 
GLfloat Cordix[2] = { -0.5,0.5 };
GLfloat Cordiy[2] = { 0.5,-0.5 };

//Display Callback 함수 
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);

    //Polyon 그리기 
    glBegin(GL_POLYGON);
    glVertex3f(Cordix[0], Cordiy[0], 0.0);
    glVertex3f(Cordix[1], Cordiy[0], 0.0);
    glVertex3f(Cordix[1], Cordiy[1], 0.0);
    glVertex3f(Cordix[0], Cordiy[1], 0.0);
    glEnd();
    glFlush();
}

//눌려지는 특수 key에 따른 event 설정 
void MySpecial(int key, int x, int y) {
    switch (key) {
        //↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동
        //y좌표 이동
    case GLUT_KEY_UP:
        if (Cordiy[0] >= 1.0 ){    //윈도우 영역을 벗어난 경우
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
        if (Cordiy[1] <= -1.0) {    //윈도우 영역을 벗어난 경우
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

        //← : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동
        //x좌표 이동
    case GLUT_KEY_LEFT:
        if (Cordix[0] <= -1.0) {    //윈도우 영역을 벗어난 경우
            /*Cordix[0] -= 0.0;
            Cordix[1] -= 0.0;*/
            Cordix[0] = -1.0;
            Cordix[1] = 0.0;
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1 감소
            Cordix[0] -= 0.1;
            Cordix[1] -= 0.1;
        }
        break;

        //→ : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동
        //x좌표 이동
    case GLUT_KEY_RIGHT:
        if (Cordix[1] >= 1.0) {    //윈도우 영역을 벗어난 경우
            /*Cordix[0] += 0.0;
            Cordix[1] += 0.0;*/
            Cordix[0] = 0.0;
            Cordix[1] = 1.0;
        }
        else {    //윈도우 영역을 벗어나지 않은 경우
            //0.1증가
            Cordix[0] += 0.1;
            Cordix[1] += 0.1;
        }
        break;

       
        /*
        * Cordix[1] - Cordix[0] <= 0.2 && Cordiy[0] - Cordiy[1] <= 0.2로 코드를 작성하면, 
            부동소수점 오류로 인해 가시적으로 최소임에도 불구하고 축소가 되어 도형이 사라진다.
            따라서, Cordix[1]-Cordix[0]<=0.4 && Cordiy[0]-Cordiy[1]<=0.4로 코드를 작성하여 가시적으로 최소일 경우 축소를 금지시켰다.
           마찬가지로, Cordix[1]-Cordix[0] >= 2.0 && Cordiy[0]-Cordiy[1] >= 2.0로 코드를 작성하면, 
            부동소주점 오류로 인해 가시적으로 최대임에도 불구하고 확대되어 도형이 window영역보다 커지게 된다. 
        * 부동소수점오류가 발생하는 이유는 x,y좌표를 나타내는 배열의 자료형을 float로 하여, float 특성상 정확한 값을 갖고 있지 않아 발생하는 것이다. 
        * 부동소수점오류 발생을 줄이기 위해, type을 double로 하는 것이 좋다. 
        */

        //PageUp : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩 연속적으로 확대(Zoom In)
    case GLUT_KEY_PAGE_UP: 
        if ((Cordix[0] <= -1.0) || (Cordiy[0] >= 1.0) || (Cordix[1] >= 1.0) || (Cordiy[1] <= -1.0)) {     //가시적으로 최대일 때 확대 금지 
            //에러: Cordix[1]-Cordix[0] >= 2.0 && Cordiy[0]-Cordiy[1] >= 2.0
            Cordix[0] -= 0.0;
            Cordix[1] += 0.0;
            Cordiy[0] += 0.0;
            Cordiy[1] -= 0.0;
        }
        else {      //확대하기 
            Cordix[0] -= 0.1;
            Cordix[1] += 0.1;
            Cordiy[0] += 0.1;
            Cordiy[1] -= 0.1;
        }
        break;

        //PageDown : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩 연속적으로 축소(Zoom Out)
        //가시부피영역 재설정?
    case GLUT_KEY_PAGE_DOWN:
        if (Cordix[1]-Cordix[0]<=0.4 && Cordiy[0]-Cordiy[1]<=0.4) {     //가시적으로 최소일 때 축소 금지 
            //에러: Cordix[1] - Cordix[0] <= 0.2 && Cordiy[0] - Cordiy[1] <= 0.2
            //(Cordix[0] <= -1.0) || (Cordiy[0] >= 1.0) || (Cordix[1] >= 1.0) || (Cordiy[1] <= -1.0) || ((Cordix[1] - Cordix[0] <= 0.2) && (Cordiy[0] - Cordiy[1] <= 0.2))
            Cordix[0] += 0.0;
            Cordix[1] -= 0.0;
            Cordiy[0] -= 0.0;
            Cordiy[1] += 0.0;
        }
        else {      //축소하기 
            Cordix[0] += 0.1;
            Cordix[1] -= 0.1;
            Cordiy[0] -= 0.1;
            Cordiy[1] += 0.1;
        }
        break;

    default:
        break;
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
    glutInitWindowSize(300,300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard Callback");
    MyInit();

    //Callback 함수 등록 
    glutDisplayFunc(MyDisplay);
    glutSpecialFunc(MySpecial);

    glutMainLoop();
    return 0;
}
