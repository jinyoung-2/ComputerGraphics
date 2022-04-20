/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    ?  실습과제4에서 계층적 모델링 기법을 통해 구현한 <전신캔로봇>모델을 선택하여 다양한 시점에서 모델링된 객체를 관찰할 수 있게한다.
    ?  Special KeyBoard key인 F1을 누르면, 제자리 원상태로 돌아오도록 설정한다. 따라서, 다양한 시점에서 모델링된 객체를 관찰한 후 원래상태로 돌아오고 싶을 때 F1을 누른다.  
    ?  KeyBoard key마다 glutLookAt( )의 인자값을 변경시킨다.
    ?  Menu마다 움직이는 모습을 잘 보이게 시점을 변경시킨다. 

    기능:
    ?  Menu callback()을 호출하여 메뉴 선택에 따른 동작을 실행시킨다.
    ?  Keyboard Callback함수를 이용하여 해당 keyboard key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다.
    ?  glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
    ?  glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
    ?  glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.
    ?  Timer Callback 함수 마지막 부분에 glutTimerFunc()를 호출하여 계속해서 타이머 이벤트를 인의적으로 발생시킨다.
        이유: GLUT 타이머는 단 한번만 타이머 이벤트를 발생시킨다.

    ?  glutLookAt()함수를 이용하여 Camera의 위치 & Camera가 가리키는 초점의 위치 & Camera의 기울임을 변경시켜 시점좌표계를 새로 설정한다.

