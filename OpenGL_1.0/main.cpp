/**************************
 * Includes
 *
 **************************/
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

/**************************
 * Function Declarations
 *
 **************************/

class __gloViewport {
	private:
	HWND f_hWnd;
	HDC f_hDC;
	HGLRC f_hRC;     
	bool f_enabled;
public:
		__stdcall  __gloViewport(void) {
		f_hWnd = NULL;
		f_enabled = false; 
		};
		__stdcall ~__gloViewport(void) {
		if (f_enabled==true) Disable();
		};
int Bind(HWND a_hWnd){
	f_hWnd  = a_hWnd;
	return 0;
}
int Enable(void)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    /* set the pixel format for the DC */
    f_hDC   = GetDC (f_hWnd);
    /* get the device context (DC) */
    memset(&pfd,'\0', sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (f_hDC, &pfd);
    SetPixelFormat (f_hDC, iFormat, &pfd);
    /* create and enable the render context (RC) */
    f_hRC = wglCreateContext( f_hDC ); wglMakeCurrent( f_hDC, f_hRC );
    f_enabled = true;
}
int Disable(void)
{
	if (f_hWnd==NULL || f_enabled==false) {
		f_enabled=false;return -1;
		}
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (f_hRC); ReleaseDC (f_hWnd, f_hDC);
    f_enabled = false;
}
};

class __gloCurve {
	private:
		

	public:
class __X {
	protected:
		void *f_owner;
	private: float f_x;
	public:
		__stdcall  __X(void *a_owner){
		f_owner = a_owner;
		f_x = 0;
		};
		__stdcall ~__X(){
		};
	void __stdcall operator= (float a_x) {
	f_x = a_x;	
	};
	__stdcall operator float ()  {
	return f_x;	
	};
	friend __gloCurve;
} X;
		__stdcall  __gloCurve(void) : X(this) {
		};
		__stdcall ~__gloCurve(void){
		};

	float __stdcall getX(__int32 param) {
	return X;
	};
	float __stdcall getY(__int32 param) {
	return 0;
	};
	float __stdcall getZ(__int32 param) {
	return 0;
	};
	void __stdcall setX(float a_x, __int32 param) {
	X = a_x;	
	};
	void __stdcall setY(float a_y, __int32 param) {

	};
	void __stdcall setZ(float a_z,__int32 param) {

	};


};

class __gloCircle : public __gloCurve {
	public:
};

class __gloButton : public __gloCurve {
	public:
};



float circle (int k, int r, int h) {
  int x,y;
  glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 180; i++)
    {
    x = r * cos(i) - h;
    y = r * sin(i) + k;
    glVertex3f(x + k,y - h,0);
    
    x = r * cos(i + 0.1) - h;
    y = r * sin(i + 0.1) + k;
    glVertex3f(x + k,y - h,0);
    }
    glEnd();
}


LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{

float x = 0, xi=0.05,y = 0, yi = 0.04,z = 0, zi=0.0;

    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 200, 250,
      NULL, NULL, hInstance, NULL);

	HWND oGLwh =CreateWindowEx(0,
            "STATIC",
            "",
            WS_VISIBLE|
            WS_CHILD|BS_PUSHBUTTON,
            0,
            20,
            200,
            200,
            hWnd,
            (HMENU)NULL,
            hInstance,
            0);
//	SetWindowPos(oGLwh,hWnd,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
__gloViewport *static_viewport = new __gloViewport();
static_viewport->Bind(oGLwh); 
    /* enable OpenGL for the window */
static_viewport->Enable(); 

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);DispatchMessage (&msg);
            }
        }
        else
        {
		
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearColor(0, 0, 0, 0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable (GL_POLYGON_SMOOTH);
glShadeModel(GL_SMOOTH);
glMatrixMode(GL_PROJECTION);
glDisable(GL_DEPTH_TEST);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glHint( GL_LINE_SMOOTH_HINT, GL_NICEST ); 
glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST ); 
glDisable( GL_LINE_SMOOTH ); 
glDisable( GL_POLYGON_SMOOTH );


__gloCircle c; c.getX(0.0);



if (x>+1-0.2) xi=-0.05;
else
if (x<-1) xi=+0.05;

x+=xi; 

if (y>+1-0.2) yi=-0.04;
else
if (y<-1) yi=+0.04;

y+=yi; 
		glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING); // Render lit geometry. 
		glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);

		glNormal3d(-1, -1, 1);
        GLfloat specular[] = { 1.0f, 1.0f, 1.0f , 1.0f};
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        GLfloat ambient[]  = { 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		GLfloat position[] = {-1.0f,+1.0f, +5.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 80.f);
		glLightf (GL_LIGHT0, GL_SPOT_EXPONENT,15);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		glMateriali(GL_FRONT, GL_SHININESS, 96);
		
		glScalef(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
         	glColor3f(0.5, 0.0, 0.0);
        glVertex3f(x + 0.0, y+ 0.0,+0.0);
         	glColor3f(0.0, 0.5, 0.0);
        glVertex3f(x + 0.2, y+ 0.0,+0.0);
         	glColor3f(0.0, 0.0, 0.5);
        glVertex3f(x + 0.2, y+ 0.2,+0.0);
         	glColor3f(0.5, 0.5, 0.5);
        glVertex3f(x + 0.0, y+ 0.2,+0.0);

        glEnd();
		glScalef(1.0f, 1.0f, 1.0f);
        glDisable(GL_LIGHTING); // Render non-lit geometry.
        	
        SwapBuffers (hDC);
        Sleep (22);    
        }
    }

    /* shutdown OpenGL */
    static_viewport->Disable();
    /* destroy the window explicitly */
    DestroyWindow (hWnd);
    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}



