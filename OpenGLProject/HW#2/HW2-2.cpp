/*************************************************************************/
/*				       HW#2-2.  GLU Modeling                             */
/*
	���� ���� :
	GLU Modeling�� �Ͽ� 3D Primitives�� �����Ѵ�. 

	���:
	3D �������� 3D��ü�� �����ϴ� Quadrics�� �̿��Ѵ�. 
	GLU Modeling�� �Ͽ� 3D Primitives�� Sphere, Cylinder, Disk, PartialDisk�� �����Ѵ�. 
	glOrtho() ������ȯ�Լ��� �̿��Ͽ� ���ú��� �ȿ� �ִ� ��ü���� ������ Z=0�� ��鿡 �׸���.
	glViewport()�� �̿��Ͽ� ȭ����� ������ ��ġ�� ũ�⸦ �����Ѵ�.
	Reshape callback�� �̿��Ͽ� ���ΰ�ħ�� Window���� viewport��ġ�� ũ�⸦ �Է¹޾�, ���ú����� ��Ⱦ��� �����ϰ� �����Ͽ� �ְ���� �ذ��Ѵ�.
	
	�� ������ �ٽ��� "Display List"�� �̿��Ѵ�.  �ݺ������� ����Ǿ�� �� ��Ҹ� Display List ���ο� ���Խ�Ű�Ƿν�, �̹� ���ǵ� ��ü�� ������ �� ���·� �����Ѵ�.
	���� ���α׷��� �ӵ��� ����ų �� �ִ�. 
*/
/**************************************************************************/


#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>


GLUquadricObj* qobj = gluNewQuadric();	//���ο� Quadric ����

// DisplayList�� ���� ID�� ���� �ĺ���
// �Ѳ����� �������� DisplayList ID�� �Ҵ��ϱ� ���� �迭�� ����
GLuint MyListID[4];
int variable_list = 1;					// ����Ʈ ���� ���� ����

// Display List �����ϴ� �Լ� 
void MyCreateList() {
	
	// ���̵� ���� ����Ʈ 4���� ���� �����,
	// �������� �ʰ� ������ �Ϸ�� ������ �����.

	//Sphere
	MyListID[0] = glGenLists(4);				//Display List ���̵� �Ҵ�(��� �� �� ���̵� �� ù��° ���̵� �ǵ�����) 
	glNewList(MyListID[0], GL_COMPILE);			//Display List ����
	gluQuadricDrawStyle(qobj, GLU_FILL);		//���ϴ� Draw Style ���� -> �ݽð����(CCW)���� �׷���
	gluQuadricNormals(qobj, GLU_SMOOTH);		//�������� ���� -> �ε巴�� ���̰� 
	gluQuadricOrientation(qobj, GLU_OUTSIDE);	//�������� ���� �� �ܺ� ��� ���� ���� ���� -> �ٱ����� ����Ŵ
	gluQuadricTexture(qobj, GL_FALSE);			//Texture ��ǥ ���x
	gluSphere(qobj, 1.5, 50, 50);				//Sphere ����(�׸���) 	
	glEndList();								//Display List�� ���� ǥ���� 


	//Cylinder   
	MyListID[1] = MyListID[0] + 1;		
	glNewList(MyListID[1], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_FILL);		//���ϴ� Draw Style ���� -> Wire-frame ������ Modeling
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluCylinder(qobj, 1.0, 0.0, 8, 10, 6);	//Cylinder ����(�׸���) 	 	
	glEndList();


	//Disk
	MyListID[2] = MyListID[1] + 1;		
	glNewList(MyListID[2], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);	//���ϴ� Draw Style ���� -> �ܺ� �𼭸��� Modeling
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluDisk(qobj, 0.5, 2.0, 20, 3);				//Disk ����(�׸���) 			
	glEndList();


	//Partial Disk 
	MyListID[3] = MyListID[2] + 1;		
	glNewList(MyListID[3], GL_COMPILE);
	gluQuadricDrawStyle(qobj, GLU_POINT);		//���ϴ� Draw Style ���� -> Point�θ� Modeling 
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluPartialDisk(qobj, 0.5, 2.0, 26, 13, 60, -100);	//60������ �ݽð�������� 100����ŭ �̵��� PartialDisk ����(�׸���) 	 
	//gluPartialDisk(qobj, 0.5, 2.0, 26, 13, 60, 100);	//60������ �ð�������� 100����ŭ �̵�
	glEndList();	
}

// ���� ���� ���� �Լ���, glEnable�� ���� �����带 Ȱ��ȭ��Ų��. 
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

// Display �ݹ� �Լ� 
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//�����쿡�� �׸� ���ŷ�, ȭ���� �����ϰ� ���� 

	glMatrixMode(GL_MODELVIEW);		//�𵨺� ����
	glLoadIdentity();				//��� �ʱ�ȭ 

	glEnable(GL_LIGHTING);			//���� ��� Ȱ��ȭ 
	glShadeModel(GL_SMOOTH);		//�ε巴�� ��ĥ

	// �������� �Ϸ�� ����Ʈ�� ������ ����(Display List ����)
	glCallList(MyListID[variable_list]);	
	glFlush();
}

// reshape �ݹ� �Լ�: ������ â �������ÿ� ȣ���
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);			//(x, y)��ġ���� width* height������ �̹��� ���

	//���ο� width, height�� ���� ���ϱ� 
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;

	glMatrixMode(GL_PROJECTION);		//������Ľ������� ��ȯ(for ������ȯ�Լ����� ������ ������� ���)
	glLoadIdentity();					//���� projection ��� �ʱ�ȭ(�׵����)
	//���ú��ǿ� viewport�� ��Ⱦ�� ��ġ���� �ְ����
	glOrtho(-2.5 * Widthfactor, 2.5 * Widthfactor, -2.5 * Heightfactor, 2.5 * Heightfactor, -10.0, 10.0);
}

int main(int argc, char** argv)		
{
	//Window �ʱ�ȭ �� ����
	glutInit(&argc, argv);			//Window OS�� Session ���� �� GLUT Library �ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB);	//display mode ���� && RGB 
	glutInitWindowSize(500, 500);	//Window ũ�� ���� => x������� ũ��=500, y�� ������ ũ��=500���� ����
	glutInitWindowPosition(0, 0);	//Monitor���� Window�� ������ ��ġ ����
	glutCreateWindow("Show 3D Primitive");	//title�� ���ڷ� ���� ���ο� Window ����
	glClearColor(1, 1, 1, 0);
	MyInit();						//���� ����

	//Callback �Լ� ���
	glutDisplayFunc(MyDisplay);		//Display Callback�Լ� ���
	glutReshapeFunc(MyReshape);		//Reshape Callback�Լ� ��� 
	
	// Display List ����
	MyCreateList(); 

	//�̺�Ʈ ������ ���� 
	glutMainLoop();	//GLUT Event ó�� Loop �Է� 
	return 0;		//����
}