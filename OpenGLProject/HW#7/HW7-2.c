#include <stdlib.h>
#include <GL/glut.h>

static int body = 0, head = 0, arm1 = 0, arm2 = 0, leg1 = 0, leg2 = 0;  //ȸ�� ���� 
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //��Ȳ�� ���� ���� ȸ�� ������ ������ ���� 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop���� �����ϱ� ���� �ʿ��� ���� 
static int go_to = -1;

//Timer Callback �Լ�
void MyTimer(int value) {
    if (value == 1) {           //�Ӹ� �����̱�
        if (dir_head == 0) {    //stop�� ���
            dir_head = 1;
            return;
        }
        head += dir_head;       //���ο� ���� 
        if (head == 0) {
            if (chk0 == 1) {    //���� ��ġ�̸�, stop�� ���
                chk0 = -1;      //chk���� ���� -1�� �����Ͽ� stop�� �ƴ��� ���
                return;
            }
            else                //���� ��ġ�ε�, stop�� �ƴ� �̵��ϴ� ���
                chk0 = 1;       //chk���� ���� 1�� �����Ͽ� �������� ���� ��ġ�� ��� stop���� ��� 
        }

        //ȸ�� ���� 
        if (head >= 50)
            dir_head = -1;
        else if (head <= -50)
            dir_head = 1;

        glutTimerFunc(50, MyTimer, 1);
        glutPostRedisplay();
    }
    else if (value == 2) {      //�������� �����̱�
        if (dir_arm1 == 0) {    //stop�� ���  => ó����ġ�� �̵��ϵ��� dir_arm1���� 1�� ���� 
            dir_arm1 = 1;
            return;
        }

        arm1 += dir_arm1;       //���ο� ����

        //ȸ�� ����
        if (arm1 <= -45)
            dir_arm1 = 1;
        else if (arm1 >= 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
            chk1 = -1;
            return;
        }
        glutTimerFunc(50, MyTimer, 2);
        glutPostRedisplay();
    }
    else if (value == 3) {      //������ �����̱�
        if (dir_arm2 == 0) {    //stop�� ���
            dir_arm2 = -1;
            return;
        }
        arm2 += dir_arm2;       //���ο� ����

        //ȸ�� ����
        if (arm2 >= 45)
            dir_arm2 = -1;
        else if (arm2 == 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
            chk2 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 3);
        glutPostRedisplay();
    }
    else if (value == 4) {      //�����ʴٸ� �����̱�
        if (dir_leg1 == 0) {    //stop�� ���
            dir_leg1 = 1;
            return;
        }
        leg1 += dir_leg1;       //���ο� ����

        //ȸ�� ����
        if (leg1 <= -45)
            dir_leg1 = 1;
        else if (leg1 == 0) {  //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
            chk3 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 4);
        glutPostRedisplay();
    }
    else if (value == 5) {      //���ʴٸ� �����̱�
        if (dir_leg2 == 0) {    //stop�� ���
            dir_leg2 = -1;
            return;
        }
        leg2 += dir_leg2;       //���ο� ����

        //ȸ�� ����
        if (leg2 >= 45)
            dir_leg2 = -1;
        else if (leg2 == 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
            chk4 = -1;
            return;
        }

        glutTimerFunc(50, MyTimer, 5);
        glutPostRedisplay();
    }
    else if (value == 6) {
        if (go_to == 1) {           //�Ӹ� stop
            dir_head = 1;
            return;
        }
        else if (go_to == 2) {      //�������� stop
            dir_arm1 = 1;
            return;
        }
        else if (go_to == 3) {      //������ stop
            dir_arm2 = -1;
            return;
        }
        else if (go_to == 4) {      //�����ʴٸ� stop
            dir_leg1 = 1;
            return;
        }
        else if (go_to == 5) {      //���ʴٸ� stop
            dir_leg2 = -1;
            return;
        }
    }
}


// Pop-up MainMenu ����
// �ش� �޴��� �´� ��ü�� �ѹ� �������ٰ� ���� �ڼ��� ���ƿ�
void MyMainMenu(int entryID) {  //entryID: �޴����� ������ ���� ��ȣ 
    if (entryID == 1) {
        //�Ӹ� �����̱�
        if (chk0 != 1) {    //stop���� -> move���·� ��ȯ
            chk0 = 1;
        }
        dir_head = -1;
        glutTimerFunc(40, MyTimer, entryID);    //Ÿ�̸� �ݹ��Լ� ���
    }
    else if (entryID == 2) {
        //�������� �����̱�
        if (chk1 != 1) {        //stop���� -> move���·� ��ȯ
            chk1 = 1;
        }
        dir_arm1 = -1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 3) {
        //������ �����̱�
        if (chk2 != 1) {    //stop���� -> move���·� ��ȯ    
            chk2 = 1;
        }
        dir_arm2 = 1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 4) {
        //�����ʴٸ� �����̱�
        if (chk3 != 1) {    //stop���� -> move���·� ��ȯ
            chk3 = 1;
        }
        dir_leg1 = -1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 5) {
        //���ʴٸ� �����̱�
        if (chk4 != 1) {    //stop���� -> move���·� ��ȯ
            chk4 = 1;
        }
        dir_leg2 = 1;
        glutTimerFunc(40, MyTimer, entryID);
    }
    else if (entryID == 6)       //�ָ޴����� exit ������ ���
        exit(0);                //����

    glutPostRedisplay();        //Display Event ���� �߻���Ŵ 
}

