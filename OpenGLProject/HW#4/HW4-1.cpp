/*************************************************************************/
/*													                     */
/*
	문제 정의 :
	• 각 손가락 당 관절은 2개 이상

	• 기본 필수 기능
	 <1 키를 누르면> 첫번째 손가락을 접었다 펼쳤다 반복
	 <2 키를 누르면> 두번째 손가락을 접었다 펼쳤다 반복
	 <3 키를 누르면> 세번째 손가락을 접었다 펼쳤다 반복
	 <4 키를 누르면> 모든 손가락이 접었다 펼쳤다 반복
	 <S 키를 누르면> 움직이던 손가락이 움직임을 멈춤

	• 추가 선택 기능
	 <마우스 왼쪽 버튼을 클릭하면> 어깨, 팔꿈치 및 모든 손가락을 움직여서 Robot Arm이 특정 물건을 잡는 것처럼 회전
	 <마우스 오른쪽 버튼을 클릭하면> 팔꿈치 및 모든 손가락을 움직여서 Robot Arm의 원래 위치와 자세로 되돌아가도록 함.

	조건:
	• 위의 모든 조건들의 회전 각도는 0 ~ 180 범위로 제한
	• Cube가 아닌 Cylinder, Cone 등으로 Robot Arm을 다양한 Modeling 함수를 사용하여 모델링해도 좋음

	기능:
	• Keyboard Callback함수를 이용하여 해당 keyboard key를 눌렀을 경우 각각에 맞는 동작이 실행되도록 한다.
	• Mouse Callback함수를 이용하여 mouse의 button위치와 state에 따라 각각에 맞는 동작이 실행되도록 한다.
	• glutPostdisplay()를 호출하여 각각의 event 발생시 변동된 사항이 강제적으로 적용되도록 한다.
	• glutInitDisplayMode()의 인자로 GLUT_DOUBLE을 이용한다. Double buffering을 이용하여 single buffering의 문제점인 유령효과를 해결한다.
	• glutSwapBuffers()를 통해 상황에 따라 back buffer를 front buffer로 전환한다. Display function의 끝에 추가한다.
	• Timer Callback 함수 마지막 부분에 glutTimerFunc()를 호출하여 계속해서 타이머 이벤트를 인의적으로 발생시킨다.
		이유: GLUT 타이머는 단 한번만 타이머 이벤트를 발생시킨다.

	• 행렬스택을 이용하여 로봇의 몸 구조를 표현한다. 몸 구조 중 관절 부분을 유의하며 코드를 작성한다.
*/
/**************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>

static int arm1 = 0, arm2 = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0;
static int dir_finger[3] = { 0 }, dir_arm1 = 1, dir_arm2 = 1;
static int chk_finger[3] = { -1,-1,-1 }, chk_arm[2] = { -1,-1 };

int go_stop = 0;

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}

void drawArm1() {
	glTranslatef(-1.0, 0.0, 0.0);	 // Pivot 지정 및 객체 이동
	glRotatef((GLfloat)arm1, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
	glTranslatef(1.0, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동 
	glScalef(2.0, 0.7, 1.0);
	glutWireCube(1.0);
}

void drawArm2() {
	glTranslatef(0.5, 0.0, 0.0);	// Pivot 지정 및 객체 이동
	glRotatef((GLfloat)arm2, 0.0, 0.0, 1.0); // 원점을 기준으로 회전
	glTranslatef(0.5, 0.0, 0.0);	// Pivot으로 지정할 위치를 원점으로 이동
	glutWireCube(1.0);
}

void drawFinger1() {
    glTranslatef(-0.1, 0.12, -0.5);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);// finger1-1
    glTranslatef(-0.1, 0.12, 0.0);// Pivot으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger1-1 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.15, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);// finger1-2
    glTranslatef(0.15, 0.0, 0.0);// Pivot으로 지정할 위치를 원점으로 이동
	glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger1-2 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.17, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);// finger1-3
    glTranslatef(0.17, 0.0, 0.0);// Pivot으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3);// finger1-3 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
}

void drawFinger2() {
    glTranslatef(-0.1, 0.0, -0.5);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger2, 0.0, 1.0, 0.0);// finger2-1
    glTranslatef(-0.1, 0.0, 0.0);// Pivot 으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3);// finger2-1 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.15, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger2, 0.0, 1.0, 0.0);// finger2-2
    glTranslatef(0.15, 0.0, 0.0);// Pivot으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger2-2 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.17, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger2, 0.0, 1.0, 0.0);// finger2-3
    glTranslatef(0.17, 0.0, 0.0);// Pivot으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger2-3 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
}

void drawFinger3() {
    glTranslatef(-0.1, -0.12, -0.5);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);// finger3-1
    glTranslatef(-0.1, -0.12, 0.0);// Pivot 으로 지정할 위치를 원점으로 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger3-1 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.15, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);// finger3-2
    glTranslatef(0.15, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger3-2 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
    glTranslatef(0.17, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);// finger3-3
    glTranslatef(0.17, 0.0, 0.0);// Pivot 지정 및 객체 이동
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3); // finger3-3 마디 크기 설정
        glutWireCube(1.0);		// 그리기
        glPopMatrix();
}

void MyDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(-2.0, -2.0, 0.0);
        glPushMatrix();
            drawArm1();	//shoulder
            glPushMatrix();
                drawArm2();	//elbow
                glPushMatrix(); //finger
                    glTranslatef(0.9, 0.0, 0.0);
                    glPushMatrix();
                        drawFinger1();	//finger1
                        glPopMatrix();
                    glPushMatrix();
                        drawFinger2();	//finger2
                        glPopMatrix();
                    glPushMatrix();
                        drawFinger3();	//finger3
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();  //finger 끝
            glPopMatrix();
        glPopMatrix();      // 원점으로 back 

    glutSwapBuffers();
}


void MyTimer(int value)
{
	if (value == 0)
	{
		if (go_stop == 0)			//마우스 왼쪽 버튼에 대한 Callback함수 처리: Robot Arm이 특정 물건을 잡는것처럼 회전 
		{
			arm1 += dir_arm1;
			arm2 += dir_arm2;

			if (chk_arm[0] != 1 || chk_arm[1] != 1)
			{
				//shoulder부분의 가능한 회전범위에 따른 처리 
				if (arm1 >= 60)
					dir_arm1 = -1;		//제자리로 돌아오도록 
				else if (arm1 <= 0)
					dir_arm1 = 1;		//최대각도로 움직일수 있도록 

				//elbow부분의 가능한 회전범위에 따른 처리 
				if (arm2 >= 60)
					dir_arm2 = -1;		//제자리로 돌아오도록 
				else if (arm2 <= 0)
					dir_arm2 = 1;		//최대각도로 움직일수 있도록 
			}	
			else
				return;
		

			//finger
			finger1 += dir_finger[0];
			finger2 += dir_finger[1];
			finger3 += dir_finger[2];

			//Robot Arm의 모든 구조가 최대각도일 경우 stop하도록 return처리 
			if (arm1 >= 60 || arm2 >= 60 || finger1 >= 60 || finger2 >= 60 || finger3 >= 60)
				return;


			if (chk_finger[0] != 1 || chk_finger[1] != 1 || chk_finger[2] != 1)
			{
				//finger1,2,3부분의 가능한 회전범위에 따른 처리
				if (finger1 >= 60)
					dir_finger[0] = -1;	//제자리로 돌아오도록
				else if (finger1 <= 0)
					dir_finger[0] = 1;	//최대각도로 움직일수 있도록

				if (finger2 >= 60)
					dir_finger[1] = -1;	//제자리로 돌아오도록
				else if (finger2 <= 0)
					dir_finger[1] = 1;	//최대각도로 움직일수 있도록

				if (finger3 <= -60)
					dir_finger[2] = 1;	//제자리로 돌아오도록
				else if (finger3 >= 0)
					dir_finger[2] = -1;	//최대각도로 움직일수 있도록

			}
			else
				return;

			glutTimerFunc(100, MyTimer, 0);
			glutPostRedisplay();
		}
		else if (go_stop == 1)		//마우스 오른쪽 버튼에 대한 Callback함수 처리: Robot Arm의 원래 위치와 자세로 되돌아가도록 함 
		{
			if (arm1 <= 0 || arm2 <= 0)		//stop조건에 해당하는 경우 => chk관련 변수의 값을 모두 0으로 지정하여 stop상태임을 명시
			{       
				for (int i = 0; i < 2; i++)
					chk_arm[i] = 0;
				for (int i = 0; i < 3; i++)
					chk_finger[i] = 0;
				return;
			}
			else                            //stop조건에 해당하지 않는 경우 => 계속 회전 
			{
				arm1 += dir_arm1;
				arm2 += dir_arm2;

				finger1 += dir_finger[0];
				finger2 += dir_finger[1];
				finger3 += dir_finger[2];

				glutTimerFunc(100, MyTimer, 0);
				glutPostRedisplay();
			}
		}
	}

	if (value == 1)
	{       //첫번째 손가락을 접었다 펼쳤다 반복
		if (dir_finger[0] == 0) {   //stop
			return;
		}

		finger1 += dir_finger[0];
		if (finger1 >= 60)
			dir_finger[0] = -1;
		else if (finger1 <= 0)
			dir_finger[0] = 1;

		glutTimerFunc(100, MyTimer, 1);
		glutPostRedisplay();
	}
	else if (value == 2)
	{  //두번째 손가락을 접었다 펼쳤다 반복
		if (dir_finger[1] == 0) {   //stop
			return;
		}

		finger2 += dir_finger[1];
		if (finger2 >= 60)
			dir_finger[1] = -1;
		else if (finger2 <= 0)
			dir_finger[1] = 1;

		glutTimerFunc(100, MyTimer, 2);
		glutPostRedisplay();
	}
	else if (value == 3)
	{  //세번째 손가락을 접었다 펼쳤다 반복
		if (dir_finger[2] == 0) {   //stop
			return;
		}

		finger3 += dir_finger[2];
		if (finger3 <= -60)
			dir_finger[2] = 1;
		else if (finger3 >= 0)
			dir_finger[2] = -1;

		glutTimerFunc(100, MyTimer, 3);
		glutPostRedisplay();
	}
	else if (value == 4)
	{  //모든 손가락이 접었다 펼쳤다 반복
		//finger1,2,3 모두 동일한 회전 범위를 갖는다

		finger1 += dir_finger[0];
		if (finger1 >= 60)
			dir_finger[0] = -1;
		else if (finger1 <= 0)
			dir_finger[0] = 1;


		finger2 += dir_finger[1];
		if (finger2 >= 60)
			dir_finger[1] = -1;
		else if (finger2 <= 0)
			dir_finger[1] = 1;


		finger3 += dir_finger[2];
		if (finger3 <= -60)
			dir_finger[2] = 1;
		else if (finger3 >= 0)
			dir_finger[2] = -1;


		glutTimerFunc(100, MyTimer, 4);
		glutPostRedisplay();
	}
	else if (value == 5)
	{  //움직이던 손가락이 멈춤
		//finger관련 변환회전각도를 0으로 지정 
		dir_finger[0] = 0;
		dir_finger[1] = 0;
		dir_finger[2] = 0;
		glutTimerFunc(100, MyTimer, 1);
		glutTimerFunc(100, MyTimer, 2);
		glutTimerFunc(100, MyTimer, 3);

		glutPostRedisplay();
	}
}


// Reshape Callback 함수 
void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

// Keyboard Callback 함수 
void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':   //첫번째 손가락을 접었다 펼쳤다 반복
		dir_finger[0] = -1;
		glutTimerFunc(100, MyTimer, 1);
		break;
	case '2':   //두번째 손가락을 접었다 펼쳤다 반복
		dir_finger[1] = -1;
		glutTimerFunc(100, MyTimer, 2);
		break;
	case '3':   //세번째 손가락을 접었다 펼쳤다 반복
		dir_finger[2] = 1;
		glutTimerFunc(100, MyTimer, 3);
		break;
	case '4':   //모든 손가락이 접었다 펼쳤다 반복
		dir_finger[0] = -1;
		dir_finger[1] = -1;
		dir_finger[2] = 1;
		glutTimerFunc(100, MyTimer, 4);
		break;
	case 'S':   //움직이던 손가락이 움직임을 멈춤
		glutTimerFunc(10, MyTimer, 5);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

// Mouse Callback 함수 
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {         //마우스 왼쪽 버튼 click
		// 어깨, 팔꿈치 및 모든 손가락 움직여 특정 물건을 잡는 것처럼 회전 
		go_stop = 0;

		dir_arm1 = 1;
		dir_arm2 = 1;
		dir_finger[0] = -1;
		dir_finger[1] = -1;
		dir_finger[2] = 1;

		glutTimerFunc(100, MyTimer, 0);
	}
	else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {   //마우스 오른쪽 버튼 click
		// 팔꿈치 및 모든 손가락 움직여 원래 위치와 자세로 되돌아감
		go_stop = 1;

		for (int i = 0; i < 2; i++)
			chk_arm[i] = 1;
		for (int i = 0; i < 3; i++)
			chk_finger[i] = 1;

		dir_arm1 = -1;
		dir_arm2 = -1;
		dir_finger[0] = 1;
		dir_finger[1] = 1;
		dir_finger[2] = -1;

		glutTimerFunc(100, MyTimer, 0);
	}
	glutPostRedisplay();        //Display Event 강제 발생시킴 
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();

	//Callback 함수 등록 
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMainLoop();
	return 0;
}