*/
/************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

static int body = 0, head = 0, arm1 = 0, arm2 = 0, leg1 = 0, leg2 = 0;  //회전 각도 
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //상황에 따라 기존 회전 각도에 연산할 각도 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop임을 전달하기 위해 필요한 변수 
static int go_to = -1;

GLfloat cx = 0.0, cy = 0.0, cz = 0.0, fx = 0.0, fy = 0.0, fz = 0.0, ux = 0.0, uy = 0.0, uz = 0.0;   //glutLookAt()함수의 인자 변화를 위해 정적변수 사용

// 발판 그리기
void DrawGround()
{
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

//Timer Callback 함수
void MyTimer(int value)
{
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

        //카메라 위치와 초점위치를 변경시켜 움직이는 로봇을 바라보기
        cy = cy + 0.01;
        fy = fy + 0.01;

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

        //카메라 위치를 변경시켜 움직이는 오른쪽팔 방향으로 로봇을 바라보기 
        cz = cz - 0.001;
        cy = cy + 0.1;
        cx = cx - 0.15;

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

        //카메라 위치를 변경시켜 움직이는 왼쪽팔 방향으로 로봇을 바라보기 
        cz = cz - 0.001;
        cy = cy + 0.1;
        cx = cx + 0.15;

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

        //카메라 위치를 변경시켜 움직이는 오른쪽다리 방향으로 로봇을 바라보기 
        cz = cz + 0.001;
        cy = cy - 0.1;
        cx = cx - 0.15;

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

        //카메라 위치를 변경시켜 움직이는 왼쪽다리 방향으로 로봇을 바라보기 
        cz = cz + 0.001;
        cy = cy - 0.1;
        cx = cx + 0.15;

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


        // Camera의 X축 좌표가 0.1씩 연속적으로 증가  
    case 'q':
    case 'Q':
        cx += 0.1;
        break;

        // Camera의 X축 좌표가 0.1씩 연속적으로 감소
    case 'w':
    case 'W':
        cx -= 0.1;
        break;

        // Camera의 Y축 좌표가 0.1씩 연속적으로 증가
    case 'e':
    case 'E':
        cy += 0.1;
        break;

        // Camera의 Y축 좌표가 0.1씩 연속적으로 감소
    case 'r':
    case 'R':
        cy -= 0.1;
        break;

        // Camera의 Z축 좌표가 0.1씩 연속적으로 증가 
    case 'd':
    case 'D':
        cz += 0.1;
        break;

        // Camera의 Z축 좌표가 0.1씩 연속적으로 감소
    case 'f':
    case 'F':
        cz -= 0.1;
        break;

        // 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 증가 
    case 't':
    case 'T':
        fx += 0.1;
        break;

        // 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 감소
    case 'y':
    case 'Y':
        fx -= 0.1;
        break;

        // 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 증가
    case 'u':
    case 'U':
        fy += 0.1;
        break;

        // 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 감소
    case 'i':
    case 'I':
        fy -= 0.1;
        break;

        // 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 증가
    case 'o':
    case 'O':
        fz += 0.1;
        break;

        // 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 감소
    case 'p':
    case 'P':
        fz -= 0.1;
        break;

        // Camera 기울임의 X축 좌표가 0.1씩 연속적으로 증가  
    case 'z':
    case 'Z':
        ux += 0.1;
        break;

        // Camera 기울임의 X축 좌표가 0.1씩 연속적으로 감소 
    case 'x':
    case 'X':
        ux -= 0.1;
        break;

        // Camera 기울임의 Y축 좌표가 0.1씩 연속적으로 증가 
    case 'c':
    case 'C':
        uy += 0.1;
        break;

        // Camera 기울임의 Y축 좌표가 0.1씩 연속적으로 감소 
    case 'v':
    case 'V':
        uy -= 0.1;
        break;

        // Camera 기울임의 Z축 좌표가 0.1씩 연속적으로 증가 
    case 'b':
    case 'B':
        uz += 0.1;
        break;

        // Camera 기울임의 Z축 좌표가 0.1씩 연속적으로 감소 
    case 'n':
    case 'N':
        uz -= 0.1;
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);

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
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   // << 이것을 하지 않으면 호출될때마다 누적될 수 있으니 주의하기!


    //시점변환
    gluLookAt(0.0 + cx, 0.0 + cy, 3.5 + cz, 0.0 + fx, 0.0 + fy, 0.0 + fz, 0.0 + ux, 1.0 + uy, 0.0 + uz);      //Camera가 가리키는 초점의 위치 변화를 위해 변수 사용

    DrawGround();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);

      glPushMatrix(); //몸통 생성
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
        glTranslatef(1.0, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
        glScalef(1.0, 1.2, 1.0);
        glutWireCube(1.0);

        glPushMatrix(); //머리 생성 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // 원점을 기준으로 회전
            glutWireCube(0.5);
            glPopMatrix(); //머리 end

        glPushMatrix(); //오른쪽 팔1 생성 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)arm1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.5, 0.8, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //오른쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutWireCube(0.5);
                glPopMatrix();  //오른쪽 팔2 end
            glPopMatrix();  //오른쪽 팔1 end
            
        glPushMatrix(); //왼쪽 팔1 생성 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)arm2, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.5, 0.8, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //왼쪽 팔2 생성
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.0, -0.2, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutWireCube(0.5);
                glPopMatrix();  //왼쪽 팔2 end
            glPopMatrix();  //왼쪽 팔1 end
  

        glPushMatrix(); //오른쪽 다리1 생성 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)leg1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.6, 0.9, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //오른쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutWireCube(0.5);
                glPopMatrix();  //오른쪽 다리2 end
            glPopMatrix();  //오른쪽 다리1 end

        glPushMatrix(); //왼쪽 다리1 생성 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot 지정 및 객체 이동
            glRotatef((GLfloat)leg2, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
            glScalef(0.6, 0.9, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //왼쪽 다리2 생성
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot 지정 및 객체 이동
                glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
                glutWireCube(0.5);
                glPopMatrix();  //왼쪽 다리2 end
            glPopMatrix();  //왼쪽 다리1 end
        glPopMatrix();  //몸통 end 

    glutSwapBuffers();
}


// Camera의 위치 변화에 따른 기능 수행  => glutLookAt()함수의 인자 중 Camera 위치 부분 좌표 변화
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {

    case GLUT_KEY_F1:   // 기본 상태로 되돌아가기 
        cx = 0.0;
        cy = 0.0;
        break;

    case GLUT_KEY_UP:   //↑ : 위의 시점에서 로봇 바라보기 
        cy = 7.0;
        break;

    case GLUT_KEY_DOWN: //↓ : 아래의 시점에서 로봇 바라보기         
        cy = -7.0;
        break;

    case GLUT_KEY_LEFT: // ← : 오른쪽 옆의 시점에서 로봇 바라보기 
        cx = -7.0;
        break;

    case GLUT_KEY_RIGHT:// → : 왼쪽 옆의 시점에서 로봇 바라보기 
        cx = 7.0;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}


//Reshape Callback 함수
void MyReshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);        // 투영 행렬 스택 사용
    glLoadIdentity();                   // 행렬 초기화(CTM을 I로 설정)
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ModelView");
    MyInit();

    //Callback 함수 등록 
    glutDisplayFunc(MyDisplay);     //Display Callback 함수
    glutReshapeFunc(MyReshape);     //Reshape Callback 함수
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback 함수
    glutSpecialFunc(MySpecialKeyboard); //Sepcial KeyBoard Callback 함수 
    glutMainLoop();
    return 0;
}
