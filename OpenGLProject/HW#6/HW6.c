/*************************************************************************/
/*													                     */
/*
    ���� ���� :
    �ڵ�7-2�� �����Ͽ� ������ ���� ����� �� �� �ִ� ���α׷� ����

    ?  Teapot ��ü�� Torus ��ü, �� 2���� ��ü�� �� ������ �׸�.
    ?  �ϳ��� �����츦 4���� �������� ����
    ?  ������ ���� : �������� => gluPerspective()
    ?  ���ϴ��� ���� : �������� => glOrtho()
    
    ?  ������ �ִ� ��ü���� ���� Keyboard Callback�� SpecialKeyboard Callback �Լ��� ����Ͽ� Camera�� �̵�(������ȯ)�� ������ �� �ֵ��� ��.(�� �������� ��ȯ�� ����ǵ��� ��)
    => ���ϴܰ� ���� ������ �����ϴ� Teapot ��ü�� ������ �߾ӿ� ��ġ�ϵ��� �������ֱ� ���� Ư�� ���� �������� ��ȯ�� �����ϵ��� �Ѵ�. 

    ?  ��� �������� ��ü�� �⺻������ ������ �߽ɺο� ��ġ�ϵ��� �ϰ�. Keyboard�� ������ ��쿡�� �׻� �߽ɺο� ��ġ�ϵ��� ��.
    => ��ü�� ������ �߽ɺο� ��ġ�ϵ���(=0,0,0�� ��ġ�ϵ���)����
    
    ?  �������� ũ�⸦ ���Ƿ� �����ϰų� Full Screen���� �����Ͽ��� ��쿡�� �������� ũ�⿡ ������� ��ü�� ���°� �ְ���� �ʵ��� ��.
    => �������� ũ�⿡ ������ ���� �ʰ� �׻� ��ü�� ���°� �����ϵ���, �� ��ü ���� �� ũ�Ⱑ �����ϰ� �����Ǿ�� �Ѵ�

    ���:
    ?  glutLookAt()�Լ��� �̿��Ͽ� Camera�� ��ġ �� Camera�� ����Ű�� ������ ��ġ�� ������� ������ǥ�踦 ���� �����Ѵ�.
    ?  Keyboard Callback�Լ��� �̿��Ͽ� �ش� key�� ������ ��� ������ȯ�� ������ �� �ִ�.
        => ��� ������ ���ÿ� ��ȯ�� ����ȴ�.
    ?  Special Keyboard Callback�Լ��� �̿��Ͽ� �ش� key�� ������ ��� ������ȯ�� ������ �� �ִ�.
        => �� �������� ���� ��ȯ�� ����ȴ�.
    ?  glutPostdisplay()�� ȣ���Ͽ� ������ event �߻��� ������ ������ ���������� ����ǵ��� �Ѵ�.
    ?  glutInitDisplayMode()�� ���ڷ� GLUT_DOUBLE�� �̿��Ѵ�. Double buffering�� �̿��Ͽ� single buffering�� �������� ����ȿ���� �ذ��Ѵ�.
    ?  glutSwapBuffers()�� ���� ��Ȳ�� ���� back buffer�� front buffer�� ��ȯ�Ѵ�. Display function�� ���� �߰��Ѵ�.


*/
/************************************************************************/


#include <GL/glut.h>

int Width, Height;
GLfloat cx = 0.0, cy = 0.0, cz = 0.0;   //glutLookAt()�Լ��� ���� ��ȭ�� ���� �������� ���

//������ Camera��ġ ��������
GLfloat c1x = 0.0, c1y = 0.0, c1z = 0.0;
GLfloat c2x = 0.0, c2y = 0.0, c2z = 0.0;

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);   //�� ����  
}

// �𵨺�ȯ => 2���� ��ü �׸���(�� ������) 
void DrawScene() {

    // Teapot
    glColor3f(0.3, 0.3, 0.7);
    glPushMatrix(); //ī�޶��� �̵��� �����ϸ� �Ǵ°Ŷ�, ������ ��ü �߾ӿ� ��ġ�ϵ��� ����
        glutWireTeapot(1.0);
        glPushMatrix();
            // Torus
            glColor3f(0.0, 1.0, 1.0);
            glTranslatef(0.0, 0.0, -2.0);
            glRotatef(-30.0, 0.0, 1.0, 0.0);
            glScalef(0.2, 0.2, -0.5);
            glRotatef(30.0, 0.0, 1.0, 0.0);
            glutWireTorus(0.5, 2.0, 20, 20);
            glPopMatrix();
        glPopMatrix();

    // ����
    //glColor3f(0.7, 0.7, 0.7);           //�� ����
    //glPushMatrix();                     //��� ����      
    //    glTranslatef(0.0, -1.0, 0.0);
    //    glBegin(GL_QUADS);              //��ü ��ǥ�� ���� �׸��� 
    //        glVertex3f(2.0, 0.0, 2.0);
    //        glVertex3f(2.0, 0.0, -2.0);
    //        glVertex3f(-2.0, 0.0, -2.0);
    //        glVertex3f(-2.0, 0.0, 2.0);
    //    glEnd();
    //    glPopMatrix();

}

// Reshape Callback �Լ�
void MyReshape(int w, int h) {
    Width = w;
    Height = h;

    glMatrixMode(GL_PROJECTION);        // ���� ��� ���� ���
    glLoadIdentity();                  // ��� �ʱ�ȭ(CTM�� I�� ����)

    glMatrixMode(GL_MODELVIEW);         // �𵨺� ��� ���� ���
    glLoadIdentity();                  // ��� �ʱ�ȭ(CTM�� I�� ����)
}


