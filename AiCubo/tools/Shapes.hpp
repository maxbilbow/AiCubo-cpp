//
//  RMXShapes.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXShapes_h
#define RattleGL3_0_RMXShapes_h


#endif


//#define TEXTURE_ID_CUBE 1

namespace RMX {
    
    class Draw {
        static void CubeFace(float fSize);
        static void CubeWithTextureCoords (float fSize);
        static void Sphere(double r, int lats, int longs);
        static void Sphere(float size);//Particle pCube = Particle();
        static void RenderObjects(void);
        static void Teapot(float f);
        static void Plane(float x);
        static void Fog(int draw);
    };
}