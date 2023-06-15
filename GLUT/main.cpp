//#include <windows.h>
//#include "../../../x86_libraries/GL/glut.h"

#ifdef __BORLANDC__
#include "./BCC/glut.h"
#pragma comment(lib,"BCC/glut32.lib")
#else
#include "./GCC/glut.h"
#pragma comment(lib,"GCC/glut32.lib")
#endif

//#pragma comment(lib,"lopengl32")
//#pragma comment(lib,"lglu32")
// sta�e do obs�ugi menu podr�cznego
//#include <stdlib.h>

enum
{
    FULL_WINDOW, // aspekt obrazu - ca�e okno
    ASPECT_1_1, // aspekt obrazu 1:1
    WIRE_SPHERE, // kula
    WIRE_CONE, // sto�ek
    WIRE_CUBE, // sze�cian
    WIRE_TORUS, // torus
    WIRE_DODECAHEDRON, // dwunasto�cian
    WIRE_TEAPOT, // czajnik
    WIRE_OCTAHEDRON, // o�mio�cian
    WIRE_TETRAHEDRON, // czworo�cian
    WIRE_ICOSAHEDRON, // dwudziesto�cian
    EXIT // wyj�cie
};
 
// aspekt obrazu
 
int aspect = ASPECT_1_1;
 
// rodzaj obiektu
 
int object = WIRE_SPHERE;
 
// rozmiary bry�y obcinania
 
const GLdouble left = -40.0;
const GLdouble right = 40.0;
const GLdouble bottom = -70.0;
const GLdouble top = 70.0;
const GLdouble Near = 200.0;
const GLdouble Far = 70.0;
 
// wsp�czynnik skalowania
 
GLfloat scale = 1.0;
 
// k�ty obrotu
 
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
 
// przesuni�cie
 
GLfloat translatex = 0.0;
GLfloat translatey = 0.0;
 
// wska�nik naci�ni�cia lewego przycisku myszki
 
int button_state = GLUT_UP;

// po�o�enie kursora myszki
 
int button_x, button_y;
 
// funkcja generuj�ca scen� 3D
 
void DrawCube(int x, int y, int z, int c)
{
    glTranslatef(x, y, z);
    glColor3f(0.0f, 0.0f, c);
    glutSolidCube(1);
    glTranslatef(-x, -y, -z);
 
}
 
void DrawWireCube(int x, int y, int z, int c)
{
    glTranslatef(x, y, z);
    glColor3f(0.0f, c, 0.0f);
    glutWireCube(1);
    glTranslatef(-x, -y, -z);
}
 
int tab[20][20] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0 },
    { 0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0 },
    { 0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0 },
    { 0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,1,1,1,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0 },
    { 0,0,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,1,0 },
    { 0,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0 },
    { 0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0 },
    { 0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0 },
    { 0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0 },
    { 0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0 },
    { 0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};
 
void DrawBoard()
{
    for (int i = -10; i < 10; ++i)
    {
        for (int j = -10; j < 10; ++j)
        {
            if (tab[i + 10][j + 10] == 0)
            {
                DrawCube(i, j, 0, 1);
                DrawWireCube(i, j, 0, 1);
            }
            else
            {
                DrawCube(i, j, 0, 0);
            }
        }
    }
 
    for (int i = -10; i < 10; ++i)
    {
        for (int j = -10; j < 10; ++j)
        {
            if (tab[i + 10][j + 10] == 0)
            {
                DrawCube(i, j, 1, 1);
                DrawWireCube(i, j, 1, 1);
            }
        }
    }
 
    for (int i = -10; i < 10; ++i)
    {
        for (int j = -10; j < 10; ++j)
        {
            if (tab[i + 10][j + 10] == 0)
            {
                DrawCube(i, j, 2, 1);
                DrawWireCube(i, j, 2, 1);
            }
        }
    }
}
 
