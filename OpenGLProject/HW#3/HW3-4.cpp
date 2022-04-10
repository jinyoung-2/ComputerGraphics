/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    Menu Callback를 응용하여 아래의 기능이 수행되도록 한다.
    • 주메뉴 : Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit
    • Draw Sphere 하부 메뉴 : Small Sphere, Large Sphere
    • Draw Torus 하부 메뉴 : Small Torus , Large Torus
    • Draw Teapot 하부 메뉴 : Small Teapot , Large Teapot
    • Change Color 하부 메뉴 : Red, Green, Blue

    조건:
    • 각 메뉴를 클릭하였을 때 선택 항목에 맞는 도형 및 색이 그려지도록 함.
    • 각 도형의 Small과 Large는 각각의 크기를 구분할 수 있도록 적절히 설정.

    기능:
    Draw할 도형(Sphere, Tours, Teapot 중)을 판단하기 위해 boolean형으로 변수를 선언하고 초기화한다.
    Color 메뉴를 클릭하였을 때 기존 도형에 선택 항목에 맞는 색이 그려질 수 있도록 유의한다.
    각각의 메뉴가 선택되었을 때, 화면에 display될 수 있도록 glutPostdisplay()를 호출하여 강제적으로 display function을 실행시킨다. 
*/
/**************************************************************************/
#include <GL/glut.h>

//도형의 종류와 크기를 판단하기 위해 boolean형으로 변수 선언 및 초기화
GLboolean IsSphere = true;
GLboolean IsTours = false;
GLboolean IsTeapot = false;
GLboolean IsSmall = false;

GLfloat color[3] = { 0.5,0.5,0.5 };     //RGB의 각각의 값을 color배열을 이용하여 나타낸다. 

// Display Callback 
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color[0], color[1], color[2]);

    //Sphere인 경우 
    if ((IsSphere) && (IsSmall))        //small인 경우
        glutWireSphere(0.5, 30, 30);
    else if ((IsSphere) && (!IsSmall))  //large인 경우
        glutWireSphere(0.7, 30, 30);

    //Tours인 경우
    else if ((IsTours) && (IsSmall))    //small인 경우
        glutWireTorus(0.1, 0.3, 20, 20);
    else if ((IsTours) && (!IsSmall))   //large인 경우
        glutWireTorus(0.2, 0.7, 20, 20);

    //Teapot인 경우    
    else  if ((IsTeapot) && (IsSmall))  //small인 경우
        glutWireTeapot(0.2);
    else if ((IsTeapot) && (!IsSmall))  //large인 경우
        glutWireTeapot(0.5);

    glFlush();
}

// Pop-up MainMenu 생성
void MyMainMenu(int entryID) {
    if(entryID==1)              //주메뉴에서 exit 선택한 경우
        exit(0);                //종료

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}

// Pop-up SubMenu 생성
void MySizeMenu1(int entryID) {
    if (entryID == 1)           IsSmall = true;
    else if (entryID == 2)      IsSmall = false;

    //Sphere을 그리도록 설정 
    IsSphere = true;
    IsTours = false;
    IsTeapot = false;

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}
void MySizeMenu2(int entryID) {
    if (entryID == 1)           IsSmall = true;
    else if (entryID == 2)      IsSmall = false;

    //Tours을 그리도록 설정 
    IsSphere = false;
    IsTours = true;
    IsTeapot = false;

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}
void MySizeMenu3(int entryID) {
    if (entryID == 1)           IsSmall = true;
    else if (entryID == 2)      IsSmall = false;

    //Teapot을 그리도록 설정 
    IsSphere = false;
    IsTours = false;
    IsTeapot = true;

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}
void MyColorMenu(int entryID) {

    if (entryID == 1) {         //주메뉴 Color에서 서브메뉴 red 선택한 경우 
        color[0] = 1.0;
        color[1] = 0.0;
        color[2] = 0.0;
    }
    else if (entryID == 2) {    //주메뉴 Color에서 서브메뉴 green 선택한 경우  
        color[0] = 0.0;
        color[1] = 1.0;
        color[2] = 0.0;
    }
    else if (entryID == 3) {    //주메뉴 Color에서 서브메뉴 blue 선택한 경우 
        color[0] = 0.0;
        color[1] = 0.0;
        color[2] = 1.0;
    }

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}


void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    //서브 메뉴 생성 
    //Draw Sphere
    GLint MySizeId1 = glutCreateMenu(MySizeMenu1);  
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Large", 2);

    //Draw Tours
    GLint MySizeId2 = glutCreateMenu(MySizeMenu2);
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Large", 2);

    //Draw Teapot
    GLint MySizeId3 = glutCreateMenu(MySizeMenu3);
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Large", 2);

    //Change Color
    GLint MyColorId = glutCreateMenu(MyColorMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);


    //주메뉴 생성 
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    //현재 pop-up menu에 메뉴 항목 추가 
    //서브메뉴의 id값을 인자로 넣어줌 
    glutAddSubMenu("Draw Sphere", MySizeId1);   
    glutAddSubMenu("Draw Torus", MySizeId2);   
    glutAddSubMenu("Draw Teapot", MySizeId3);
    glutAddSubMenu("Change Color", MyColorId);
    glutAddMenuEntry("Exit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //마우스 오른쪽 버튼 누르면, 현 메뉴가 팝업됨
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Menu Callback");
    MyInit();

    //Callback 등록 
    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    return 0;
}

