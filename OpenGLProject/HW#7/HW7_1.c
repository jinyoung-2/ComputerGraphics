/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    - 실습과제4에서 계층적 모델링을 통해 구현한 <전신캔로봇>을 다음과 같은 기능이 수행되도록 추가 구현하시오.
    - <R 또는 r 키를 누르면> 양팔과 양다리를 적절히 움직여 달리는 모습이 되게하시오.
    - 로봇에 조명을 입히시오.
    
    기능:
    - Keyboard Callback함수를 이용하여 'R' 또는 'r'을 눌렀을 경우 달리는 모습이 나타나도록 한다.
    - glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
    - glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
    - glutSwapBuffers()를  glutTimerFunc()를 호출하여 계속해서 타이머 이벤트를 인의적으로 발생시킨다.
        이유: GLUT 타이머는 단 한번만 타통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.
    - Timer Callback 함수 마지막 부분에이머 이벤트를 발생시킨다.
    - 조명 효과를 구현하여 객체의 입체감, 사실감을 표현한다.
*/
/************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

static int body = 0, head = 0;
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //상황에 따라 기존 회전 각도에 연산할 각도 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop임을 전달하기 위해 필요한 변수 
static int go_to = -1;

static double time = 0;  // 달리기할 때 사용하는 변수
GLfloat rightArm1 = 0;      // 오른쪽 어깨
GLfloat rightArm2 = 0;      // 오른쪽 팔
GLfloat leftArm1 = 0;       // 왼쪽 어깨
GLfloat leftArm2 = 0;       // 왼쪽 팔
GLfloat rightLeg1 = 0;      // 오른 허벅지
GLfloat rightLeg2 = 0;      // 오른 종아리
GLfloat leftLeg1 = 0;       // 왼 허벅지
GLfloat leftLeg2 = 0;       // 왼 종아리


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
        rightArm1 += dir_arm1;       //새로운 각도
        //회전 범위
        if (rightArm1 <= -45)
            dir_arm1 = 1;
        else if (rightArm1 >= 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
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
        leftArm1 += dir_arm2;       //새로운 각도
        //회전 범위
        if (leftArm1 >= 45)
            dir_arm2 = -1;
        else if (leftArm1 == 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
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
        rightLeg1 += dir_leg1;       //새로운 각도
        //회전 범위
        if (rightLeg1 <= -45)
            dir_leg1 = 1;
        else if (rightLeg1 == 0) {  //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
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
        leftLeg1 += dir_leg2;       //새로운 각도
        //회전 범위
        if (leftLeg1 >= 45)
            dir_leg2 = -1;
        else if (leftLeg1 == 0) {   //처음위치일 경우 chk관련 변수의 값을 -1로 지정(move->stop으로 변환)
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
    else if (value == 7) {
        time = time + 0.1;
        glLoadIdentity();

        /*
        로봇의 움직임 가속도 : sin() 함수 통해 표현함
        관절의 제한범위 : abs() 함수 통해 제한함
        */
        body = -fabs(sin(time) * 10 + 5);           //몸통 각도조절(abs절대값을 줌으로써 몸통이 뒤로꺾이지 않는 한계점을 설정) 
        head = -fabs(sin(time) * 60 + 50);          //머리 각도조절(abs절대값을 줌으로써 머리가 뒤로꺾이지 않는 한계점을 설정) 

        leftArm1 = sin(time) * 60;                  //왼팔은 60도 각도까지 움직이도록 설정 & sin()함수를 사용하여 주기적인 움직임 설정
        rightArm1 = leftArm1;                       //오른팔은 왼팔반대로 60도각도까지 움직이도록 설정 & sin()함수를 사용하여 주기적인 움직임 설정.
        rightArm2 = -fabs(sin(time) * 60 + 50);     //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
        leftArm2 = -fabs(-sin(time) * 60 + 50);     //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

        rightLeg2 = fabs(-sin(time) * 30 - 30);     //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
        leftLeg2 = fabs(sin(time) * 30 - 30);       //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
        rightLeg1 = sin(time) * 60;                 //우측다리는 60도 각도까지 움직이도록 설정 & sin()함수를 사용하여 주기적인 움직임 설정
        leftLeg1 = rightLeg1;                       //좌측다리는 우측다리반대로 60도 각도까지 움직이도록 설정 & sin()함수를 사용하여 주기적인 움직임 설정

        glutPostRedisplay();
        glutSwapBuffers();

        glutTimerFunc(200, MyTimer, 7);

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
        glutTimerFunc(200, MyTimer, 7); //타이머 함수
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// 초기화 
void MyInit(void) {
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.3, 0, 0, 1.0 };          //미약한 적색광 추가 
    //GLfloat local_view[] = { 0.0 }; 

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    //광원 특성 설정 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //조명 모델 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //전역 주변 광원 색 조절
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //관찰자 시점위치 

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
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
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_ambient_color[] = { 0.7, 0.6, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.2, 0.6, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.5, 0.1, 0.2, 0.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.0,0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.2);	//시점변환
    glPushMatrix(); //몸통 생성
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
        glTranslatef(1.0, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
        glScalef(1.0, 1.2, 1.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);             //주변광 계수: 주변 반사에 대한 물체색
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);        //난반사광 계수: 난반사에 대한 물체색
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);            //정반사광 계수: 정반사에 대한 물체색 
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);     //정반사의 광택 계수
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);            //물체의 발광색 
        glutSolidCube(1.0);

        glPushMatrix(); //머리 생성 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // 원점을 기준으로 회전
            glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPopMatrix(); //머리 end

        glPushMatrix(); //오른쪽 팔1 생성 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            //glRotatef((GLfloat)rightArm1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glRotatef(rightArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(rightArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
                glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 팔2 end
            glPopMatrix();  //오른쪽 팔1 end

        glPushMatrix(); //왼쪽 팔1 생성 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            //glRotatef((GLfloat)leftArm1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glRotatef(leftArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(leftArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
                glutSolidCube(0.5);
                glPopMatrix();  //왼쪽 팔2 end
            glPopMatrix();  //왼쪽 팔1 end


        glPushMatrix(); //오른쪽 다리1 생성 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            //glRotatef((GLfloat)rightLeg1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glRotatef(rightLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(rightLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
                glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 다리2 end
            glPopMatrix();  //오른쪽 다리1 end

        glPushMatrix(); //왼쪽 다리1 생성 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            //glRotatef((GLfloat)leftLeg1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glRotatef(leftLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(leftLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
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