//Display Callback �Լ�
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //���ϴ��� ���� => ��������
    glViewport(0, 0, 250, 250);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);      //����������ȯ
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(0.0 + cx + c1x, 0.0 + cy + c1y, 1.0 + cz + c1z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //������ȯ
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    //���ϴ��� ���� 
    //glViewport(250, 0, 250, 250);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
    //glLoadIdentity();
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);      //����������ȯ
    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //gluLookAt(-1.0 + cx, 0.0 +cy, 0.0+cz,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //������ȯ
    //DrawScene();
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();



    //�»���� ����
    //glViewport(0, 250, 250, 250);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
    //glLoadIdentity();
    //gluPerspective(30, 500 / 500, 3.0, 50.0);
    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //gluLookAt(3.0 + cx, 0.0 + cy, 0.0 + cz,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //������ȯ
    //DrawScene();
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();


    //������ ���� => ��������
    glViewport(250, 250, 250, 250);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(30, 500/500, 3.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(5.0 + cx + c2x, 5.0 + cy + c2y, 5.0 + cz + c2z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //������ȯ
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();
}

// Special KeyBoard Callback �Լ� => ���� ������ ������ȯ�� ���� ���� 
// ��� ������ �ִ� ��ü���� ������ �߾ӿ��� ���̰� �ϱ� ���� ������ȯ ��, ���ǹ��� �̿��Ѵ�. Ư�� ������ ��� ��� + or -0.1�� ���� �ʴ´�. 
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
        //���� Case1�� Camera��ġ ����
    case GLUT_KEY_F1:   // Camera�� X�� ��ǥ�� 0.1�� ���������� ���� 
        if(cx+c1x <= 2.7)
            c1x += 0.1;
        break;
    case GLUT_KEY_F2:   // Camera�� X�� ��ǥ�� 0.1�� ���������� ����
        if(cx+c1x >= -2.7)
            c1x -= 0.1;
        break;
    case GLUT_KEY_F3:   // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
        if(cy+c1y <= 2.7)
            c1y += 0.1;
        break;
    case GLUT_KEY_F4:   // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
        if (cy + c1y >= -2.7)
            c1y -= 0.1;
        break;
    case GLUT_KEY_F5:   // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����     //�׸� ����� ==> check�ϱ� 
        if (cz + c1z <= 2.0)
            c1z += 0.1;
        break;
    case GLUT_KEY_F6:   // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����  
        if (cz + c1z >= -2.0)
            c1z -= 0.1;
        break;

        //���� Case4�� Camera��ġ ����
    case GLUT_KEY_F7:   // Camera�� X�� ��ǥ�� 0.1�� ���������� ����  
        if (cx + c2x <= 2.7)
            c2x += 0.1;
        break;
    case GLUT_KEY_F8:   // Camera�� X�� ��ǥ�� 0.1�� ���������� ����  
        if (cx + c2x >= -2.7)
            c2x -= 0.1;
        break;
    case GLUT_KEY_F9:   // Camera�� Y�� ��ǥ�� 0.1�� ���������� ���� 
        if (cy + c2y <= 2.7)
            c2y += 0.1;
        break;
    case GLUT_KEY_F10:  // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����  
        if (cy + c2y >= -2.7)
            c2y -= 0.1;
        break;
    case GLUT_KEY_F11:  // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����     
        if (cz + c2z <= 2.0)
            c2z += 0.1;
        break;
    case GLUT_KEY_RIGHT:  // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����      
        if (cz + c2z >= -2.0)
            c2z -= 0.1;
        break;

    default:
        break;
    }
    glutPostRedisplay();    //Display Event ���� �߻���Ŵ 
}


//KeyBoard Callback �Լ� => ��� ������ ������ȯ�� ���ÿ� ���� 
void MyKeyboard(unsigned char key, int x, int y) {
    
    //keyboard callback �Լ� ȣ���, ������ �������� �����Ų ������ȯ(ī�޶��̵�)�� �ʱ�ȭ�� ��, ��� ������ �����ϰ� ������ȯ�� �Ѵ�. 
    c1x = 0.0;
    c1y = 0.0;
    c1z = 0.0;
    c2x = 0.0;
    c2y = 0.0;
    c2z = 0.0;

    switch (key) {
        // Camera�� X�� ��ǥ�� 0.1�� ���������� ����  
    case 'q':
    case 'Q':
        if(cx <= 2.7)
            cx += 0.1;
        break;

        // Camera�� X�� ��ǥ�� 0.1�� ���������� ����
    case 'w':
    case 'W':
        if(cx >= -2.7)
            cx -= 0.1;
        break;

        // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'e':
    case 'E':
        if(cy <= 2.7)
            cy += 0.1;
        break;

        // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'r':
    case 'R':
        if(cy >= -2.7)
            cy -= 0.1;
        break;

        // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����        
    case 'd':
    case 'D':
        if(cz <= 2.0)
            cz += 0.1;
        break;

        // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����          
    case 'f':
    case 'F':
        if(cz >= -2.0)
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


int main(int argc, char** argv) {

    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewport Partition");

    MyInit();

    //Callback �Լ� ���
    glutDisplayFunc(MyDisplay);     //Display Callback �Լ�
    glutReshapeFunc(MyReshape);     //Reshape Callback �Լ�
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback �Լ�
    glutSpecialFunc(MySpecialKeyboard);     //Sepcial KeyBoard Callback �Լ� 

    glutMainLoop();
    return 0;
}
