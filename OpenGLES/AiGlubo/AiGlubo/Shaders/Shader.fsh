//
//  Shader.fsh
//  AiGlubo
//
//  Created by Max Bilbow on 29/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

varying lowp vec4 colorVarying;
//precision mediump float;
void main()
{
    gl_FragColor = colorVarying;
}
