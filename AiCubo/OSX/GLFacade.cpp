//
//  cStuff.c
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//
//
//#import <GLUT/GLUT.h>
//#import <GLKit/GLKit.h>
//#import <SceneKit/SceneKit.h>
//#import "RMXMaths.h"
//#import <RattleGL-Swift.h>
#import <iostream>
#import <exception>
//#import <GLKit/GLKVector4.h>
#import <GLUT/GLUT.h>
//#import <GLKit/GLKVector3.h>
//#import <GLKit/GLKVector4.h>
#import <GLKit/GLKMatrix4.h>
#import "Object.h"
#import "ASingleton.h"
#import "Window.h"
#import "Camera.h"
#import "OpenGLView.h"
#import "GLFacade.h"

namespace RMX {

    
    void GL::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
        gluPerspective(fovy, aspect, zNear, zFar);
    }
    
    void GL::PostRedisplay() {
        glutPostRedisplay();
    }
    

    void GL::LookAt(Camera * camera, ushort mode) {
        GL::LookAt(camera->modelView, mode);
    }
    
    void GL::LookAt(GLKMatrix4  view, ushort mode) {
        switch (mode) {
            case MODEL_VIEW_ROWS:
                gluLookAt(view.m00,view.m01,view.m02,
                          view.m10,view.m11,view.m12,
                          view.m20,view.m21,view.m22
                          );
                break;
            case MODEL_VIEW_COLS:
                gluLookAt(view.m00,view.m10,view.m20,
                          view.m01,view.m11,view.m21,
                          view.m02,view.m12,view.m22
                          );
                break;
            default:
                break;
        }
        
        
    }


    void GL::Materialfv(int32_t a,int32_t b, GLKVector4 color){
        glMaterialfv(a,b,color.v);
    }

    void GL ::Translate(GLKVector3 v){
        glTranslatef(v.x, v.y, v.z);
    }

    void GL ::Shine(int32_t a, int32_t b, GLKVector4 color) {
        glLightfv(a, b, color.v);
    }

    void GL::Render(void (*render)(float),float size) {
        render(size);
    }

    void GL::Center(void (*center)(int,int),int x, int y){
        center(x,y);
    }

    void GL::GetLastMouseDelta(int * x, int * y) {
//        GetLastMouseDelta(x,y);
        throw std::invalid_argument("Not setup!");
    }

   
   
    void GL::MakePerspective(float fovy, float aspect, float near, float far){
        gluPerspective(fovy, aspect, near, far);
    }

    void GL::SwapBuffers(){
        glutSwapBuffers();
    }

    void GL::Init(int argc, char * argv[]){
        glutInit(&argc, argv);
    }

    void GL::InitDisplayMode(unsigned int mode){
        glutInitDisplayMode(mode);
    }
    int GL::EnterGameMode(){
        return glutEnterGameMode();
    }

    void GL::MakeWindow(int posx,int posy, int w, int h, const char * name){
        glutInitWindowPosition(posx,posy);
        glutInitWindowSize(w,h);
        glutCreateWindow(name);
    }

    void GL::RegisterCallbacks(void *display,void *reshape){
        glutDisplayFunc(OpenGLView::display);
        glutReshapeFunc(OpenGLView::reshape);
    }
    
    void GL::LeaveGameMode() {
        glutLeaveGameMode();
    }
    
    void GL::InitWindowSize (Window * window){
        glutInitWindowSize (window->getWidth(), window->getHeight());
    }
    
    void GL::InitWindowSize (int width, int height){
        glutInitWindowSize (width, height);
    }
    
    void GL::ReshapeFunc(void (*reshape)(int, int)) {
        glutReshapeFunc(reshape);
    }
    
    void GL::DisplayFunc(void (*display)(void)){
        glutDisplayFunc(display);
    }
    
    void GL::KeyboardFunc(void (*func)(unsigned char, int, int)) {
        glutKeyboardFunc(func);
    }
    
    void GL::KeyboardUpFunc(void (*func)(unsigned char, int, int)) {
        glutKeyboardUpFunc(func);
    }
    
    void GL::SpecialFunc(void (*func)(int, int, int)) {
        glutSpecialFunc(func);
    }
    
    void GL::SpecialUpFunc(void (*func)(int, int, int)) {
        glutSpecialUpFunc(func);
    }
    
    void GL::MouseFunc(void (*func)(int, int, int, int)) {
        glutMouseFunc(func);
    }
    
    void GL::MotionFunc(void (*func)(int, int)) {
        glutMotionFunc(func);
    }
    
    void GL::PassiveMotionFunc(void (*func)(int, int)) {
        glutPassiveMotionFunc(func);
    }
    
    void GL::IdleFunc(void (*func)()) {
        glutIdleFunc(func);
    }
    
    int GL::CreateWindow(const char *title) {
        return glutCreateWindow(title);
    }
    
    void GL::DestroyWindow(int win) {
        glutDestroyWindow(win);
    }
    
    void GL::MainLoop() {
        glutMainLoop();
    }
    
    int GL::GameModeGet(unsigned int mode) {
        return glutGameModeGet(mode);
    }
}