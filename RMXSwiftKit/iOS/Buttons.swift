//
//  Buttoms.swift
//  AiScene
//
//  Created by Max Bilbow on 20/05/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation
import UIKit
//import RMXKit




    extension RMXInput {
        
        static func getImage() -> RMImage {
            return RMImage(named: "art.scnassets/2D/circle_shape.png")!
        }
        internal func getButton(frame: CGRect) -> UIView {
            let buttonBase = UIView(frame: frame)
            buttonBase.alpha = 0.5
            buttonBase.layer.cornerRadius = 20
            buttonBase.backgroundColor = UIColor.blueColor()
    //        buttonBase.userInteractionEnabled = true
            
            return buttonBase

        }
        
        internal func moveButton(size: CGSize, origin: CGPoint) -> UIView {
            let frame = CGRectMake(origin.x, origin.y, size.width, size.height)
            let baseButton = self.getButton(frame)
            
            
            return baseButton
        }

        
        
        
                
        var moveButtonCenter: CGRect {
            let avg = (GameViewController.instance.view.bounds.size * 0.13).average
            let size = CGSize(width: avg, height: avg)
            let origin = CGPoint(x: GameViewController.instance.view.bounds.size.width * 0.07, y: GameViewController.instance.view.bounds.size.height * 0.88 - size.height)
            let frame = CGRectMake(origin.x, origin.y, size.width, size.height)
            return frame
        }
        
        var boomButtonCenter: CGRect {
            let avg = (GameViewController.instance.view.bounds.size * 0.10).average
            let size = CGSize(width: avg, height: avg)
            let origin = CGPoint(x: GameViewController.instance.view.bounds.size.width * 0.82 - size.width / 2, y: GameViewController.instance.view.bounds.size.height * 0.88 - size.height)
            let frame = CGRectMake(origin.x, origin.y, size.width, size.height)
            return frame
        }
        
        func explode(recogniser: UILongPressGestureRecognizer) {
             CppBridge.sendMessage(UserAction.MOVE_UP.description, withScale: -Float(self.moveSpeed))
            //        RMXNode.current?.setAngle(roll: 0)
//            CppBridge.sendMessage("\(UserAction.THROW_OR_GRAB_UNTRACKED)")
//            if recogniser.state == .Ended {
//                if RMXNode.current?.isHoldingItem ?? false {
//                    RMX.ActionProcessor.current.action(UserAction.THROW_OR_GRAB_UNTRACKED)
////                    RMXNode.current?.throwItem(force: 1)
//                } else {
//                    RMX.ActionProcessor.current.action(UserAction.BOOM, speed: 1)
//                }
//                //RMX.ActionProcessor.current.explode(force: self.boomTimer)
//                
//            } else {
//                RMX.ActionProcessor.current.action(UserAction.BOOM, speed: 0)
//                self.boomTimer++ //TODO: put this in the ActionProcessor class
//            }
        }
        
        var jumpButtonCenter: CGRect {
            let avg = (GameViewController.instance.view.bounds.size * 0.10).average
            let size = CGSize(width: avg, height: avg)
            let origin = CGPoint(x: GameViewController.instance.view.bounds.size.width * 0.82 + size.width / 2, y: GameViewController.instance.view.bounds.size.height * 0.85 - size.height)
            let frame = CGRectMake(origin.x, origin.y, size.width, size.height)
            return frame
        }
        
       
    }
