#include <windows.h>
#include "main.h"
#include <gl/gl.h>
#include <stdio.h>
#include <stdlib.h>

HWND g_hMainDialog;
HWND Structure;
HWND About;
UINT KBcod;

// angle variables
float angx = 0.0f;
float angy = 0.0f;
float angz = 1.0f;
// grid variables
float Fx = 0.0f;
float Fy = 1.0f;
float Sx = 0.87f;
float Sy = -0.5f;
float Tx = -0.87f;
float Ty = -0.5f;
// speed
float theta = 0.0f;
float Spd = 1.0f;


BOOL CALLBACK OpenProc(HWND, UINT, WPARAM, LPARAM);
VOID EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC );
VOID DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC );

static char g_szClassName[] = "MyWindowClass";
static HINSTANCE g_hInst = NULL;


int STDCALL
WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
   g_hInst = hInst;

HDC hDC;
HGLRC hRC;
MSG msg;
BOOL bQuit = FALSE;

        g_hMainDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_DIALOG), NULL, OpenProc);
        if(g_hMainDialog != NULL)
        {
            ShowWindow(g_hMainDialog, SW_SHOW);
        }
        else
        {
            MessageBox(NULL, "CreateDialog returned NULL", "Warning!",
                MB_OK | MB_ICONINFORMATION);
        }

Structure = GetDlgItem(g_hMainDialog,IDC_STRUCT);

// enable OpenGL for the window
EnableOpenGL( Structure, &hDC, &hRC );

// program main loop
while ( !bQuit ) {

// check for messages
if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {

// handle or dispatch messages
if ( msg.message == WM_QUIT ) {
bQuit = TRUE;
} else {
TranslateMessage( &msg );
DispatchMessage( &msg );
}

} else {


glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
glClear( GL_COLOR_BUFFER_BIT );

glPushMatrix();
glRotatef( theta, angx, angy, angz );
glBegin( GL_TRIANGLES );
glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( Fx, Fy );
glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( Sx, Sy );
glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( Tx, Ty );
glEnd();
glPopMatrix();


SwapBuffers( hDC );

theta += Spd;

}

}

// shutdown OpenGL
DisableOpenGL( Structure, hDC, hRC );

// destroy the window explicitly
DestroyWindow( g_hMainDialog );

return msg.wParam;


}

BOOL CALLBACK OpenProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
int nCmdShow;
int len = 0;
HDC main;
LPRECT recy;


    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case WM_CREATE:

                break;

                case WM_KEYDOWN:
                KBcod = GetKBCodePage();

                break;

                case WM_COMMAND:
                case IDC_ABOUT:
                system("start IExplore.exe http://users.pandora.be/gothicsouls");
                MessageBox (NULL, "OpenGL Structure written by Toon Wouters in Dev-C++ (www.bloodshed.net)
                This example shows you the basic movements of a triangle in OpenGL.
Kuniva - spidyvshades@hotmail.com" , "About...", 0 + MB_ICONASTERISK);
                break;

                case IDC_MODIFY:
                len = GetWindowTextLength(GetDlgItem(hwnd, IDC_SPEED));
                if(len > 0)
                {
                int i = NULL;
                char* Speed;
                Speed = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, IDC_SPEED, Speed, len + 1);
                sscanf(Speed,"%f", &Spd);
                GlobalFree((HANDLE)Speed);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, ANGX));
                if(len > 0)
                {
                int i = NULL;
                char* AngleX;
                AngleX = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, ANGX, AngleX, len + 1);
                sscanf(AngleX,"%f", &angx);
                GlobalFree((HANDLE)AngleX);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, ANGY));
                if(len > 0)
                {
                int i = NULL;
                char* AngleY;
                AngleY = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, ANGY, AngleY, len + 1);
                sscanf(AngleY,"%f", &angy);
                GlobalFree((HANDLE)AngleY);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, ANGZ));
                if(len > 0)
                {
                int i = NULL;
                char* AngleZ;
                AngleZ = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, ANGZ, AngleZ, len + 1);
                sscanf(AngleZ,"%f", &angz);
                GlobalFree((HANDLE)AngleZ);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, FIRSTX));
                if(len > 0)
                {
                int i = NULL;
                char* FirstX;
                FirstX = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, FIRSTX, FirstX, len + 1);
                sscanf(FirstX,"%f", &Fx);
                GlobalFree((HANDLE)FirstX);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, FIRSTY));
                if(len > 0)
                {
                int i = NULL;
                char* FirstY;
                FirstY = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, FIRSTY, FirstY, len + 1);
                sscanf(FirstY,"%f", &Fy);
                GlobalFree((HANDLE)FirstY);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, SECONDX));
                if(len > 0)
                {
                int i = NULL;
                char* SecondX;
                SecondX = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, SECONDX, SecondX, len + 1);
                sscanf(SecondX,"%f", &Sx);
                GlobalFree((HANDLE)SecondX);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, SECONDY));
                if(len > 0)
                {
                int i = NULL;
                char* SecondY;
                SecondY = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, SECONDY, SecondY, len + 1);
                sscanf(SecondY,"%f", &Sy);
                GlobalFree((HANDLE)SecondY);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, THIRDX));
                if(len > 0)
                {
                int i = NULL;
                char* ThirdX;
                ThirdX = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, THIRDX, ThirdX, len + 1);
                sscanf(ThirdX,"%f", &Tx);
                GlobalFree((HANDLE)ThirdX);
                }
                len = GetWindowTextLength(GetDlgItem(hwnd, THIRDY));
                if(len > 0)
                {
                int i = NULL;
                char* ThirdY;
                ThirdY = (char*)GlobalAlloc(GPTR, len + 1);
                GetDlgItemText(hwnd, THIRDY, ThirdY, len + 1);
                sscanf(ThirdY,"%f", &Ty);
                GlobalFree((HANDLE)ThirdY);
                }
                 //sscanf(string, "%f", floatnumber)//


                break;
                break;


                case WM_DESTROY:
                DestroyWindow(g_hMainDialog);
                PostQuitMessage (0);
                return 0;
                break;

            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

// Enable OpenGL

VOID EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC )
{
PIXELFORMATDESCRIPTOR pfd;
int iFormat;

// get the device context (DC)
*hDC = GetDC( hWnd );

// set the pixel format for the DC
ZeroMemory( &pfd, sizeof( pfd ) );
pfd.nSize = sizeof( pfd );
pfd.nVersion = 1;
pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
pfd.iPixelType = PFD_TYPE_RGBA;
pfd.cColorBits = 24;
pfd.cDepthBits = 16;
pfd.iLayerType = PFD_MAIN_PLANE;
iFormat = ChoosePixelFormat( *hDC, &pfd );
SetPixelFormat( *hDC, iFormat, &pfd );

// create and enable the render context (RC)
*hRC = wglCreateContext( *hDC );
wglMakeCurrent( *hDC, *hRC );

}


// Disable OpenGL

VOID DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
wglMakeCurrent( NULL, NULL );
wglDeleteContext( hRC );
ReleaseDC( Structure, hDC );
} 


