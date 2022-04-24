/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    코드7-2를 참조하여 다음과 같은 결과를 낼 수 있는 프로그램 구현

    ?  Teapot 객체와 Torus 객체, 총 2개의 객체를 한 뷰폿에 그림.
    ?  하나의 윈도우를 4개의 뷰폿으로 분할
    ?  우상단의 뷰폿 : 원근투영 => gluPerspective()
    ?  좌하단의 뷰폿 : 평행투영 => glOrtho()
    
    ?  뷰폿에 있는 물체들은 각각 Keyboard Callback과 SpecialKeyboard Callback 함수를 사용하여 Camera의 이동(시점변환)을 제어할 수 있도록 함.(각 뷰폿별로 변환이 수행되도록 함)
    => 좌하단과 우상단 뷰폿에 존재하는 Teapot 객체는 뷰폿의 중앙에 위치하도록 설정해주기 위해 특정 범위 내에서만 변환이 가능하도록 한다. 

    ?  모든 뷰폿들은 객체를 기본적으로 뷰폿의 중심부에 위치하도록 하고. Keyboard로 제어할 경우에도 항상 중심부에 위치하도록 함.
    => 객체의 초점이 중심부에 위치하도록(=0,0,0에 위치하도록)설정
    
    ?  윈도우의 크기를 임의로 변경하거나 Full Screen으로 변경하였을 경우에는 윈도우의 크기에 상관없이 객체의 형태가 왜곡되지 않도록 함.
    => 윈도우의 크기에 영향을 받지 않고 항상 객체의 형태가 동일하도록, 즉 객체 형태 및 크기가 동일하게 유지되어야 한다

    기능:
    ?  glutLookAt()함수를 이용하여 Camera의 위치 및 Camera가 가리키는 초점의 위치를 변경시켜 시점좌표계를 새로 설정한다.
    ?  Keyboard Callback함수를 이용하여 해당 key를 눌렀을 경우 시점변환을 제어할 수 있다.
        => 모든 뷰폿은 동시에 변환이 수행된다.
    ?  Special Keyboard Callback함수를 이용하여 해당 key를 눌렀을 경우 시점변환을 제어할 수 있다.
        => 각 뷰폿별로 따로 변환이 수행된다.
    ?  glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
    ?  glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
    ?  glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.


*/
/************************************************************************/


#include <GL/glut.h>

int Width, Height;
GLfloat cx = 0.0, cy = 0.0, cz = 0.0;   //glutLookAt()함수의 인자 변화를 위해 정적변수 사용

//뷰폿별 Camera위치 조절변수
GLfloat c1x = 0.0, c1y = 0.0, c1z = 0.0;
GLfloat c2x = 0.0, c2y = 0.0, c2z = 0.0;

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);   //색 지정  
}

// 모델변환 => 2개의 물체 그리기(한 뷰폿당) 
void DrawScene() {

    // Teapot
    glColor3f(0.3, 0.3, 0.7);
    glPushMatrix(); //카메라의 이동을 구현하면 되는거라, 초점은 물체 중앙에 위치하도록 구현
        glutWireTeapot(1.0);
        glPushMatrix();
            // Torus
            glColor3f(0.0, 1.0, 1.0);
            glTranslatef(0.0, 0.0, -2.0);
            glRotatef(-30.0, 0.0, 1.0, 0.0);
            glScalef(0.2, 0.2, -0.5);
            glRotatef(30.0, 0.0, 1.0, 0.0);
            glutWireTorus(0.5, 2.0, 20, 20);
            glPopMatrix();
        glPopMatrix();

    // 발판
    //glColor3f(0.7, 0.7, 0.7);           //색 지정
    //glPushMatrix();                     //행렬 스택      
    //    glTranslatef(0.0, -1.0, 0.0);
    //    glBegin(GL_QUADS);              //물체 좌표를 통해 그리기 
    //        glVertex3f(2.0, 0.0, 2.0);
    //        glVertex3f(2.0, 0.0, -2.0);
    //        glVertex3f(-2.0, 0.0, -2.0);
    //        glVertex3f(-2.0, 0.0, 2.0);
    //    glEnd();
    //    glPopMatrix();

}

// Reshape Callback 함수
void MyReshape(int w, int h) {
    Width = w;
    Height = h;

    glMatrixMode(GL_PROJECTION);        // 투영 행렬 스택 사용
    glLoadIdentity();                  // 행렬 초기화(CTM을 I로 설정)

    glMatrixMode(GL_MODELVIEW);         // 모델뷰 행렬 스택 사용
    glLoadIdentity();                  // 행렬 초기화(CTM을 I로 설정)
}


