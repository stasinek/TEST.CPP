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
// sta³e do obs³ugi menu podrêcznego
//#include <stdlib.h>

enum
{
    FULL_WINDOW, // aspekt obrazu - ca³e okno
    ASPECT_1_1, // aspekt obrazu 1:1
    WIRE_SPHERE, // kula
    WIRE_CONE, // sto¿ek
    WIRE_CUBE, // szeœcian
    WIRE_TORUS, // torus
    WIRE_DODECAHEDRON, // dwunastoœcian
    WIRE_TEAPOT, // czajnik
    WIRE_OCTAHEDRON, // oœmioœcian
    WIRE_TETRAHEDRON, // czworoœcian
    WIRE_ICOSAHEDRON, // dwudziestoœcian
    EXIT // wyjœcie
};
 
// aspekt obrazu
 
int aspect = ASPECT_1_1;
 
// rodzaj obiektu
 
int object = WIRE_SPHERE;
 
// rozmiary bry³y obcinania
 
const GLdouble left = -40.0;
const GLdouble right = 40.0;
const GLdouble bottom = -70.0;
const GLdouble top = 70.0;
const GLdouble Near = 200.0;
const GLdouble Far = 70.0;
 
// wspó³czynnik skalowania
 
GLfloat scale = 1.0;
 
// k¹ty obrotu
 
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
 
// przesuniêcie
 
GLfloat translatex = 0.0;
GLfloat translatey = 0.0;
 
// wskaŸnik naciœniêcia lewego przycisku myszki
 
int button_state = GLUT_UP;

// po³o¿enie kursora myszki
 
int button_x, button_y;
 
// funkcja generuj¹ca scenê 3D
 
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
    // kolor t³a - zawartoœæ bufora koloru
    glClearColor(1.0, 1.0, 1.0, 1.0);
 
    // czyszczenie bufora koloru
    glClear(GL_COLOR_BUFFER_BIT);
 
    // wybór macierzy modelowania
    glMatrixMode(GL_MODELVIEW);
 
    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();
 
    // przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
    glTranslatef(0, 0, -(Near + Far) / 2);
 
    // przesuniêcie obiektu - ruch myszk¹
    glTranslatef(translatex, translatey, 0.0);
 
    // skalowanie obiektu - klawisze "+" i "-"
    glScalef(scale, scale, scale);
 
    // obroty obiektu - klawisze kursora
    glRotatef(rotatex, 1.0, 0, 0);
    glRotatef(rotatey, 0, 1.0, 0);
 
    DrawBoard();
 
    // skierowanie poleceñ do wykonania
    glFlush();
 
    // zamiana buforów koloru
    glutSwapBuffers();
}
 
// zmiana wielkoœci okna
 
void Reshape(int width, int height)
{
    // obszar renderingu - ca³e okno
    glViewport(0, 0, width, height);
 
    // wybór macierzy rzutowania
    glMatrixMode(GL_PROJECTION);
 
    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();
 
    // parametry bry³y obcinania
    if (aspect == ASPECT_1_1)
    {
        // wysokoœæ okna wiêksza od wysokoœci okna
        if (width < height && width > 0)
            glFrustum(left, right, bottom * height / width, top * height / width, Near, Far);
        else
 
            // szerokoœæ okna wiêksza lub równa wysokoœci okna
            if (width >= height && height > 0)
                glFrustum(left * width / height, right * width / height, bottom, top, Near, Far);
 
    }
    else
        glFrustum(left, right, bottom, top, Near, Far);
 
    // generowanie sceny 3D
    Display();
}
 
// obs³uga klawiatury
 
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
 
// obs³uga klawiszy funkcyjnych i klawiszy kursora
 
void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        // kursor w lewo
    case GLUT_KEY_LEFT:
        rotatey -= 1;
        break;
 
        // kursor w górê
    case GLUT_KEY_UP:
        rotatex -= 1;
        break;
 
        // kursor w prawo
    case GLUT_KEY_RIGHT:
        rotatey += 1;
        break;
 
        // kursor w dó³
    case GLUT_KEY_DOWN:
        rotatex += 1;
        break;
    }
 
    // odrysowanie okna
    Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
 
