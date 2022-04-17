/*************************************************************************/
/*													                     */
/*
    문제 정의 :
    • 아래의 깡통 로봇의 이미지를 참고하고, 지금까지 배운 모델링 방법을 사용하여 최대한 유사하게 전신(Full Body)을 모델링
    • 차렷 자세를 초기 기본자세로 설정하여 모델링
    • 메뉴 생성
         <머리 움직이기> 
         <오른팔 움직이기>
         <왼쪽팔 움직이기>
         <오른다리 움직이기>
         <왼쪽다리 움직이기>
    • 메뉴 클릭
         해당 메뉴에 맞는 신체가 한번 움직였다가 원래 자세로 돌아옴
    • S 누르면
         움직이는 신체가 멈춤

    조건:
    • 관절의 모든 회전 각도 범위는 실체 인체와 유사하도록 함.

    기능:
    • Menu callback()을 호출하여 메뉴 선택에 따른 동작을 실행시킨다. 
    • Keyboard Callback함수를 이용하여 해당 keyboard key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다. 
    • glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
    • glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
    • glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.
    • Timer Callback 함수 마지막 부분에 glutTimerFunc()를 호출하여 계속해서 타이머 이벤트를 인의적으로 발생시킨다.
        이유: GLUT 타이머는 단 한번만 타이머 이벤트를 발생시킨다.
    
    • 행렬스택을 이용하여 로봇의 몸 구조를 표현한다. 몸 구조 중 관절 부분을 유의하며 코드를 작성한다. 
*/
/************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>

static int body = 0, head = 0, arm1 = 0, arm2 = 0, leg1 = 0, leg2 = 0;  //회전 각도 
static int dir_head=1,dir_arm1=-1,dir_arm2=1, dir_leg1=-1, dir_leg2=1;  //상황에 따라 기존 회전 각도에 연산할 각도 
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
        dir_head=-1;    
        glutTimerFunc(40, MyTimer, entryID);    //타이머 콜백함수 등록
    }
    else if (entryID == 2) {
        //오른쪽팔 움직이기
        if(chk1!=1){        //stop상태 -> move상태로 변환
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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