//Display Callback 함수
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //좌하단의 뷰폿 => 직교투영
    glViewport(0, 0, 250, 250);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);      //직교투영변환
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(0.0 + cx + c1x, 0.0 + cy + c1y, 1.0 + cz + c1z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //시점변환
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    //우하단의 뷰폿 
    //glViewport(250, 0, 250, 250);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
    //glLoadIdentity();
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);      //직교투영변환
    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //gluLookAt(-1.0 + cx, 0.0 +cy, 0.0+cz,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //시점변환
    //DrawScene();
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();



    //좌상단의 뷰폿
    //glViewport(0, 250, 250, 250);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
    //glLoadIdentity();
    //gluPerspective(30, 500 / 500, 3.0, 50.0);
    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //gluLookAt(3.0 + cx, 0.0 + cy, 0.0 + cz,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //시점변환
    //DrawScene();
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();


    //우상단의 뷰폿 => 원근투영
    glViewport(250, 250, 250, 250);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(30, 500/500, 3.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(5.0 + cx + c2x, 5.0 + cy + c2y, 5.0 + cz + c2z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //시점변환
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();
}

// Special KeyBoard Callback 함수 => 각각 뷰폿의 시점변환을 따로 제어 
// 모든 뷰폿에 있는 객체들이 뷰폿의 중앙에서 보이게 하기 위해 시점변환 시, 조건문을 이용한다. 특정 범위를 벗어날 경우 + or -0.1를 하지 않는다. 
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
        //뷰폿 Case1의 Camera위치 조절
    case GLUT_KEY_F1:   // Camera의 X축 좌표가 0.1씩 연속적으로 증가 
        if(cx+c1x <= 2.7)
            c1x += 0.1;
        break;
    case GLUT_KEY_F2:   // Camera의 X축 좌표가 0.1씩 연속적으로 감소
        if(cx+c1x >= -2.7)
            c1x -= 0.1;
        break;
    case GLUT_KEY_F3:   // Camera의 Y축 좌표가 0.1씩 연속적으로 증가
        if(cy+c1y <= 2.7)
            c1y += 0.1;
        break;
    case GLUT_KEY_F4:   // Camera의 Y축 좌표가 0.1씩 연속적으로 감소
        if (cy + c1y >= -2.7)
            c1y -= 0.1;
        break;
    case GLUT_KEY_F5:   // Camera의 Z축 좌표가 0.1씩 연속적으로 증가     //그림 사라짐 ==> check하기 
        if (cz + c1z <= 2.0)
            c1z += 0.1;
        break;
    case GLUT_KEY_F6:   // Camera의 Z축 좌표가 0.1씩 연속적으로 감소  
        if (cz + c1z >= -2.0)
            c1z -= 0.1;
        break;

        //뷰폿 Case4의 Camera위치 조절
    case GLUT_KEY_F7:   // Camera의 X축 좌표가 0.1씩 연속적으로 증가  
        if (cx + c2x <= 2.7)
            c2x += 0.1;
        break;
    case GLUT_KEY_F8:   // Camera의 X축 좌표가 0.1씩 연속적으로 감소  
        if (cx + c2x >= -2.7)
            c2x -= 0.1;
        break;
    case GLUT_KEY_F9:   // Camera의 Y축 좌표가 0.1씩 연속적으로 증가 
        if (cy + c2y <= 2.7)
            c2y += 0.1;
        break;
    case GLUT_KEY_F10:  // Camera의 Y축 좌표가 0.1씩 연속적으로 감소  
        if (cy + c2y >= -2.7)
            c2y -= 0.1;
        break;
    case GLUT_KEY_F11:  // Camera의 Z축 좌표가 0.1씩 연속적으로 증가     
        if (cz + c2z <= 2.0)
            c2z += 0.1;
        break;
    case GLUT_KEY_RIGHT:  // Camera의 Z축 좌표가 0.1씩 연속적으로 감소      
        if (cz + c2z >= -2.0)
            c2z -= 0.1;
        break;

    default:
        break;
    }
    glutPostRedisplay();    //Display Event 강제 발생시킴 
}


//KeyBoard Callback 함수 => 모든 뷰폿의 시점변환을 동시에 제어 
void MyKeyboard(unsigned char key, int x, int y) {
    
    //keyboard callback 함수 호출시, 각각의 뷰폿에서 실행시킨 시점변환(카메라이동)을 초기화한 후, 모든 뷰폿은 동일하게 시점변환을 한다. 
    c1x = 0.0;
    c1y = 0.0;
    c1z = 0.0;
    c2x = 0.0;
    c2y = 0.0;
    c2z = 0.0;

    switch (key) {
        // Camera의 X축 좌표가 0.1씩 연속적으로 증가  
    case 'q':
    case 'Q':
        if(cx <= 2.7)
            cx += 0.1;
        break;

        // Camera의 X축 좌표가 0.1씩 연속적으로 감소
    case 'w':
    case 'W':
        if(cx >= -2.7)
            cx -= 0.1;
        break;

        // Camera의 Y축 좌표가 0.1씩 연속적으로 증가
    case 'e':
    case 'E':
        if(cy <= 2.7)
            cy += 0.1;
        break;

        // Camera의 Y축 좌표가 0.1씩 연속적으로 감소
    case 'r':
    case 'R':
        if(cy >= -2.7)
            cy -= 0.1;
        break;

        // Camera의 Z축 좌표가 0.1씩 연속적으로 증가        
    case 'd':
    case 'D':
        if(cz <= 2.0)
            cz += 0.1;
        break;

        // Camera의 Z축 좌표가 0.1씩 연속적으로 감소          
    case 'f':
    case 'F':
        if(cz >= -2.0)
            cz -= 0.1;
        break;

    case 27:
        exit(0);
        break;

    default:
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {

    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewport Partition");

    MyInit();

    //Callback 함수 등록
    glutDisplayFunc(MyDisplay);     //Display Callback 함수
    glutReshapeFunc(MyReshape);     //Reshape Callback 함수
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback 함수
    glutSpecialFunc(MySpecialKeyboard);     //Sepcial KeyBoard Callback 함수 

    glutMainLoop();
    return 0;
}
