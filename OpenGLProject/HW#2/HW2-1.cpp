/*************************************************************************/
/*				       HW#2-1.  GL Modeling                              */
/*
	���� ���� :
	GL Modeling�� �Ͽ� 2D Primitives�� �����Ѵ�.  

	���:
	GL Library�� �̿��ϸ�, z���� 0���� �����Ͽ� 2D Primitives�� �����Ѵ�. 
	������ 2D Primitives���� Points, Lines, LineStrip, LineLoop, TrangleFan, Triangles, TriangleStrip, Polygons, Quads, QuadStrip�̴�. 
	glBegin()�Լ��� ���ڿ� ���� ���������� �ؼ��ϴ� ����� �޶�����. 
	���ú��Ǹ� �����ϴ� ������ȯ�Լ��� ȣ������ �ʰ�, �⺻ default������ ����ȭ ���ú��Ǹ� �̿��Ѵ�.  
*/
/**************************************************************************/


#include <gl/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	//�����쿡�� �׸� ���ŷ�, ȭ���� �����ϰ� ���� 
	glColor3f(0,0,1);				//3�������� vertex�� �Ķ������� ����
	glPointSize(5.0);				//��Ʈ������ ����
	//glLineWidth(5.0);				//���� ���� ����

	//���ο� 2���� Primitives ���(ǥ��)
	//Points
	glBegin(GL_POINTS);				//�� Vertex���� �ϳ��� Point�� ǥ���Ѵ�.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();
	
	//Lines
	glBegin(GL_LINES);				//Vertex���� ������� �� ���� ��� Line�� �����.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//LineStrip
	glBegin(GL_LINE_STRIP);			//Line���� �� �ٷ� �����Ѵ�.
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//LineLoop
	glBegin(GL_LINE_LOOP);			//������ Vertex�� ù ��° Vertex�� �����ϴ� Line�� �߰��� GL_LINE_STRIP
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//Triangles
	glBegin(GL_TRIANGLES);			//�� ���� Vertex�� ��� �ﰢ���� �����. 
	glVertex3f(-0.3, -0.4, 0.0); glVertex3f(0.25, -0.6, 0.0);
	glVertex3f(0.5, 0.3, 0.0); glVertex3f(0.35, 0.45, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.6, -0.2, 0.0);
	glEnd();

	//TriangleStrip
	glBegin(GL_TRIANGLE_STRIP);		//�ﰢ������ ��� �����Ѵ�.
	glVertex3f(0.6, -0.4, 0.0); glVertex3f(0.4, 0.4, 0.0);
	glVertex3f(0.2, -0.1, 0.0); glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(-0.25, -0.3, 0.0); glVertex3f(-0.5, 0.2, 0.0);
	glVertex3f(-0.8, -0.3, 0.0);
	glEnd();

	//TrangleFan
	glBegin(GL_TRIANGLE_FAN);		//�ﰢ������ ��ä ������� �����Ѵ�.
	glVertex3f(-0.5, -0.3, 0.0); glVertex3f(0.8, -0.1, 0.0);
	glVertex3f(0.65, 0.1, 0.0); glVertex3f(0.6, 0.25, 0.0);
	glVertex3f(0.15, 0.55, 0.0); glVertex3f(-0.15, 0.6, 0.0);
	glEnd();

	//Polygons
	glBegin(GL_POLYGON);			//�ܼ�, ������ �ٰ���
	glVertex3f(-0.25, -0.5, 0.0); glVertex3f(0.25, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0); glVertex3f(0.25, 0.5, 0.0);
	glVertex3f(-0.25, 0.5, 0.0); glVertex3f(-0.5, 0.0, 0.0);
	glEnd();

	//Quads
	glBegin(GL_QUADS);				//Vertex���� �� ���� ��� ���� �� ���� �𼭸��� ���� �ٰ����� �����.
	glVertex3f(0.2,-0.2,0.0); glVertex3f(0.3, 0.05, 0.0);
	glVertex3f(0.15, 0.2, 0.0); glVertex3f(-0.1, -0.15, 0.0);
	glVertex3f(-0.25, 0.15, 0.0); glVertex3f(-0.2,0.45, 0.0);
	glVertex3f(-0.35, 0.4, 0.0); glVertex3f(-0.5, 0.2, 0.0);
	glEnd();

	//QuadStrip
	glBegin(GL_QUAD_STRIP);			//�簢������ ��� �����Ѵ�. 
	glVertex3f(0.2,-0.2,0.0); glVertex3f(0.3, 0.05, 0.0);
	glVertex3f(-0.1, -0.15, 0.0); glVertex3f(0.15, 0.2, 0.0);
	glVertex3f(-0.25, 0.15, 0.0); glVertex3f(-0.2,0.45, 0.0);
	glVertex3f(-0.5, 0.2, 0.0);  glVertex3f(-0.35, 0.4, 0.0);
	glEnd();

	glFlush();						//���� ������� ���� ��� ��� �����ϵ��� �Ѵ�. 
}

int main(int argc, char** argv)
{
	//Window �ʱ�ȭ �� ����
	glutInit(&argc, argv);			//Window OS�� Session ���� �� GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB);	//display mode ���� && RGB
	glutInitWindowSize(500, 500);	//Window ũ�� ���� => x������� ũ��=500, y�� ������ ũ��=500���� ����
	glutInitWindowPosition(0, 0);	//Monitor���� Window�� ������ ��ġ ����
	glutCreateWindow("Show 2D Primitives");	//title�� ���ڷ� ���� ���ο� Window ����
	glClearColor(1, 1, 1, 0);		//Window â ������ �������� ������ ���������� ����

	//Callback �Լ� ��� 
	glutDisplayFunc(MyDisplay);		//Display Callback�Լ� ���

	//�̺�Ʈ ������ ���� 
	glutMainLoop();	//glutMainLoop(): GLUT Event ó�� Loop �Է� 
	return 0;		//����
}