void Display()
{
    // kolor t�a - zawarto�� bufora koloru
    glClearColor(1.0, 1.0, 1.0, 1.0);
 
    // czyszczenie bufora koloru
    glClear(GL_COLOR_BUFFER_BIT);
 
    // wyb�r macierzy modelowania
    glMatrixMode(GL_MODELVIEW);
 
    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();
 
    // przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
    glTranslatef(0, 0, -(Near + Far) / 2);
 
    // przesuni�cie obiektu - ruch myszk�
    glTranslatef(translatex, translatey, 0.0);
 
    // skalowanie obiektu - klawisze "+" i "-"
    glScalef(scale, scale, scale);
 
    // obroty obiektu - klawisze kursora
    glRotatef(rotatex, 1.0, 0, 0);
    glRotatef(rotatey, 0, 1.0, 0);
 
    DrawBoard();
 
    // skierowanie polece� do wykonania
    glFlush();
 
    // zamiana bufor�w koloru
    glutSwapBuffers();
}
 
// zmiana wielko�ci okna
 
void Reshape(int width, int height)
{
    // obszar renderingu - ca�e okno
    glViewport(0, 0, width, height);
 
    // wyb�r macierzy rzutowania
    glMatrixMode(GL_PROJECTION);
 
    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();
 
    // parametry bry�y obcinania
    if (aspect == ASPECT_1_1)
    {
        // wysoko�� okna wi�ksza od wysoko�ci okna
        if (width < height && width > 0)
            glFrustum(left, right, bottom * height / width, top * height / width, Near, Far);
        else
 
            // szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
            if (width >= height && height > 0)
                glFrustum(left * width / height, right * width / height, bottom, top, Near, Far);
 
    }
    else
        glFrustum(left, right, bottom, top, Near, Far);
 
    // generowanie sceny 3D
    Display();
}
 
// obs�uga klawiatury
 
void Keyboard(unsigned char key, int x, int y)
{
    // klawisz +
    if (key == '+')
        scale += 0.1;
    else
 
        // klawisz -
        if (key == '-' && scale > 0.1)
            scale -= 0.1;
 
    // odrysowanie okna
    Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
 
// obs�uga klawiszy funkcyjnych i klawiszy kursora
 
void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        // kursor w lewo
    case GLUT_KEY_LEFT:
        rotatey -= 1;
        break;
 
        // kursor w g�r�
    case GLUT_KEY_UP:
        rotatex -= 1;
        break;
 
        // kursor w prawo
    case GLUT_KEY_RIGHT:
        rotatey += 1;
        break;
 
        // kursor w d�
    case GLUT_KEY_DOWN:
        rotatex += 1;
        break;
    }
 
    // odrysowanie okna
    Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
 
// obs�uga przycisk�w myszki
 
void MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        // zapami�tanie stanu lewego przycisku myszki
        button_state = state;
 
        // zapami�tanie po�o�enia kursora myszki
        if (state == GLUT_DOWN)
        {
            button_x = x;
            button_y = y;
        }
    }
}
 
// obs�uga ruchu kursora myszki
 
void MouseMotion(int x, int y)
{
    if (button_state == GLUT_DOWN)
    {
        translatex += 1.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
        button_x = x;
        translatey += 1.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
        button_y = y;
        glutPostRedisplay();
    }
}
 
// obs�uga menu podr�cznego
 
void Menu(int value)
{
    switch (value)
    {
        // obszar renderingu - ca�e okno
    case FULL_WINDOW:
        aspect = FULL_WINDOW;
        Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
 
        // obszar renderingu - aspekt 1:1
    case ASPECT_1_1:
        aspect = ASPECT_1_1;
        Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
 
        // kula
    case WIRE_SPHERE:
        object = WIRE_SPHERE;
        Display();
        break;
 
        // cylinder
    case WIRE_CONE:
        object = WIRE_CONE;
        Display();
        break;
 
        // sze�cian
    case WIRE_CUBE:
        object = WIRE_CUBE;
        Display();
        break;
 
        // torus
    case WIRE_TORUS:
        object = WIRE_TORUS;
        Display();
        break;
 
        // dwunasto�cian
    case WIRE_DODECAHEDRON:
        object = WIRE_DODECAHEDRON;
        Display();
        break;
 
        // czajnik
    case WIRE_TEAPOT:
        object = WIRE_TEAPOT;
        Display();
        break;
 
        // o�mio�cian
    case WIRE_OCTAHEDRON:
        object = WIRE_OCTAHEDRON;
        Display();
        break;
 
        // czworo�cian
    case WIRE_TETRAHEDRON:
        object = WIRE_TETRAHEDRON;
        Display();
        break;
 
        // dwudziesto�cian
    case WIRE_ICOSAHEDRON:
        object = WIRE_ICOSAHEDRON;
        Display();
        break;
 
        // wyj�cie
    case EXIT:
        exit(0);
    }
}
 
