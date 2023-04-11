/* #include <windows.h>  //<-- od wersji 3.7 glut sam �aduje t� bibliotek� w potrzebie*/
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h> //przed dwoma nast�pnymi ze wzgl�du na windows.h
#include <GL/gl.h>
#include <GL/glu.h>
//---------------------------------------------------------------------------
float tX =  2.0f, tY =  0.0f, tZ = -10.f; //translacja matrycy
float rA =  0.0f, rX =  0.0f, rY =  0.0f, rZ = -1.0f; //obr�t tej�e

// Szeroko�� (X) i wysoko�� (Y) naszego okna:
int windowX, windowY;
int MouseBtt;
float tmpX, tmpY;

void Q(void) //rywujemy pojedyncza karte (idiotycznie banalne, ale dziala :P)
{
glBegin(GL_QUADS);
                 glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);

		 glColor3f(1.0f,0.5f,0.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);

		 glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);

		 glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);

		 glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);

		 glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
                glVertex3f( 1.0f,-1.0f,-1.0f);

glEnd();
}


//Funkcja Display zajmuje si� wy�wietlaniem:
void Display(void)
{
glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glPushMatrix();

 glTranslatef(tX, tY, tZ);
 glRotatef(rA, rX, rY, rZ);
   Q();

glPopMatrix();

glFlush();
glutSwapBuffers();
}



void Reshape(int x, int y) //zmiana roimziary okna
{
//ustawiamy zmienne globalne
windowX = x;
windowY = y;

glViewport(0, 0, windowX, windowY);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f, (float)windowX/(float)windowY, 0.01, 100); //setup perspektywy
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}


void Timer(int) //glut`owski timer...
{
//ustawiamy timer na 25milisec
glutTimerFunc(25, Timer, 0);

rA = ((int)++rA)%360; //zwiekszamy kat wzgledem wybranego (u nas [-1;-1;-1]) wektora
glutPostRedisplay();
}

void Mouse(int button,int state,int x, int y) //wcisniencia przyciskow myszy
{
MouseBtt = button;
if (state == GLUT_DOWN) //przycisk wcisniety?
 {
  if (button == GLUT_LEFT_BUTTON) //lewy? -obracamy
   {
    tmpX = x;
    tmpY = y;
    //cielsko
   }
  else if(button == GLUT_RIGHT_BUTTON)
   {
    //cielsko
   }
 }
}

void MouseMotion(int x,int y)//wywo�ywana przy przeci�ganiu (wcisniety przyciski i jednoczesna zmiana po�o�enia kursora)
{
if(MouseBtt == GLUT_LEFT_BUTTON)
 {
  tX += (x-tmpX)/20.0f;
  tY -= (y-tmpY)/20.0f;
  tmpX=x;
  tmpY=y;
 }
}

void Key(unsigned char key, int, int)//nasza obs�uga klawiatury
{
if(key == '+') tZ ++;
if(key == '-') tZ --;
}



int main(void)
{
/*funkcje biblioteki glut s� odpowiedzialne za przenosnosc kodu miedzy OSami (cross-platform)*/

// Inicjujemy OpenGL w trybie RGB i z podw�jnym buforowaniem:
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

// Ustawiamy rozmiar pocz�tkowy okna na 100 na 100:
glutInitWindowSize(100, 100);

// Tworzymy okno
glutCreateWindow("OpenGL - cross-platform na glucie by [KreciK]");

// Ustawiamy kolor, do kt�rego b�dzie czyszczony ekran funkcj� glClear();
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

// Ustawiamy odpowiednie funkcje do obs�ugi zdarze� [cross-platform]:
glutDisplayFunc(Display);
glutReshapeFunc(Reshape);
glutTimerFunc(25, Timer, 0);
glutMouseFunc(Mouse);
glutMotionFunc(MouseMotion);
glutKeyboardFunc(Key);

// W��czamy nasz program:
glutMainLoop();
}


//krecik.iglu.cz   //ANDER-KONSTRUKSZYN NA RAZIE   [od roku... :P]

