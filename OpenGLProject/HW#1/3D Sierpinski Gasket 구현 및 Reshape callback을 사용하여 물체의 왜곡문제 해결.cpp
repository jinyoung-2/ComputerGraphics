/****************************************************/
/*													*/
/*
	���� ���� :
	3D Sierpinski Gasket ���� �� Reshape callback�� ����Ͽ� ��ü�� �ְ�� �ذ�

	���: 
	glOrtho() ������ȯ�Լ��� �̿��Ͽ� ���ú��� �ȿ� �ִ� ��ü���� ������ Z=0�� ��鿡 �׸���.
	glViewport()�� �̿��Ͽ� ȭ����� ������ ��ġ�� ũ�⸦ �����Ѵ�. 
	Reshape callback�� �̿��Ͽ� ���ΰ�ħ�� Window���� viewport��ġ�� ũ�⸦ �Է¹޾�, ���ú����� ��Ⱦ��� �����ϰ� �����Ͽ� �ְ���� �ذ��Ѵ�.
*/
/***************************************************/




//2D �ﰢ�� -> 3D ���ü�� Ȯ�� 
#include <gl/glut.h>
#include <stdlib.h>		//rand()�Լ� ���뵵 
#include <math.h>

//Display Callback �Լ� 
void MyDisplay() {	
	float vertices[4][3] = { {0,0,0},{0,300,300},{300,0,300},{300,300,0} };		//3���� 4���� ���� ����(������ü�� �������� ������ ������ �̾� �����ü ����)
	float p[3] = {100,70,100 };		// �� P�� ��ġ
	int i, j;
	
	glClear(GL_COLOR_BUFFER_BIT);	//glClear(): �����쿡�� �׸� ���ŷ�, ȭ���� �����ϰ� ���� 

	for (j = 0; j < 50000; j++) {
		i = rand() % 4;				//V0,V1,V2,V3 4���� ���� �� ���� ����

		//���� ���õ� ���� ���� ���� �������� ���ο� �� ��ġ ���
		p[0] = (p[0] + vertices[i][0]) / 2.0;
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;

		//���� ������Ƽ��: ������ ������ �����ϴ� �� ��ü��ü�� ǥ���ϴµ� �־� ���� �⺻�� �Ǵ� ���
		//���ο� 3���� �� ���(ǥ��)
		glBegin(GL_POINTS);			  
			glVertex3fv(p);	
		glEnd();
	}
	glFlush();	//glFlush(): ���� ������� ���� ��� ��� �����ϵ��� �� 
}

//����Ʈ ��ȯ
// viewport: �׸��� �׷����� ���÷��� ��ġ������ �簢 ���� 
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);						//glviewport(x,y,width,height): (x,y)��ġ���� width*height������ �̹��� ���
	
	//���ο� width, height�� ���� ���ϱ� 
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;
	
	glMatrixMode(GL_PROJECTION);		//������Ľ������� ��ȯ(for ������ȯ�Լ����� ������ ������� ���)
	glLoadIdentity();					//���� projection ��� �ʱ�ȭ(�׵����)
	//���ú��ǿ� viewport�� ��Ⱦ�� ��ġ���� �ְ����
	glOrtho(-100.0 * Widthfactor, 500.0 * Widthfactor, -100.0 * Heightfactor, 500.0 * Heightfactor, 30.0, -300.0);

	//�ش� ���� �������� degree��ŭ ȸ�� 
	glRotatef(-30.0, 1.0, 0.0, 0.0);
	glRotatef(-40.0, 0.0, 0.0, 1.0);
}


void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);	//glClearColor(): window â ������ �������� �������� ������� ����
	glColor3f(1.0, 0.0, 0.0);			//3�������� vertex�� ���������� ����	
}

int main(int argc, char** argv) 
{
	//Window �ʱ�ȭ �� ����
	glutInit(&argc, argv);			//glutInit(): Window OS�� Session ���� �� GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB);	//glutInitDisplayMode(): display mode ���� && GLUT_RGB : GLUT_RGBA�� ���� Alias
	glutInitWindowSize(500, 500);	//Window ũ�� ���� => x������� ũ��=500, y�� ������ ũ��=500���� ����
	glutInitWindowPosition(0, 0);	//Monitor���� Window�� ������ ��ġ ����
	glutCreateWindow("Show 3D Sierpinski Gasket");	//title�� ���ڷ� ���� ���ο� Window ����
	
	//Callback �Լ� ��� 
	glutDisplayFunc(MyDisplay);		//Display Callback�Լ� ���
	glutReshapeFunc(MyReshape);		//Reshape Callback�Լ� ��� 
	MyInit();

	//�̺�Ʈ ������ ���� 
	glutMainLoop();	//glutMainLoop(): GLUT Event ó�� Loop �Է� 
	return 0;		//����
}