//KeyBoard Callback �Լ�
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'S':   //�����̴� ��ü�� ����
        //Ÿ�̸� �Լ� ��� -> �� ���ȣ��x 

        //chk: 1(�����̴� ����)
        //�����̴� ���� �ľ� ��, �����̴� ��ü������ stop���� ����
        if (chk0 == 1) {
            go_to = 1;
            dir_head = 0;   //�������� stop�ϱ� ���� ���ϴ� ȸ�������� 0���� ����
            glutTimerFunc(40, MyTimer, 6);  //Ÿ�̸� �ݹ��Լ� ��� 
        }
        if (chk1 == 1) {
            go_to = 2;
            dir_arm1 = 0;   //�������� stop�ϱ� ���� ���ϴ� ȸ�������� 0���� ����
            glutTimerFunc(40, MyTimer, 6);  //Ÿ�̸� �ݹ��Լ� ��� 
        }
        if (chk2 == 1) {
            go_to = 3;
            dir_arm2 = 0;    //�������� stop�ϱ� ���� ���ϴ� ȸ�������� 0���� ����
            glutTimerFunc(40, MyTimer, 6);  //Ÿ�̸� �ݹ��Լ� ��� 
        }
        if (chk3 == 1) {
            go_to = 4;
            dir_leg1 = 0;    //�������� stop�ϱ� ���� ���ϴ� ȸ�������� 0���� ����
            glutTimerFunc(40, MyTimer, 6);  //Ÿ�̸� �ݹ��Լ� ��� 
        }
        if (chk4 == 1) {
            go_to = 5;
            dir_leg2 = 0;   //�������� stop�ϱ� ���� ���ϴ� ȸ�������� 0���� ����
            glutTimerFunc(40, MyTimer, 6);  //Ÿ�̸� �ݹ��Լ� ��� 
        }
        break;
    case 'R':
    case 'r':
        //���Ȱ� ��ٸ� �����̰� ���� 
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
    GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };     //���� �ֺ��ݻ�

    GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };     //0�� ���� Ư��
    GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };     //1�� ���� Ư��
    GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 };
    GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };    //��ü Ư��
    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat material_specular[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 25.0 };

    glShadeModel(GL_SMOOTH);    //���� ���̵�
    glEnable(GL_DEPTH_TEST);    //���� ���� Ȱ��ȭ
    glEnable(GL_LIGHTING);      //���� Ȱ��ȭ

    glEnable(GL_LIGHT0);        //0�� ���� Ȱ��ȭ
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);       //0�� ���� Ư���Ҵ�
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    glEnable(GL_LIGHT1);        //1�� ���� Ȱ��ȭ
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);       //1�� ���� Ư���Ҵ�
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);   //��ü Ư���Ҵ�
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //�����ֺ��ݻ�
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //��������
   
    //�ָ޴� ���� 
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    //���� pop-up menu�� �޴� �׸� �߰� 
    glutAddMenuEntry("Move head", 1);
    glutAddMenuEntry("Move right arm", 2);
    glutAddMenuEntry("Move left arm", 3);
    glutAddMenuEntry("Move right leg", 4);
    glutAddMenuEntry("Move left leg", 5);
    glutAddMenuEntry("Exit", 6);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //���콺 ������ ��ư ������, �� �޴��� �˾���
}


//Display Callback �Լ�
void MyDisplay(void) {
    GLfloat LightPosition0[] = { 0.0, 0.0, 2.0, 1.0 };      //0�� ������ġ

    GLfloat LightPosition1[] = { 1.0, 1.0, 1.0, 1.0 };      //1�� ������ġ
    GLfloat LightDirection1[] = { -0.5, -1.0, -1.0 };       //1�� ���� ����
    GLfloat SpotAngle1[] = { 20.0 };                        //1�� ���� ����

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); //���� ����
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // ������ �������� ȸ��
        glTranslatef(1.0, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
        glScalef(1.0, 1.2, 1.0);
        glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);      //��ġ�� ����
        glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);      //����Ʈ����Ʈ
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);   //����
        glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);           //����
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);                 //�ڻ��� �¼�
        glutSolidCube(1.0);

        glPushMatrix(); //�Ӹ� ���� 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // ������ �������� ȸ��
            glutSolidCube(0.5);
            glPopMatrix(); //�Ӹ� end

        glPushMatrix(); //������ ��1 ���� 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)arm1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //������ ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //������ ��2 end
            glPopMatrix();  //������ ��1 end

        glPushMatrix(); //���� ��1 ���� 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)arm2, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //���� ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //���� ��2 end
            glPopMatrix();  //���� ��1 end


        glPushMatrix(); //������ �ٸ�1 ���� 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)leg1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //������ �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //������ �ٸ�2 end
            glPopMatrix();  //������ �ٸ�1 end

        glPushMatrix(); //���� �ٸ�1 ���� 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)leg2, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //���� �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //���� �ٸ�2 end
            glPopMatrix();  //���� �ٸ�1 end
        glPopMatrix();  //���� end 

    glutSwapBuffers();
}


//Reshape Callback �Լ�
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Can Robot Modeling");
    MyInit();

    //Callback �Լ� ��� 
    glutDisplayFunc(MyDisplay);     //Display Callback �Լ�
    glutReshapeFunc(MyReshape);     //Reshape Callback �Լ�
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback �Լ�
    glutMainLoop();
    return 0;
}