#include <stdlib.h>
#include <GL/glut.h>

static int body = 0, head = 0, arm1 = 0, arm2 = 0, leg1 = 0, leg2 = 0;  //회전 각도 
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //상황에 따라 기존 회전 각도에 연산할 각도 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop임을 전달하기 위해 필요한 변수 
static int go_to = -1;

//Timer Callback 함수
void MyTimer(int value) {
    if (value == 1) {           //머리 움직이기
        if (dir_head == 0) {    //stop인 경우
            dir_head = 1;
            return;
        }
        head += dir_head;       //새로운 각도 
        if (head == 0) {
            if (chk0 == 1) {    //원래 위치이며, stop인 경우
                chk0 = -1;      //chk관련 변수 -1로 지정하여 stop이 아님을 명시
                return;
            }
            else                //원래 위치인데, stop이 아닌 이동하는 경우
                chk0 = 1;       //chk관련 변수 1로 지정하여 다음번에 원래 위치일 경우 stop임을 명시 
        }

        //회전 범위 
        if (head >= 50)
            dir_head = -1;
        else if (head <= -50)
            dir_head = 1;

        glutTimerFunc(50, MyTimer, 1);
        glutPostRedisplay();
    }
    else if (value == 2) {      //오른쪽팔 움직이기
        if (dir_arm1 == 0) {    //stop인 경우  => 처음위치로 이동하도록 dir_arm1각도 1로 설정 
            dir_arm1 = 1;
            return;
        }

        arm1 += dir_arm1;       //새로운 각도

        //회전 범위
        if (arm1 <= -45)
            dir_arm1 = 1;
        else if (arm1 >= 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
            chk1 = -1;
            return;
        }
        glutTimerFunc(50, MyTimer, 2);
        glutPostRedisplay();
    }
    else if (value == 3) {      //왼쪽팔 움직이기
        if (dir_arm2 == 0) {    //stop인 경우
            dir_arm2 = -1;
            return;
        }
        arm2 += dir_arm2;       //새로운 각도

        //회전 범위
        if (arm2 >= 45)
            dir_arm2 = -1;
        else if (arm2 == 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
            chk2 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 3);
        glutPostRedisplay();
    }
    else if (value == 4) {      //오른쪽다리 움직이기
        if (dir_leg1 == 0) {    //stop인 경우
            dir_leg1 = 1;
            return;
        }
        leg1 += dir_leg1;       //새로운 각도

        //회전 범위
        if (leg1 <= -45)
            dir_leg1 = 1;
        else if (leg1 == 0) {  //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
            chk3 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 4);
        glutPostRedisplay();
    }
    else if (value == 5) {      //왼쪽다리 움직이기
        if (dir_leg2 == 0) {    //stop인 경우
            dir_leg2 = -1;
            return;
        }
        leg2 += dir_leg2;       //새로운 각도

        //회전 범위
        if (leg2 >= 45)
            dir_leg2 = -1;
        else if (leg2 == 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
            chk4 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 5);
        glutPostRedisplay();
    }
    else if (value == 6) {
        if (go_to == 1) {           //머리 stop
            dir_head = 1;
            return;
        }
        else if (go_to == 2) {      //오른쪽팔 stop
            dir_arm1 = 1;
            return;
        }
        else if (go_to == 3) {      //왼쪽팔 stop
            dir_arm2 = -1;
            return;
        }
        else if (go_to == 4) {      //오른쪽다리 stop
            dir_leg1 = 1;
            return;
        }
        else if (go_to == 5) {      //왼쪽다리 stop
            dir_leg2 = -1;
            return;
        }
    }
}


// Pop-up MainMenu 생성
// 해당 메뉴에 맞는 신체가 한번 움직였다가 원래 자세로 돌아옴
void MyMainMenu(int entryID) {  //entryID: 메뉴에서 선택한 값의 번호 
    if (entryID == 1) {
        //머리 움직이기
        if (chk0 != 1) {    //stop상태 -> move상태로 변환
            chk0 = 1;
        }
        dir_head = -1;
        glutTimerFunc(40, MyTimer, entryID);    //타이머 콜백함수 등록
    }
    else if (entryID == 2) {
        //오른쪽팔 움직이기
        if (chk1 != 1) {        //stop상태 -> move상태로 변환
            chk1 = 1;
        }
        dir_arm1 = -1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 3) {
        //왼쪽팔 움직이기
        if (chk2 != 1) {    //stop상태 -> move상태로 변환    
            chk2 = 1;
        }
        dir_arm2 = 1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 4) {
        //오른쪽다리 움직이기
        if (chk3 != 1) {    //stop상태 -> move상태로 변환
            chk3 = 1;
        }
        dir_leg1 = -1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 5) {
        //왼쪽다리 움직이기
        if (chk4 != 1) {    //stop상태 -> move상태로 변환
            chk4 = 1;
        }
        dir_leg2 = 1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 6)       //주메뉴에서 exit 선택한 경우
        exit(0);                //종료

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}