int main(int argc, char * argv[])
{
    // inicjalizacja biblioteki GLUT
    glutInit(&argc, argv);
 
    // inicjalizacja bufora ramki
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // rozmiary g��wnego okna programu
    glutInitWindowSize(400, 400);
 
    // utworzenie g��wnego okna programu
#ifdef WIN32
 
    glutCreateWindow("Przekszta�cenia");
#else
 
    glutCreateWindow("Przeksztalcenia");
#endif
 
    // do��czenie funkcji generuj�cej scen� 3D
    glutDisplayFunc(Display);
 
    // do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
    glutReshapeFunc(Reshape);
 
    // do��czenie funkcji obs�ugi klawiatury
    glutKeyboardFunc(Keyboard);
 
    // do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
    glutSpecialFunc(SpecialKeys);
 
    // obs�uga przycisk�w myszki
    glutMouseFunc(MouseButton);
 
    // obs�uga ruchu kursora myszki
    glutMotionFunc(MouseMotion);
 
    // utworzenie podmenu - aspekt obrazu
    int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32
 
    glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
#else
 
    glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif
 
    glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
 
    // utworzenie podmenu - obiekt
    int MenuObject = glutCreateMenu(Menu);
    glutAddMenuEntry("Kula", WIRE_SPHERE);
#ifdef WIN32
 
    glutAddMenuEntry("Sto�ek", WIRE_CONE);
    glutAddMenuEntry("Sze�cian", WIRE_CUBE);
    glutAddMenuEntry("Torus", WIRE_TORUS);
    glutAddMenuEntry("Dwunasto�cian", WIRE_DODECAHEDRON);
    glutAddMenuEntry("Czajnik", WIRE_TEAPOT);
    glutAddMenuEntry("O�mio�cian", WIRE_OCTAHEDRON);
    glutAddMenuEntry("Czworo�cian", WIRE_TETRAHEDRON);
    glutAddMenuEntry("Dwudziesto�cian", WIRE_ICOSAHEDRON);
#else
 
    glutAddMenuEntry("Stozek", WIRE_CONE);
    glutAddMenuEntry("Szescian", WIRE_CUBE);
    glutAddMenuEntry("Torus", WIRE_TORUS);
    glutAddMenuEntry("Dwunastoscian", WIRE_DODECAHEDRON);
    glutAddMenuEntry("Czajnik", WIRE_TEAPOT);
    glutAddMenuEntry("Osmioscian", WIRE_OCTAHEDRON);
    glutAddMenuEntry("Czworoscian", WIRE_TETRAHEDRON);
    glutAddMenuEntry("Dwudziestoscian", WIRE_ICOSAHEDRON);
#endif
 
    // menu g��wne
    glutCreateMenu(Menu);
    glutAddSubMenu("Aspekt obrazu", MenuAspect);
    glutAddSubMenu("Obiekt", MenuObject);
#ifdef WIN32
 
    glutAddMenuEntry("Wyj�cie", EXIT);
#else
 
    glutAddMenuEntry("Wyjscie", EXIT);
#endif
 
    // okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
    glutAttachMenu(GLUT_RIGHT_BUTTON);
 
    // wprowadzenie programu do obs�ugi p�tli komunikat�w
    glutMainLoop();
    return 0;
} 
