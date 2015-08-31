//
//  iOSControllers.swift
//  RattleGLES
//
//  Created by Max Bilbow on 25/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import GLKit
import SceneKit
//import RMXKit

import UIKit

extension RMXMobileInput {
    func resetTransform(recogniser: UITapGestureRecognizer) {
//        self.activeSprite?.setAngle(roll: 0)
         CppBridge.sendMessage(UserAction.RESET.description)
    }
    func printData(recogniser: UITapGestureRecognizer){
        CppBridge.sendMessage(UserAction.GET_INFO.description)
    }
    
    func showScores(recogniser: UITapGestureRecognizer){
        CppBridge.sendMessage("\(UserAction.TOGGLE_SCORES):1")
    }
    
    func toggleAi(recogniser: UITapGestureRecognizer){
        CppBridge.sendMessage("toggleAi")
    }
    
    
    func zoom(recogniser: UIPinchGestureRecognizer) {        
        CppBridge.sendMessage("\(UserAction.ZoomInAnOut):\(RMFloat(recogniser.velocity))")
    }
    
    
    func toggleGravity(recognizer: UITapGestureRecognizer) {
        CppBridge.sendMessage("setEffectedByGravity", withBool: grav)
        self.grav = !self.grav
    }
        
        
    func toggleAllGravity(recognizer: UITapGestureRecognizer) {
        CppBridge.sendMessage("setEffectedByGravity", withBool: grav)
        self.grav = !self.grav
    }
    
    
    ///The event handling method
    func handleOrientation(recognizer: UIPanGestureRecognizer) {
        if recognizer.numberOfTouches() == 1 {
            let point = recognizer.velocityInView(GameViewController.instance.view)
            CppBridge.turnAboutAxis(UserAction.MOVE_PITCH.description, withForce: self.lookSpeed * 10 * Float(point.y))
            CppBridge.turnAboutAxis(UserAction.MOVE_YAW.description, withForce: self.lookSpeed * Float(point.x))
            
        }
//            _handleRelease(recognizer.state)
    }

    
    func nextCamera(recogniser: UITapGestureRecognizer) {
        CppBridge.sendMessage("\(UserAction.NEXT_CAMERA):1")
    }
    
    func previousCamera(recogniser: UITapGestureRecognizer) {
        CppBridge.sendMessage("\(UserAction.PREV_CAMERA):1")
    }


    func grabOrThrow(recognizer: UITapGestureRecognizer) {
        // retrieve the SCNView
        let scnView = GameViewController.instance.view//.view as! GameView
        // check what nodes are tapped
        let p = recognizer.locationInView(scnView)
        
        self.processHit(point: p, type: UserAction.THROW_ITEM)

//        self.processHit(scnView.hitTest(p, options: nil))
    }

    
}




