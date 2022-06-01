/*************************************************************************/
/*				   HW#8   : ������ �𵨸��� �̿��� ���� �κ� ����        */
/*													                     */
/*
    ���� ���� :
    - ���ݱ��� ��� OpenGL�� �پ��� ����� �̿��Ͽ� ���� �κ� ��ü�� �����Ѵ�. 

    ���:
    1. �޴������ ���� �κ��� ��ü(�Ӹ�, ����, ����, ��ٸ�)�� ������ �� �ֵ��� �Ѵ�.
    2. Ű���� �Է��� ���� �����̴� �κ��� ��ü�� ���߰� �ϰ�, �κ��� �޸����� �ϰ�, ������ȯ�� �� �� �ֵ��� �Ѵ�.
    3. �������� ���� ���α׷��� ó�� ����� ��, �κ��� �����̸鼭 ���� ���� ��������� �Ѵ�.
    4. Texture Mapping ����� ���� �κ��� ���� ���� �̹����� �����Ѵ�.
*/
/************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>
#include <stdio.h>

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")


static int body = 0, head = 0;
static int dir_head = 1, dir_arm1 = -1, dir_arm2 = 1, dir_leg1 = -1, dir_leg2 = 1;  //��Ȳ�� ���� ���� ȸ�� ������ ������ ���� 
static int chk0 = -1, chk1 = -1, chk2 = -1, chk3 = -1, chk4 = -1;                   //stop���� �����ϱ� ���� �ʿ��� ���� 
static int go_to = -1;

static double time = 0;     // �޸����� �� ����ϴ� ����
GLfloat rightArm1 = 0;      // ������ ���
GLfloat rightArm2 = 0;      // ������ ��
GLfloat leftArm1 = 0;       // ���� ���
GLfloat leftArm2 = 0;       // ���� ��
GLfloat rightLeg1 = 0;      // ���� �����
GLfloat rightLeg2 = 0;      // ���� ���Ƹ�
GLfloat leftLeg1 = 0;       // �� �����
GLfloat leftLeg2 = 0;       // �� ���Ƹ�

// ���α׷� �����, �κ��� ������ �����ϴ� ���� 
GLfloat transRightArm = -0.1;       // ������ ���
GLfloat transLeftArm = 0.1;         // ���� ���
GLfloat transRightLeg = -0.05;      // ������ �����
GLfloat transLeftLeg = 0.05;        // ���� �����

// ���� ���� ���� 
GLfloat rx = 0.0, gx = 0.0, bx = 0.0;

//������ Camera��ġ ��������
GLfloat cx = 0.0, cy = 0.0, cz = 0.0;


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
        
        if (time <= 30.0){
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

            glutTimerFunc(100, MyTimer, 7);
        }
        else {      //�ʱ���·� ���ư��� ���� 
            body = 0.0;
            head = 0.0;
            rightArm1 = 0.0;
            rightArm2 = 0.0;
            leftArm1 = 0.0;
            leftArm2 = 0.0;
            rightLeg1 = 0.0;
            rightLeg2 = 0.0;
            leftLeg1 = 0.0;
            leftLeg2 = 0.0;
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
    else if (entryID == 6) {
        head = 0.0;
        body = 0.0;
        rightArm1 = 0.0;
        rightArm2 = 0.0;
        leftArm1 = 0.0;
        leftArm2 = 0.0;
        rightLeg1 = 0.0;
        rightLeg2 = 0.0;
        leftLeg1 = 0.0;
        leftLeg2 = 0.0;
    }
    else if (entryID == 7)       //�ָ޴����� exit ������ ���
        exit(0);                //����

    glutPostRedisplay();        //Display Event ���� �߻���Ŵ 
}

//KeyBoard Callback �Լ�
void MyKeyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'S':   //�����̴� ��ü�� ����
    case 's':
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
        time = 0.0;
        glutTimerFunc(200, MyTimer, 7); //Ÿ�̸� �Լ�
        break;
    case 'z':   // Camera�� X�� ��ǥ�� 0.1�� ���������� ����  
    case 'Z':
        if (cx <= 2.7)
            cx += 0.1;
        break;
    case 'x':   // Camera�� X�� ��ǥ�� 0.1�� ���������� ����
    case 'X':
        if (cx >= -2.7)
            cx -= 0.1;
        break;
    case 'c':   // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'C':
        if (cy <= 2.7)
            cy += 0.1;
        break;
    case 'v':   // Camera�� Y�� ��ǥ�� 0.1�� ���������� ����
    case 'V':
        if (cy >= -2.7)
            cy -= 0.1;
        break;
    case 'b':   // Camera�� Z�� ��ǥ�� 0.1�� ���������� ���� 
    case 'B':
        if (cz <= 2.0)
            cz += 0.1;
        break;  
    case 'n':   // Camera�� Z�� ��ǥ�� 0.1�� ���������� ����  
    case 'N':
        if (cz >= -2.0)
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

// �ڵ� Texture Mapping 
AUX_RGBImageRec* LoadBMP(char* Filename) {
    FILE* File = NULL;
    if (!Filename) return NULL;
    fopen_s(&File, Filename, "r");

    // seFilename�� �����ڵ� ��Ʈ������ �ٲٱ�
    int size = strlen(Filename);
    wchar_t* w_Filename = new wchar_t[size];

    for (int i = 0; i < size; ++i)  w_Filename[i] = Filename[i];
    w_Filename[size] = NULL;

    if (File) {
        fclose(File);
        return auxDIBImageLoad(w_Filename);     //���Ϸκ��� �޸𸮷�
    }
    return NULL;
}

int Texture() {
    int Status = FALSE;
    AUX_RGBImageRec* TxtImg[1];
    memset(TxtImg, 0, sizeof(void*) * 1);

    if (TxtImg[0] = LoadBMP((char*)"fruit.bmp")) {
        Status = TRUE;

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TxtImg[0]->sizeX, TxtImg[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TxtImg[0]->data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    }

    if (TxtImg[0]) {
        if (TxtImg[0]->data) {
            free(TxtImg[0]->data);
        }

        free(TxtImg[0]);
    }

    return Status;
}

// �ʱ�ȭ 
void MyInit(void) {
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.3, 0, 0, 1.0 };          //�̾��� ������ �߰� 

    Texture();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
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
    glutAddMenuEntry("Initialize", 6);
    glutAddMenuEntry("Exit", 7);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //���콺 ������ ��ư ������, �� �޴��� �˾���
}


// ���α׷� ����� �ʱ� ���� ���� �Լ� 
void MyTimer2(int value) {
    rx += 0.01;
    gx += 0.01; 
    bx += 0.01;
    if(rx <=3.0)
        glutTimerFunc(300, MyTimer2, value);

    glutPostRedisplay();        //Display Event ���� �߻���Ŵ 
}


// ���α׷� ����� �ʱ� �κ��� �����ӿ� ���� �Լ� 
void MyTimer3(int value) {
    if (rightArm1 == 1.0) {
        transRightArm = -0.1;      // ������ ���
        transLeftArm = 0.1;        // ���� ���
        transRightLeg = -0.05;      // ������ �����
        transLeftLeg = 0.05;        // ���� �����
    }
    else if (rightArm1 == -1.0) {
        transRightArm = 0.1;
        transLeftArm = -0.1;
        transRightLeg = 0.05;      // ������ �����
        transLeftLeg = -0.05;        // ���� �����
    }


    //��迡 �ε����� �ʰ�, ��� ���̿��� �̵��ϴ� ��� 
    rightArm1 += transRightArm;
    leftArm1 += transLeftArm;
    rightLeg1 += transRightLeg;
    leftLeg1 += transLeftLeg;

    if(rx <= 0.8)
        glutTimerFunc(20, MyTimer3, value);

    glutPostRedisplay();        //Display Event ���� �߻���Ŵ 
}

//Display Callback �Լ�
void MyDisplay(void) {

    GLfloat no_mat[] = { 0.0 + rx, 0.0 + gx, 0.0 + bx, 1.0 };
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

    gluLookAt(1.0+cx,0.5+cy, 5.0+cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.2);	//������ȯ
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
            glutSolidCube(0.5);
            glPopMatrix(); //�Ӹ� end

        glPushMatrix(); //������ ��1 ���� 
            glTranslatef(-0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef(rightArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //������ ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(rightArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //������ ��2 end
            glPopMatrix();  //������ ��1 end

        glPushMatrix(); //���� ��1 ���� 
            glTranslatef(0.6, 0.2, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef(leftArm1, 0.0, 0.0, 1.0);
            glScalef(0.5, 0.8, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //���� ��2 ����
                glTranslatef(0.0, -0.3, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(leftArm2, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //���� ��2 end
            glPopMatrix();  //���� ��1 end


        glPushMatrix(); //������ �ٸ�1 ���� 
            glTranslatef(-0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef(rightLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //������ �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(rightLeg2, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);	// Pivot���� ������ ��ġ�� �������� �̵�
                glutSolidCube(0.5);
                glPopMatrix();  //������ �ٸ�2 end
            glPopMatrix();  //������ �ٸ�1 end

        glPushMatrix(); //���� �ٸ�1 ���� 
            glTranslatef(0.3, -0.7, 0.0);	 // Pivot ���� �� ��ü �̵�
            glRotatef(leftLeg1, 0.0, 0.0, 1.0);
            glScalef(0.6, 0.9, 1.0);
            glutSolidCube(0.5);
            glPushMatrix(); //���� �ٸ�2 ����
                glTranslatef(-0.5, -0.5, 0.0);	 // Pivot ���� �� ��ü �̵�
                glRotatef(leftLeg2, 0.0, 0.0, 1.0);
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
    glutTimerFunc(2000,MyTimer2,1); //���� Timer Callback �Լ�
    glutTimerFunc(2000, MyTimer3, 1);   //������ Timer Callback �Լ�
    glutMainLoop();
    return 0;
}