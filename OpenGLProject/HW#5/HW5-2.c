/*************************************************************************/
/*													                     */
/*
    ���� ���� :
    ?  �ǽ�����4���� ������ �𵨸� ����� ���� ������ <����ĵ�κ�>���� �����Ͽ� �پ��� �������� �𵨸��� ��ü�� ������ �� �ְ��Ѵ�.
    ?  Special KeyBoard key�� F1�� ������, ���ڸ� �����·� ���ƿ����� �����Ѵ�. ����, �پ��� �������� �𵨸��� ��ü�� ������ �� �������·� ���ƿ��� ���� �� F1�� ������.  
    ?  KeyBoard key���� glutLookAt( )�� ���ڰ��� �����Ų��.
    ?  Menu���� �����̴� ����� �� ���̰� ������ �����Ų��. 

    ���:
    ?  Menu callback()�� ȣ���Ͽ� �޴� ���ÿ� ���� ������ �����Ų��.
    ?  Keyboard Callback�Լ��� �̿��Ͽ� �ش� keyboard key�� ������ ��� ������ �´� ������ ����ǵ��� �Ѵ�.
    ?  glutPostdisplay()�� ȣ���Ͽ� ������ event �߻��� ������ ������ ���������� ����ǵ��� �Ѵ�.
    ?  glutInitDisplayMode()�� ���ڷ� GLUT_DOUBLE�� �̿��Ѵ�. Double buffering�� �̿��Ͽ� single buffering�� �������� ����ȿ���� �ذ��Ѵ�.
    ?  glutSwapBuffers()�� ���� ��Ȳ�� ���� back buffer�� front buffer�� ��ȯ�Ѵ�. Display function�� ���� �߰��Ѵ�.
    ?  Timer Callback �Լ� ������ �κп� glutTimerFunc()�� ȣ���Ͽ� ����ؼ� Ÿ�̸� �̺�Ʈ�� ���������� �߻���Ų��.
        ����: GLUT Ÿ�̸Ӵ� �� �ѹ��� Ÿ�̸� �̺�Ʈ�� �߻���Ų��.

    ?  glutLookAt()�Լ��� �̿��Ͽ� Camera�� ��ġ & Camera�� ����Ű�� ������ ��ġ & Camera�� ������� ������� ������ǥ�踦 ���� �����Ѵ�.

*/
/************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

static int body = 0, head = 0, arm1 = 0, arm2 = 0, leg1 = 0, leg2 = 0;  //ȸ�� ���� 
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //��Ȳ�� ���� ���� ȸ�� ������ ������ ���� 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop���� �����ϱ� ���� �ʿ��� ���� 
static int go_to = -1;

GLfloat cx = 0.0, cy = 0.0, cz = 0.0, fx = 0.0, fy = 0.0, fz = 0.0, ux = 0.0, uy = 0.0, uz = 0.0;   //glutLookAt()�Լ��� ���� ��ȭ�� ���� �������� ���

// ���� �׸���
void DrawGround()
{
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES);
    for (float x = -2.0; x <= 2.2; x += 0.2) {
        glVertex3f(x, -0.7, -2.0);
        glVertex3f(x, -0.7, 2.0);
    }

    for (float z = -2.0; z <= 2.2; z += 0.2) {
        glVertex3f(-2.0, -0.7, z);
        glVertex3f(2.0, -0.7, z);
    }
    glEnd();
}

//Timer Callback �Լ�
void MyTimer(int value)
{
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

        //ī�޶� ��ġ�� ������ġ�� ������� �����̴� �κ��� �ٶ󺸱�
        cy = cy + 0.01;
        fy = fy + 0.01;

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

        //ī�޶� ��ġ�� ������� �����̴� �������� �������� �κ��� �ٶ󺸱� 
        cz = cz - 0.001;
        cy = cy + 0.1;
        cx = cx - 0.15;

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

        //ī�޶� ��ġ�� ������� �����̴� ������ �������� �κ��� �ٶ󺸱� 
        cz = cz - 0.001;
        cy = cy + 0.1;
        cx = cx + 0.15;

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

        //ī�޶� ��ġ�� ������� �����̴� �����ʴٸ� �������� �κ��� �ٶ󺸱� 
        cz = cz + 0.001;
        cy = cy - 0.1;
        cx = cx - 0.15;

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

        //ī�޶� ��ġ�� ������� �����̴� ���ʴٸ� �������� �κ��� �ٶ󺸱� 
        cz = cz + 0.001;
        cy = cy - 0.1;
        cx = cx + 0.15;

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


        // Camera�� X�� ��ǥ�� 0.1�� ���������� ����  
    case 'q':
    case 'Q':
        cx += 0.1;
        break;

        // Camera�� X�� ��ǥ�� 0.1�� ���������� ����
    case 'w':
    case 'W':
        cx -= 0.1;
        break;

        // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'e':
    case 'E':
        cy += 0.1;
        break;

        // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'r':
    case 'R':
        cy -= 0.1;
        break;

        // Camera�� Z�� ��ǥ�� 0.1�� ���������� ���� 
    case 'd':
    case 'D':
        cz += 0.1;
        break;

        // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����
    case 'f':
    case 'F':
        cz -= 0.1;
        break;

        // ����(Focus)�� X�� ��ǥ�� 0.1�� ���������� ���� 
    case 't':
    case 'T':
        fx += 0.1;
        break;

        // ����(Focus)�� X�� ��ǥ�� 0.1�� ���������� ����
    case 'y':
    case 'Y':
        fx -= 0.1;
        break;

        // ����(Focus)�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'u':
    case 'U':
        fy += 0.1;
        break;

        // ����(Focus)�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'i':
    case 'I':
        fy -= 0.1;
        break;

        // ����(Focus)�� Z�� ��ǥ�� 0.1�� ���������� ����
    case 'o':
    case 'O':
        fz += 0.1;
        break;

        // ����(Focus)�� Z�� ��ǥ�� 0.1�� ���������� ����
    case 'p':
    case 'P':
        fz -= 0.1;
        break;

        // Camera ������� X�� ��ǥ�� 0.1�� ���������� ����  
    case 'z':
    case 'Z':
        ux += 0.1;
        break;

        // Camera ������� X�� ��ǥ�� 0.1�� ���������� ���� 
    case 'x':
    case 'X':
        ux -= 0.1;
        break;

        // Camera ������� Y�� ��ǥ�� 0.1�� ���������� ���� 
    case 'c':
    case 'C':
        uy += 0.1;
        break;

        // Camera ������� Y�� ��ǥ�� 0.1�� ���������� ���� 
    case 'v':
    case 'V':
        uy -= 0.1;
        break;

        // Camera ������� Z�� ��ǥ�� 0.1�� ���������� ���� 
    case 'b':
    case 'B':
        uz += 0.1;
        break;

        // Camera ������� Z�� ��ǥ�� 0.1�� ���������� ���� 
    case 'n':
    case 'N':
        uz -= 0.1;
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
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   // << �̰��� ���� ������ ȣ��ɶ����� ������ �� ������ �����ϱ�!


    //������ȯ
    gluLookAt(0.0 + cx, 0.0 + cy, 3.5 + cz, 0.0 + fx, 0.0 + fy, 0.0 + fz, 0.0 + ux, 1.0 + uy, 0.0 + uz);      //Camera�� ����Ű�� ������ ��ġ ��ȭ�� ���� ���� ���

    DrawGround();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);

      glPushMatrix(); //���� ����
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // ������ �������� ȸ��
        glTranslatef(1.0, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
        glScalef(1.0, 1.2, 1.0);
        glutWireCube(1.0);

        glPushMatrix(); //�Ӹ� ���� 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // ������ �������� ȸ��
            glutWireCube(0.5);
            glPopMatrix(); //�Ӹ� end

        glPushMatrix(); //������ ��1 ���� 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)arm1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.5, 0.8, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //������ ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutWireCube(0.5);
                glPopMatrix();  //������ ��2 end
            glPopMatrix();  //������ ��1 end
            
        glPushMatrix(); //���� ��1 ���� 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)arm2, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.5, 0.8, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //���� ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutWireCube(0.5);
                glPopMatrix();  //���� ��2 end
            glPopMatrix();  //���� ��1 end
  

        glPushMatrix(); //������ �ٸ�1 ���� 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)leg1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.6, 0.9, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //������ �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutWireCube(0.5);
                glPopMatrix();  //������ �ٸ�2 end
            glPopMatrix();  //������ �ٸ�1 end

        glPushMatrix(); //���� �ٸ�1 ���� 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)leg2, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glScalef(0.6, 0.9, 1.0);
            glutWireCube(0.5);
            glPushMatrix(); //���� �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutWireCube(0.5);
                glPopMatrix();  //���� �ٸ�2 end
            glPopMatrix();  //���� �ٸ�1 end
        glPopMatrix();  //���� end 

    glutSwapBuffers();
}


// Camera�� ��ġ ��ȭ�� ���� ��� ����  => glutLookAt()�Լ��� ���� �� Camera ��ġ �κ� ��ǥ ��ȭ
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {

    case GLUT_KEY_F1:   // �⺻ ���·� �ǵ��ư��� 
        cx = 0.0;
        cy = 0.0;
        break;

    case GLUT_KEY_UP:   //�� : ���� �������� �κ� �ٶ󺸱� 
        cy = 7.0;
        break;

    case GLUT_KEY_DOWN: //�� : �Ʒ��� �������� �κ� �ٶ󺸱�         
        cy = -7.0;
        break;

    case GLUT_KEY_LEFT: // �� : ������ ���� �������� �κ� �ٶ󺸱� 
        cx = -7.0;
        break;

    case GLUT_KEY_RIGHT:// �� : ���� ���� �������� �κ� �ٶ󺸱� 
        cx = 7.0;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}


//Reshape Callback �Լ�
void MyReshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);        // ���� ��� ���� ���
    glLoadIdentity();                   // ��� �ʱ�ȭ(CTM�� I�� ����)
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ModelView");
    MyInit();

    //Callback �Լ� ��� 
    glutDisplayFunc(MyDisplay);     //Display Callback �Լ�
    glutReshapeFunc(MyReshape);     //Reshape Callback �Լ�
    glutKeyboardFunc(MyKeyboard);   //KeyBoard Callback �Լ�
    glutSpecialFunc(MySpecialKeyboard); //Sepcial KeyBoard Callback �Լ� 
    glutMainLoop();
    return 0;
}
