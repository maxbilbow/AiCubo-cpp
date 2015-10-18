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

extension RMXInput {
    func resetCamera(recogniser: UITapGestureRecognizer) {
        //        RMX.ActionProcessor.current.action(.RESET_CAMERA, speed: 1)
        CppBridge.sendMessage("resetCamera:1")
    }
    
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
    
    #if iOS
    func zoom(recogniser: UIPinchGestureRecognizer) {        
        CppBridge.sendMessage("\(UserAction.ZoomInAnOut):\(RMFloat(recogniser.velocity))")
    }
    #endif
    
    func toggleGravity(recognizer: UITapGestureRecognizer) {
        CppBridge.sendMessage("setEffectedByGravity", withBool: grav)
        self.grav = !self.grav
    }
        
        
    func toggleAllGravity(recognizer: UITapGestureRecognizer) {
        CppBridge.sendMessage("setEffectedByGravity", withBool: grav)
        self.grav = !self.grav
    }
    
    
    func jump(recogniser: UILongPressGestureRecognizer){
        switch recogniser.state {
        case .Began:
            CppBridge.setKey(RMX_KEY_SPACE, action: RMX_PRESS, withMods: 0)
            //                CppBridge.sendMessage(UserAction.JUMP.description, withScale: 0)
            break
        case .Ended:
            //                CppBridge.sendMessage(UserAction.JUMP.description, withScale: 1)
            CppBridge.setKey(RMX_KEY_SPACE, action: RMX_RELEASE, withMods: 0)
            break
        default:
            //                CppBridge.sendMessage(UserAction.MOVE_UP.description, withScale: Float(self.moveSpeed))
            break
        }
        
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




