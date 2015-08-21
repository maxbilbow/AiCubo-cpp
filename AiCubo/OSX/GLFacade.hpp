//
//  GLFacade.hpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef GLFacade_h
#define GLFacade_h


#endif /* GLFacade_h */
#define MODEL_VIEW_ROWS ushort(0)
#define MODEL_VIEW_COLS ushort(1)
#define MODEL_VIEW_DEFAULT MODEL_VIEW_COLS


//#import "Camera.h"
namespace RMX {
    
    class GL {
    public:
        static void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
       

        //void GLKMakeLookAt(GLKBaseEffect * effect,Camera * view);
        static void PostRedisplay();
        static void LookAt(Camera * camera, ushort mode = MODEL_VIEW_DEFAULT);
        static void LookAt(GLKMatrix4  view, ushort mode = MODEL_VIEW_DEFAULT);
        static void Materialfv(int32_t a,int32_t b, GLKVector4 color);
        static void Translate(GLKVector3 v);
        static void Shine(int32_t a, int32_t b, GLKVector4 color);

        static void Render(void (*render)(float),float size);
        static void Center(void (*center)(int,int),int x, int y);

        static void GetLastMouseDelta(int * x, int * y);
        
        static void MakePerspective(float fovy, float aspect, float near, float far);
        static void SwapBuffers();
        static void Init(int argc, char * argv[]);
        static void InitDisplayMode(unsigned int mode);
        static int EnterGameMode();
        static void MakeWindow(int posx,int posy, int w, int h, const char * name);
        static void RegisterCallbacks(void *display,void *reshape);
        
        static void LeaveGameMode();
        static void InitWindowSize (Window * window);
        static void InitWindowSize (int width, int height);
        
        static void DisplayFunc(void (display)(void));
        static void ReshapeFunc(void (reshape)(int,int));
        
        
        static void KeyboardFunc(void (*func)(unsigned char, int, int));
        static void KeyboardUpFunc(void (*func)(unsigned char, int, int));
        static void SpecialFunc(void (*func)(int, int, int));
        static void SpecialUpFunc(void (*func)(int, int, int));
        
        static void MouseFunc(void (*func)(int, int, int, int));
        static void MotionFunc(void (*func)(int, int));
        static void PassiveMotionFunc(void (*func)(int, int));
        
        static int CreateWindow(const char *title);
        static void DestroyWindow(int win);

        static void IdleFunc(void (*func)());
        
        static void MainLoop();
        
        static int GameModeGet(unsigned int mode);
    };

}
