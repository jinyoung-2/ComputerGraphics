/*************************************************************************/
/*				       HW#2-1.  GL Modeling                              */
/*
	문제 정의 :
	GL Modeling을 하여 2D Primitives를 구현한다.  

	기능:
	GL Library를 이용하며, z값을 0으로 지정하여 2D Primitives를 구현한다. 
	구현한 2D Primitives들은 Points, Lines, LineStrip, LineLoop, TrangleFan, Triangles, TriangleStrip, Polygons, Quads, QuadStrip이다. 
	glBegin()함수의 인자에 따라 꼭지점들을 해석하는 방법이 달라진다. 
	가시부피를 설정하는 투영변환함수를 호출하지 않고, 기본 default값으로 정규화 가시부피를 이용한다.  
*/
/**************************************************************************/


#include <gl/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	//윈도우에서 그림 제거로, 화면을 깨끗하게 지움 
	glColor3f(0,0,1);				//3차원에서 vertex를 파란색으로 지정
	glPointSize(5.0);				//폰트사이즈 지정
	//glLineWidth(5.0);				//선의 굵기 지정

	//새로운 2차원 Primitives 출력(표시)
	//Points
	glBegin(GL_POINTS);				//각 Vertex들을 하나의 Point로 표현한다.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();
	
	//Lines
	glBegin(GL_LINES);				//Vertex들을 순서대로 두 개씩 묶어서 Line을 만든다.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//LineStrip
	glBegin(GL_LINE_STRIP);			//Line들을 한 줄로 연결한다.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//LineLoop
	glBegin(GL_LINE_LOOP);			//마지막 Vertex와 첫 번째 Vertex를 연결하는 Line이 추가된 GL_LINE_STRIP
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//Triangles
	glBegin(GL_TRIANGLES);			//세 개의 Vertex를 묶어서 삼각형을 만든다. 
	glVertex3f(-0.3, -0.4, 0.0); glVertex3f(0.25, -0.6, 0.0);
	glVertex3f(0.5, 0.3, 0.0); glVertex3f(0.35, 0.45, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.6, -0.2, 0.0);
	glEnd();

	//TriangleStrip
	glBegin(GL_TRIANGLE_STRIP);		//삼각형들을 길게 연결한다.
	glVertex3f(0.6, -0.4, 0.0); glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.2, -0.1, 0.0); glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-0.25, -0.3, 0.0); glVertex3f(-0.5, 0.2, 0.0);
	glVertex3f(-0.8, -0.3, 0.0);
	glEnd();

	//TrangleFan
	glBegin(GL_TRIANGLE_FAN);		//삼각형들을 부채 모양으로 연결한다.
	glVertex3f(-0.5, -0.3, 0.0); glVertex3f(0.8, -0.1, 0.0);
	glVertex3f(0.65, 0.1, 0.0); glVertex3f(0.6, 0.25, 0.0);
	glVertex3f(0.15, 0.55, 0.0); glVertex3f(-0.15, 0.6, 0.0);
	glEnd();

	//Polygons
	glBegin(GL_POLYGON);			//단순, 볼록한 다각형
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//Quads
	glBegin(GL_QUADS);				//Vertex들을 네 개씩 묶어서 만든 네 개의 모서리를 가진 다각형을 만든다.
	glVertex3f(0.2,-0.2,0.0); glVertex3f(0.3, 0.05, 0.0);
	glVertex3f(0.15, 0.2, 0.0); glVertex3f(-0.1, -0.15, 0.0);
	glVertex3f(-0.25, 0.15, 0.0); glVertex3f(-0.2,0.45, 0.0);
	glVertex3f(-0.35, 0.4, 0.0); glVertex3f(-0.5, 0.2, 0.0);
	glEnd();

	//QuadStrip
	glBegin(GL_QUAD_STRIP);			//사각형들을 길게 연결한다. 
	glVertex3f(0.2,-0.2,0.0); glVertex3f(0.3, 0.05, 0.0);
	glVertex3f(-0.1, -0.15, 0.0); glVertex3f(0.15, 0.2, 0.0);
	glVertex3f(-0.25, 0.15, 0.0); glVertex3f(-0.2,0.45, 0.0);
	glVertex3f(-0.5, 0.2, 0.0);  glVertex3f(-0.35, 0.4, 0.0);
	glEnd();

	glFlush();						//아직 실행되지 않은 명령 모두 실행하도록 한다. 
}

int main(int argc, char** argv)
{
	//Window 초기화 및 생성
	glutInit(&argc, argv);			//Window OS와 Session 연결 및 GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB);	//display mode 설정 && RGB
	glutInitWindowSize(500, 500);	//Window 크기 설정 => x축방향의 크기=500, y축 방향의 크기=500으로 설정
	glutInitWindowPosition(0, 0);	//Monitor에서 Window의 시작점 위치 설정
	glutCreateWindow("Show 2D Primitives");	//title를 인자로 갖는 새로운 Window 생성
	glClearColor(1, 1, 1, 0);		//Window 창 생성시 바탕색을 투명한 검정색으로 지정

	//Callback 함수 등록 
	glutDisplayFunc(MyDisplay);		//Display Callback함수 등록

	//이벤트 루프로 진입 
	glutMainLoop();	//glutMainLoop(): GLUT Event 처리 Loop 입력 
	return 0;		//종료
}