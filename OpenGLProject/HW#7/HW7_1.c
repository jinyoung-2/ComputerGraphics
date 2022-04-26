/*************************************************************************/
/*													                     */
/*
    ���� ���� :
    - �ǽ�����4���� ������ �𵨸��� ���� ������ <����ĵ�κ�>�� ������ ���� ����� ����ǵ��� �߰� �����Ͻÿ�.
    - <R �Ǵ� r Ű�� ������> ���Ȱ� ��ٸ��� ������ ������ �޸��� ����� �ǰ��Ͻÿ�.
    - �κ��� ������ �����ÿ�.
    
    ���:
    - Keyboard Callback�Լ��� �̿��Ͽ� 'R' �Ǵ� 'r'�� ������ ��� �޸��� ����� ��Ÿ������ �Ѵ�.
    - glutPostdisplay()�� ȣ���Ͽ� ������ event �߻��� ������ ������ ���������� ����ǵ��� �Ѵ�.
    - glutInitDisplayMode()�� ���ڷ� GLUT_DOUBLE�� �̿��Ѵ�. Double buffering�� �̿��Ͽ� single buffering�� �������� ����ȿ���� �ذ��Ѵ�.
    - glutSwapBuffers()��  glutTimerFunc()�� ȣ���Ͽ� ����ؼ� Ÿ�̸� �̺�Ʈ�� ���������� �߻���Ų��.
        ����: GLUT Ÿ�̸Ӵ� �� �ѹ��� Ÿ���� ��Ȳ�� ���� back buffer�� front buffer�� ��ȯ�Ѵ�. Display function�� ���� �߰��Ѵ�.
    - Timer Callback �Լ� ������ �κп��̸� �̺�Ʈ�� �߻���Ų��.
    - ���� ȿ���� �����Ͽ� ��ü�� ��ü��, ��ǰ��� ǥ���Ѵ�.
*/
/************************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

static int body = 0, head = 0;
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //��Ȳ�� ���� ���� ȸ�� ������ ������ ���� 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;       //stop���� �����ϱ� ���� �ʿ��� ���� 
static int go_to = -1;

static double time = 0;  // �޸����� �� ����ϴ� ����
GLfloat rightArm1 = 0;      // ������ ���
GLfloat rightArm2 = 0;      // ������ ��
GLfloat leftArm1 = 0;       // ���� ���
GLfloat leftArm2 = 0;       // ���� ��
GLfloat rightLeg1 = 0;      // ���� �����
GLfloat rightLeg2 = 0;      // ���� ���Ƹ�
GLfloat leftLeg1 = 0;       // �� �����
GLfloat leftLeg2 = 0;       // �� ���Ƹ�


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
        rightArm1 += dir_arm1;       //���ο� ����
        //ȸ�� ����
        if (rightArm1 <= -45)
            dir_arm1 = 1;
        else if (rightArm1 >= 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
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
        leftArm1 += dir_arm2;       //���ο� ����
        //ȸ�� ����
        if (leftArm1 >= 45)
            dir_arm2 = -1;
        else if (leftArm1 == 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
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
        rightLeg1 += dir_leg1;       //���ο� ����
        //ȸ�� ����
        if (rightLeg1 <= -45)
            dir_leg1 = 1;
        else if (rightLeg1 == 0) {  //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
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
        leftLeg1 += dir_leg2;       //���ο� ����
        //ȸ�� ����
        if (leftLeg1 >= 45)
            dir_leg2 = -1;
        else if (leftLeg1 == 0) {   //ó����ġ�� ��� chk���� ������ ���� -1�� ����(move->stop���� ��ȯ)
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
    else if (value == 7) {
        time = time + 0.1;
        glLoadIdentity();

        /*
        �κ��� ������ ���ӵ� : sin() �Լ� ���� ǥ����
        ������ ���ѹ��� : abs() �Լ� ���� ������
        */
        body = -fabs(sin(time) * 10 + 5);           //���� ��������(abs���밪�� �����ν� ������ �ڷβ����� �ʴ� �Ѱ����� ����) 
        head = -fabs(sin(time) * 60 + 50);          //�Ӹ� ��������(abs���밪�� �����ν� �Ӹ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

        leftArm1 = sin(time) * 60;                  //������ 60�� �������� �����̵��� ���� & sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
        rightArm1 = leftArm1;                       //�������� ���ȹݴ�� 60���������� �����̵��� ���� & sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
        rightArm2 = -fabs(sin(time) * 60 + 50);     //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
        leftArm2 = -fabs(-sin(time) * 60 + 50);     //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

        rightLeg2 = fabs(-sin(time) * 30 - 30);     //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
        leftLeg2 = fabs(sin(time) * 30 - 30);       //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
        rightLeg1 = sin(time) * 60;                 //�����ٸ��� 60�� �������� �����̵��� ���� & sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
        leftLeg1 = rightLeg1;                       //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵��� ���� & sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

        glutPostRedisplay();
        glutSwapBuffers();

        glutTimerFunc(200, MyTimer, 7);

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
        glutTimerFunc(200, MyTimer, 7); //Ÿ�̸� �Լ�
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// �ʱ�ȭ 
void MyInit(void) {
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.3, 0, 0, 1.0 };          //�̾��� ������ �߰� 
    //GLfloat local_view[] = { 0.0 }; 

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    //���� Ư�� ���� 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //���� �� 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //���� �ֺ� ���� �� ����
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //������ ������ġ 

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
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
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_ambient_color[] = { 0.7, 0.6, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.2, 0.6, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = { 0.5, 0.1, 0.2, 0.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.0,0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.2);	//������ȯ
    glPushMatrix(); //���� ����
        glTranslatef(-1.0, 0.0, 0.0);	 // Pivot ���� �� ��ü �̵�
        glRotatef((GLfloat)body, 0.0, 0.0, 1.0); // ������ �������� ȸ��
        glTranslatef(1.0, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
        glScalef(1.0, 1.2, 1.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);             //�ֺ��� ���: �ֺ� �ݻ翡 ���� ��ü��
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);        //���ݻ籤 ���: ���ݻ翡 ���� ��ü��
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);            //���ݻ籤 ���: ���ݻ翡 ���� ��ü�� 
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);     //���ݻ��� ���� ���
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);            //��ü�� �߱��� 
        glutSolidCube(1.0);

        glPushMatrix(); //�Ӹ� ���� 
            glTranslatef(0.0, 0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef((GLfloat)head, 0.0, 0.5, 0.0); // ������ �������� ȸ��
            glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPopMatrix(); //�Ӹ� end

        glPushMatrix(); //������ ��1 ���� 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            //glRotatef((GLfloat)rightArm1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glRotatef(rightArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //������ ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(rightArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
                glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
                glutSolidCube(0.5);
                glPopMatrix();  //������ ��2 end
            glPopMatrix();  //������ ��1 end

        glPushMatrix(); //���� ��1 ���� 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            //glRotatef((GLfloat)leftArm1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glRotatef(leftArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //���� ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(leftArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
                glutSolidCube(0.5);
                glPopMatrix();  //���� ��2 end
            glPopMatrix();  //���� ��1 end


        glPushMatrix(); //������ �ٸ�1 ���� 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            //glRotatef((GLfloat)rightLeg1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glRotatef(rightLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //������ �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(rightLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
                glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
                glutSolidCube(0.5);
                glPopMatrix();  //������ �ٸ�2 end
            glPopMatrix();  //������ �ٸ�1 end

        glPushMatrix(); //���� �ٸ�1 ���� 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            //glRotatef((GLfloat)leftLeg1, 0.0, 0.0, 1.0); // ������ �������� ȸ��
            glRotatef(leftLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            glutSolidCube(0.5);
            glPushMatrix(); //���� �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(leftLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
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
