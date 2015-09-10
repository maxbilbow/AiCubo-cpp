//
//  RMXGLFWWindow.swift
//  RMXKit
//
//  Created by Max Bilbow on 10/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
//import AppKit





class View : GLFWView {
   
    
    
    override func prepareOpenGL() {
        CppBridge.setupScene()
        super.prepareOpenGL()
    }
    
    
    
    
    override func update() {
        CppBridge.updateSceneLogic()
        super.update()
    }
    
    
}