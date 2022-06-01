/*************************************************************************/
/*				   HW#8   : 계층적 모델링을 이용한 수박 로봇 구현        */
/*													                     */
/*
    문제 정의 :
    - 지금까지 배운 OpenGL의 다양한 기술을 이용하여 수박 로봇 객체를 구현한다. 

    기능:
    1. 메뉴기능을 통해 로봇의 신체(머리, 몸통, 양팔, 양다리)를 움직일 수 있도록 한다.
    2. 키보드 입력을 통해 움직이는 로봇의 신체를 멈추게 하고, 로봇이 달리도록 하고, 시점변환을 할 수 있도록 한다.
    3. 조명기능을 통해 프로그램이 처음 실행될 때, 로봇이 움직이면서 조명에 의해 밝아지도록 한다.
    4. Texture Mapping 기능을 통해 로봇에 수박 패턴 이미지를 적용한다.
*/
/************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>
#include <stdio.h>

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")


static int body = 0, head = 0;
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //상황에 따라 기존 회전 각도에 연산할 각도 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;                   //stop임을 전달하기 위해 필요한 변수 
static int go_to = -1;

static double time = 0;     // 달리기할 때 사용하는 변수
GLfloat rightArm1 = 0;      // 오른쪽 어깨
GLfloat rightArm2 = 0;      // 오른쪽 팔
GLfloat leftArm1 = 0;       // 왼쪽 어깨
GLfloat leftArm2 = 0;       // 왼쪽 팔
GLfloat rightLeg1 = 0;      // 오른 허벅지
GLfloat rightLeg2 = 0;      // 오른 종아리
GLfloat leftLeg1 = 0;       // 왼 허벅지
GLfloat leftLeg2 = 0;       // 왼 종아리

// 프로그램 실행시, 로봇의 움직임 제한하는 변수 
GLfloat transRightArm = -0.1;       // 오른쪽 어깨
GLfloat transLeftArm = 0.1;         // 왼쪽 어깨
GLfloat transRightLeg = -0.05;      // 오른쪽 허벅지
GLfloat transLeftLeg = 0.05;        // 왼쪽 허벅지

// 조명 조절 변수 
GLfloat rx = 0.0, gx = 0.0, bx = 0.0;

//뷰폿별 Camera위치 조절변수
GLfloat cx = 0.0, cy = 0.0, cz = 0.0;


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
        
        if (time <= 30.0){
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

            glutTimerFunc(100, MyTimer, 7);
        }
        else {      //초기상태로 돌아가게 설정 
            body = 0.0;
            head = 0.0;
            rightArm1 = 0.0;
            rightArm2 = 0.0;
            leftArm1 = 0.0;
            leftArm2 = 0.0;
            rightLeg1 = 0.0;
            rightLeg2 = 0.0;
            leftLeg1 = 0.0;
            leftLeg2 = 0.0;
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
    else if (entryID == 6) {
        head = 0.0;
        body = 0.0;
        rightArm1 = 0.0;
        rightArm2 = 0.0;
        leftArm1 = 0.0;
        leftArm2 = 0.0;
        rightLeg1 = 0.0;
        rightLeg2 = 0.0;
        leftLeg1 = 0.0;
        leftLeg2 = 0.0;
    }
    else if (entryID == 7)       //주메뉴에서 exit 선택한 경우
        exit(0);                //종료

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}

//KeyBoard Callback 함수
void MyKeyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'S':   //움직이는 신체가 멈춤
    case 's':
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
        time = 0.0;
        glutTimerFunc(200, MyTimer, 7); //타이머 함수
        break;
    case 'z':   // Camera의 X축 좌표가 0.1씩 연속적으로 증가  
    case 'Z':
        if (cx <= 2.7)
            cx += 0.1;
        break;
    case 'x':   // Camera의 X축 좌표가 0.1씩 연속적으로 감소
    case 'X':
        if (cx >= -2.7)
            cx -= 0.1;
        break;
    case 'c':   // Camera의 Y축 좌표가 0.1씩 연속적으로 증가
    case 'C':
        if (cy <= 2.7)
            cy += 0.1;
        break;
    case 'v':   // Camera의 Y축 좌표가 0.1씩 연속적으로 감소
    case 'V':
        if (cy >= -2.7)
            cy -= 0.1;
        break;
    case 'b':   // Camera의 Z축 좌표가 0.1씩 연속적으로 증가 
    case 'B':
        if (cz <= 2.0)
            cz += 0.1;
        break;  
    case 'n':   // Camera의 Z축 좌표가 0.1씩 연속적으로 감소  
    case 'N':
        if (cz >= -2.0)
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

// 자동 Texture Mapping 
AUX_RGBImageRec* LoadBMP(char* Filename) {
    FILE* File = NULL;
    if (!Filename) return NULL;
    fopen_s(&File, Filename, "r");

    // seFilename을 유니코드 스트링으로 바꾸기
    int size = strlen(Filename);
    wchar_t* w_Filename = new wchar_t[size];

    for (int i = 0; i < size; ++i)  w_Filename[i] = Filename[i];
    w_Filename[size] = NULL;

    if (File) {
        fclose(File);
        return auxDIBImageLoad(w_Filename);     //파일로부터 메모리로
    }
    return NULL;
}

int Texture() {
    int Status = FALSE;
    AUX_RGBImageRec* TxtImg[1];
    memset(TxtImg, 0, sizeof(void*) * 1);

    if (TxtImg[0] = LoadBMP((char*)"fruit.bmp")) {
        Status = TRUE;

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TxtImg[0]->sizeX, TxtImg[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TxtImg[0]->data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    }

    if (TxtImg[0]) {
        if (TxtImg[0]->data) {
            free(TxtImg[0]->data);
        }

        free(TxtImg[0]);
    }

    return Status;
}

// 초기화 
void MyInit(void) {
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.3, 0, 0, 1.0 };          //미약한 적색광 추가 

    Texture();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
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
    glutAddMenuEntry("Initialize", 6);
    glutAddMenuEntry("Exit", 7);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //마우스 오른쪽 버튼 누르면, 현 메뉴가 팝업됨
}


// 프로그램 실행시 초기 조명에 대한 함수 
void MyTimer2(int value) {
    rx += 0.01;
    gx += 0.01; 
    bx += 0.01;
    if(rx <=3.0)
        glutTimerFunc(300, MyTimer2, value);

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}


// 프로그램 실행시 초기 로봇의 움직임에 대한 함수 
void MyTimer3(int value) {
    if (rightArm1 == 1.0) {
        transRightArm = -0.1;      // 오른쪽 어깨
        transLeftArm = 0.1;        // 왼쪽 어깨
        transRightLeg = -0.05;      // 오른쪽 허벅지
        transLeftLeg = 0.05;        // 왼쪽 허벅지
    }
    else if (rightArm1 == -1.0) {
        transRightArm = 0.1;
        transLeftArm = -0.1;
        transRightLeg = 0.05;      // 오른쪽 허벅지
        transLeftLeg = -0.05;        // 왼쪽 허벅지
    }


    //경계에 부딪히지 않고, 경계 사이에서 이동하는 경우 
    rightArm1 += transRightArm;
    leftArm1 += transLeftArm;
    rightLeg1 += transRightLeg;
    leftLeg1 += transLeftLeg;

    if(rx <= 0.8)
        glutTimerFunc(20, MyTimer3, value);

    glutPostRedisplay();        //Display Event 강제 발생시킴 
}

//Display Callback 함수
void MyDisplay(void) {

    GLfloat no_mat[] = { 0.0 + rx, 0.0 + gx, 0.0 + bx, 1.0 };
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

    gluLookAt(1.0+cx,0.5+cy, 5.0+cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.2);	//시점변환
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
            glutSolidCube(0.5);
            glPopMatrix(); //머리 end

        glPushMatrix(); //오른쪽 팔1 생성 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef(rightArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(rightArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 팔2 end
            glPopMatrix();  //오른쪽 팔1 end

        glPushMatrix(); //왼쪽 팔1 생성 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef(leftArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(leftArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //왼쪽 팔2 end
            glPopMatrix();  //왼쪽 팔1 end


        glPushMatrix(); //오른쪽 다리1 생성 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef(rightLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //오른쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(rightLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutSolidCube(0.5);
                glPopMatrix();  //오른쪽 다리2 end
            glPopMatrix();  //오른쪽 다리1 end

        glPushMatrix(); //왼쪽 다리1 생성 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef(leftLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //왼쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glRotatef(leftLeg2, 0.0, 0.0, 1.0);
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
    glutTimerFunc(2000,MyTimer2,1); //조명 Timer Callback 함수
    glutTimerFunc(2000, MyTimer3, 1);   //움직임 Timer Callback 함수
    glutMainLoop();
    return 0;
}