// obs³uga przycisków myszki
 
void MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        // zapamiêtanie stanu lewego przycisku myszki
        button_state = state;
 
        // zapamiêtanie po³o¿enia kursora myszki
        if (state == GLUT_DOWN)
        {
            button_x = x;
            button_y = y;
        }
    }
}
 
// obs³uga ruchu kursora myszki
 
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
 
// obs³uga menu podrêcznego
 
void Menu(int value)
{
    switch (value)
    {
        // obszar renderingu - ca³e okno
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
 
        // szeœcian
    case WIRE_CUBE:
        object = WIRE_CUBE;
        Display();
        break;
 
        // torus
    case WIRE_TORUS:
        object = WIRE_TORUS;
        Display();
        break;
 
        // dwunastoœcian
    case WIRE_DODECAHEDRON:
        object = WIRE_DODECAHEDRON;
        Display();
        break;
 
        // czajnik
    case WIRE_TEAPOT:
        object = WIRE_TEAPOT;
        Display();
        break;
 
        // oœmioœcian
    case WIRE_OCTAHEDRON:
        object = WIRE_OCTAHEDRON;
        Display();
        break;
 
        // czworoœcian
    case WIRE_TETRAHEDRON:
        object = WIRE_TETRAHEDRON;
        Display();
        break;
 
        // dwudziestoœcian
    case WIRE_ICOSAHEDRON:
        object = WIRE_ICOSAHEDRON;
        Display();
        break;
 
        // wyjœcie
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
 
    // rozmiary g³ównego okna programu
    glutInitWindowSize(400, 400);
 
    // utworzenie g³ównego okna programu
#ifdef WIN32
 
    glutCreateWindow("Przekszta³cenia");
#else
 
    glutCreateWindow("Przeksztalcenia");
#endif
 
    // do³¹czenie funkcji generuj¹cej scenê 3D
    glutDisplayFunc(Display);
 
    // do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
    glutReshapeFunc(Reshape);
 
    // do³¹czenie funkcji obs³ugi klawiatury
    glutKeyboardFunc(Keyboard);
 
    // do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
    glutSpecialFunc(SpecialKeys);
 
    // obs³uga przycisków myszki
    glutMouseFunc(MouseButton);
 
    // obs³uga ruchu kursora myszki
    glutMotionFunc(MouseMotion);
 
    // utworzenie podmenu - aspekt obrazu
    int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32
 
    glutAddMenuEntry("Aspekt obrazu - ca³e okno", FULL_WINDOW);
#else
 
    glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif
 
    glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
 
    // utworzenie podmenu - obiekt
    int MenuObject = glutCreateMenu(Menu);
    glutAddMenuEntry("Kula", WIRE_SPHERE);
#ifdef WIN32
 
    glutAddMenuEntry("Sto¿ek", WIRE_CONE);
    glutAddMenuEntry("Szeœcian", WIRE_CUBE);
    glutAddMenuEntry("Torus", WIRE_TORUS);
    glutAddMenuEntry("Dwunastoœcian", WIRE_DODECAHEDRON);
    glutAddMenuEntry("Czajnik", WIRE_TEAPOT);
    glutAddMenuEntry("Oœmioœcian", WIRE_OCTAHEDRON);
    glutAddMenuEntry("Czworoœcian", WIRE_TETRAHEDRON);
    glutAddMenuEntry("Dwudziestoœcian", WIRE_ICOSAHEDRON);
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
 
    // menu g³ówne
    glutCreateMenu(Menu);
    glutAddSubMenu("Aspekt obrazu", MenuAspect);
    glutAddSubMenu("Obiekt", MenuObject);
#ifdef WIN32
 
    glutAddMenuEntry("Wyjœcie", EXIT);
#else
 
    glutAddMenuEntry("Wyjscie", EXIT);
#endif
 
    // okreœlenie przycisku myszki obs³uguj¹cego menu podrêczne
    glutAttachMenu(GLUT_RIGHT_BUTTON);
 
    // wprowadzenie programu do obs³ugi pêtli komunikatów
    glutMainLoop();
    return 0;
} 
