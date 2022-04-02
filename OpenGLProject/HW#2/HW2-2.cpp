/*************************************************************************/
/*				       HW#2-2.  GLU Modeling                             */
/*
	문제 정의 :
	GLU Modeling을 하여 3D Primitives를 구현한다. 

	기능:
	3D 공간에서 3D객체를 생성하는 Quadrics를 이용한다. 
	GLU Modeling을 하여 3D Primitives인 Sphere, Cylinder, Disk, PartialDisk를 구현한다. 
	glOrtho() 투영변환함수를 이용하여 가시부피 안에 있는 객체들을 투영면 Z=0인 평면에 그린다.
	glViewport()를 이용하여 화면상의 뷰폿의 위치와 크기를 설정한다.
	Reshape callback을 이용하여 새로고침된 Window상의 viewport위치와 크기를 입력받아, 가시부피의 종횡비와 동일하게 설정하여 왜곡문제를 해결한다.
	
	이 문제의 핵심인 "Display List"를 이용한다.  반복적으로 실행되어야 할 요소를 Display List 내부에 포함시키므로써, 이미 정의된 물체를 컴파일 된 형태로 재사용한다.
	따라서 프로그램의 속도를 향상시킬 수 있다. 
*/
/**************************************************************************/


#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>


GLUquadricObj* qobj = gluNewQuadric();	//새로운 Quadric 생성

// DisplayList는 정수 ID에 의해 식별됨
// 한꺼번에 여러개의 DisplayList ID를 할당하기 위해 배열로 생성
GLuint MyListID[4];
int variable_list = 1;					// 리스트 내부 변수 변경

// Display List 생성하는 함수 
void MyCreateList() {
	
	// 아이디를 가진 리스트 4개를 새로 만들되,
	// 실행하지 않고 컴파일 완료된 버전을 만든다.

	//Sphere
	MyListID[0] = glGenLists(4);				//Display List 아이디 할당(사용 안 된 아이디 중 첫번째 아이디를 되돌려줌) 
	glNewList(MyListID[0], GL_COMPILE);			//Display List 생성
	gluQuadricDrawStyle(qobj, GLU_FILL);		//원하는 Draw Style 지정 -> 반시계방향(CCW)으로 그려짐
	gluQuadricNormals(qobj, GLU_SMOOTH);		//법선벡터 제어 -> 부드럽게 보이게 
	gluQuadricOrientation(qobj, GLU_OUTSIDE);	//법선벡터 내부 및 외부 등과 같은 방향 지정 -> 바깥쪽을 가리킴
	gluQuadricTexture(qobj, GL_FALSE);			//Texture 좌표 사용x
	gluSphere(qobj, 1.5, 50, 50);				//Sphere 생성(그리기) 	
	glEndList();								//Display List의 끝을 표시함 


	//Cylinder   
	MyListID[1] = MyListID[0] + 1;		
	glNewList(MyListID[1], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL);		//원하는 Draw Style 지정 -> Wire-frame 형태의 Modeling
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluCylinder(qobj, 1.0, 0.0, 8, 10, 6);	//Cylinder 생성(그리기) 	 	
	glEndList();


	//Disk
	MyListID[2] = MyListID[1] + 1;		
	glNewList(MyListID[2], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);	//원하는 Draw Style 지정 -> 외부 모서리만 Modeling
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluDisk(qobj, 0.5, 2.0, 20, 3);				//Disk 생성(그리기) 			
	glEndList();


	//Partial Disk 
	MyListID[3] = MyListID[2] + 1;		
	glNewList(MyListID[3], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_POINT);		//원하는 Draw Style 지정 -> Point로만 Modeling 
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluPartialDisk(qobj, 0.5, 2.0, 26, 13, 60, -100);	//60도부터 반시계방향으로 100도만큼 이동한 PartialDisk 생성(그리기) 	 
	//gluPartialDisk(qobj, 0.5, 2.0, 26, 13, 60, 100);	//60도부터 시계방향으로 100도만큼 이동
	glEndList();	
}

// 조명값 세팅 설정 함수로, glEnable를 통해 조명모드를 활성화시킨다. 
void MyInit(void) {
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

// Display 콜백 함수 
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//윈도우에서 그림 제거로, 화면을 깨끗하게 지움 

	glMatrixMode(GL_MODELVIEW);		//모델뷰 선택
	glLoadIdentity();				//행렬 초기화 

	glEnable(GL_LIGHTING);			//조명 모드 활성화 
	glShadeModel(GL_SMOOTH);		//부드럽게 색칠

	// 컴파일이 완료된 리스트가 실제로 실행(Display List 실행)
	glCallList(MyListID[variable_list]);	
	glFlush();
}

// reshape 콜백 함수: 윈도우 창 재조정시에 호출됨
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);			//(x, y)위치에서 width* height영역에 이미지 출력

	//새로운 width, height의 비율 구하기 
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;

	glMatrixMode(GL_PROJECTION);		//투영행렬스택으로 변환(for 투영변환함수들을 원래의 목적대로 사용)
	glLoadIdentity();					//현재 projection 행렬 초기화(항등행렬)
	//가시부피와 viewport의 종횡비를 일치시켜 왜곡방지
	glOrtho(-2.5 * Widthfactor, 2.5 * Widthfactor, -2.5 * Heightfactor, 2.5 * Heightfactor, -10.0, 10.0);
}

int main(int argc, char** argv)		
{
	//Window 초기화 및 생성
	glutInit(&argc, argv);			//Window OS와 Session 연결 및 GLUT Library 초기화
	glutInitDisplayMode(GLUT_RGB);	//display mode 설정 && RGB 
	glutInitWindowSize(500, 500);	//Window 크기 설정 => x축방향의 크기=500, y축 방향의 크기=500으로 설정
	glutInitWindowPosition(0, 0);	//Monitor에서 Window의 시작점 위치 설정
	glutCreateWindow("Show 3D Primitive");	//title를 인자로 갖는 새로운 Window 생성
	glClearColor(1, 1, 1, 0);
	MyInit();						//조명값 세팅

	//Callback 함수 등록
	glutDisplayFunc(MyDisplay);		//Display Callback함수 등록
	glutReshapeFunc(MyReshape);		//Reshape Callback함수 등록 
	
	// Display List 생성
	MyCreateList(); 

	//이벤트 루프로 진입 
	glutMainLoop();	//GLUT Event 처리 Loop 입력 
	return 0;		//종료
}