//KeyBoard Callback 함수
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'S':   //움직이는 신체가 멈춤
        //타이머 함수 사용 -> 단 재귀호출x 

        //chk: 1(움직이는 상태)
        //움직이는 구조 파악 후, 움직이는 신체에서만 stop행위 실행
        if (chk0 == 1) {
            go_to = 1;
            dir_head = 0;   //움직임을 stop하기 위해 변하는 회전각도를 0으로 설정
            glutTimerFunc(40, MyTimer, 6);  //타이머 콜백함수 등록 
        }
        if (chk1 == 1) {
            go_to = 2;
            dir_arm1 = 0;   //움직임을 stop하기 위해 변하는 회전각도를 0으로 설정
            glutTimerFunc(40, MyTimer, 6);  //타이머 콜백함수 등록 
        }
        if (chk2 == 1) {
            go_to = 3;
            dir_arm2 = 0;    //움직임을 stop하기 위해 변하는 회전각도를 0으로 설정
            glutTimerFunc(40, MyTimer, 6);  //타이머 콜백함수 등록 
        }
        if (chk3 == 1) {
            go_to = 4;
            dir_leg1 = 0;    //움직임을 stop하기 위해 변하는 회전각도를 0으로 설정
            glutTimerFunc(40, MyTimer, 6);  //타이머 콜백함수 등록 
        }
        if (chk4 == 1) {
            go_to = 5;
            dir_leg2 = 0;   //움직임을 stop하기 위해 변하는 회전각도를 0으로 설정
            glutTimerFunc(40, MyTimer, 6);  //타이머 콜백함수 등록 
        }
        break;
    case 'R':
    case 'r':
        //양팔과 양다리 움직이게 설정 
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}


void MyInit(void) {
    GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };     //전역 주변반사

    GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };     //0번 광원 특성
    GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };     //1번 광원 특성
    GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 };
    GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };    //물체 특성
    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat material_specular[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 25.0 };

    glShadeModel(GL_SMOOTH);    //구로 셰이딩
    glEnable(GL_DEPTH_TEST);    //깊이 버퍼 활성화
    glEnable(GL_LIGHTING);      //조명 활성화

    glEnable(GL_LIGHT0);        //0번 광원 활성화
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);       //0번 광원 특성할당
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    glEnable(GL_LIGHT1);        //1번 광원 활성화
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);       //1번 광원 특성할당
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);   //물체 특성할당
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //전역주변반사
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //근접시점
   
    //주메뉴 생성 
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    //현재 pop-up menu에 메뉴 항목 추가 
    glutAddMenuEntry("Move head", 1);
    glutAddMenuEntry("Move right arm", 2);
    glutAddMenuEntry("Move left arm", 3);
    glutAddMenuEntry("Move right leg", 4);
    glutAddMenuEntry("Move left leg", 5);
    glutAddMenuEntry("Exit", 6);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //마우스 오른쪽 버튼 누르면, 현 메뉴가 팝업됨
}


//Display Callback 함수
void MyDisplay(void) {
    GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 1.0 };      //0번 광원위치

    GLfloat LightPosition1[] = { 1.0, 1.0, 1.0, 1.0 };      //1번 광원위치
    GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };       //1번 광원 방향
    GLfloat SpotAngle1[] = { 20.0 };                        //1번 광원 각도

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); //몸통 생성
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
        glTranslatef(1.0, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
        glScalef(1.0, 1.2, 1.0);
        glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);      //위치성 광원
        glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);      //스포트라이트
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);   //방향
        glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);           //각도
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);                 //코사인 승수
        glutSolidCube(1.0);

        glPushMatrix(); //머리 생성 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // 원점을 기준으로 회전
            glutSolidCube(0.5);
            glPopMatrix(); //머리 end

        glPushMatrix(); //오른쪽 팔1 생성 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)arm1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 팔2 end
            glPopMatrix();  //오른쪽 팔1 end

        glPushMatrix(); //왼쪽 팔1 생성 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)arm2, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //왼쪽 팔2 end
            glPopMatrix();  //왼쪽 팔1 end


        glPushMatrix(); //오른쪽 다리1 생성 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)leg1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 다리2 end
            glPopMatrix();  //오른쪽 다리1 end

        glPushMatrix(); //왼쪽 다리1 생성 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)leg2, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //왼쪽 다리2 end
            glPopMatrix();  //왼쪽 다리1 end
        glPopMatrix();  //몸통 end 

    glutSwapBuffers();
}


//Reshape Callback 함수
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Can Robot Modeling");
    MyInit();

    //Callback 함수 등록 
    glutDisplayFunc(MyDisplay);     //Display Callback 함수
    glutReshapeFunc(MyReshape);     //Reshape Callback 함수
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback 함수
    glutMainLoop();
    return 0;
}