/****************************************************/
/*													*/
/*
	문제 정의 :
	3D Sierpinski Gasket 구현 및 Reshape callback을 사용하여 물체의 왜곡문제 해결

	기능: 
	glOrtho() 투영변환함수를 이용하여 가시부피 안에 있는 객체들을 투영면 Z=0인 평면에 그린다.
	glViewport()를 이용하여 화면상의 뷰폿의 위치와 크기를 설정한다. 
	Reshape callback을 이용하여 새로고침된 Window상의 viewport위치와 크기를 입력받아, 가시부피의 종횡비와 동일하게 설정하여 왜곡문제를 해결한다.
*/
/***************************************************/




//2D 삼각형 -> 3D 사면체로 확장 
#include <gl/glut.h>
#include <stdlib.h>		//rand()함수 사용용도 
#include <math.h>

//Display Callback 함수 
void MyDisplay() {	
	float vertices[4][3] = { {0,0,0},{0,300,300},{300,0,300},{300,300,0} };		//3차원 4개의 정점 생성(정육면체의 꼭지점을 연결한 선분을 이어 정사면체 생성)
	float p[3] = {100,70,100 };		// 점 P의 위치
	int i, j;
	
	glClear(GL_COLOR_BUFFER_BIT);	//glClear(): 윈도우에서 그림 제거로, 화면을 깨끗하게 지움 

	for (j = 0; j < 50000; j++) {
		i = rand() % 4;				//V0,V1,V2,V3 4개의 정점 중 임의 선택

		//새로 선택된 점과 현재 점을 기준으로 새로운 점 위치 계산
		p[0] = (p[0] + vertices[i][0]) / 2.0;
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;

		//기하 프리미티브: 가상의 공간을 구성하는 각 객체물체를 표현하는데 있어 가장 기본이 되는 요소
		//새로운 3차원 점 출력(표시)
		glBegin(GL_POINTS);			  
			glVertex3fv(p);	
		glEnd();
	}
	glFlush();	//glFlush(): 아직 실행되지 않은 명령 모두 실행하도록 함 
}

//뷰포트 변환
// viewport: 그림이 그려지는 디스플레이 장치에서의 사각 영역 
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);						//glviewport(x,y,width,height): (x,y)위치에서 width*height영역에 이미지 출력
	
	//새로운 width, height의 비율 구하기 
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;
	
	glMatrixMode(GL_PROJECTION);		//투영행렬스택으로 변환(for 투영변환함수들을 원래의 목적대로 사용)
	glLoadIdentity();					//현재 projection 행렬 초기화(항등행렬)
	//가시부피와 viewport의 종횡비를 일치시켜 왜곡방지
	glOrtho(-100.0 * Widthfactor, 500.0 * Widthfactor, -100.0 * Heightfactor, 500.0 * Heightfactor, 30.0, -300.0);

	//해당 축을 기준으로 degree만큼 회전 
	glRotatef(-30.0, 1.0, 0.0, 0.0);
	glRotatef(-40.0, 0.0, 0.0, 1.0);
}


void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);	//glClearColor(): window 창 생성시 바탕색을 불투명한 흰색으로 지정
	glColor3f(1.0, 0.0, 0.0);			//3차원에서 vertex를 빨간색으로 지정	
}

int main(int argc, char** argv) 
{
	//Window 초기화 및 생성
	glutInit(&argc, argv);			//glutInit(): Window OS와 Session 연결 및 GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB);	//glutInitDisplayMode(): display mode 설정 && GLUT_RGB : GLUT_RGBA를 위한 Alias
	glutInitWindowSize(500, 500);	//Window 크기 설정 => x축방향의 크기=500, y축 방향의 크기=500으로 설정
	glutInitWindowPosition(0, 0);	//Monitor에서 Window의 시작점 위치 설정
	glutCreateWindow("Show 3D Sierpinski Gasket");	//title를 인자로 갖는 새로운 Window 생성
	
	//Callback 함수 등록 
	glutDisplayFunc(MyDisplay);		//Display Callback함수 등록
	glutReshapeFunc(MyReshape);		//Reshape Callback함수 등록 
	MyInit();

	//이벤트 루프로 진입 
	glutMainLoop();	//glutMainLoop(): GLUT Event 처리 Loop 입력 
	return 0;		//종료
}