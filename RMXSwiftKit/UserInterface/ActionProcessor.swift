//
//  RMSActionProcessor.swift
//  RattleGL
//
//  Created by Max Bilbow on 22/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation
#if OSX
import AppKit
    #elseif iOS
    import UIKit
    
    #endif
    import SceneKit
//import RMXKit

//@available(OSX 10.9, *)
//extension RMX {
//    static var willDrawFog: Bool = false
//    
//    static func toggleFog(){
//        RMX.willDrawFog = !RMX.willDrawFog
//    }
//}

extension RMX {

     class ActionProcessor  {
        
        private static var _current: ActionProcessor?
        static var current: ActionProcessor! {
            return _current ?? ActionProcessor()
        }
        private var boomTimer: RMFloat = 1
        
    
        init(){
            if ActionProcessor._current != nil {
                fatalError("singleton error")
            } else {
                ActionProcessor._current = self
            }
        }


        
     
        private var _movement: (x:RMFloat, y:RMFloat, z:RMFloat) = (x:0, y:0, z:0)
        private var _panThreshold: RMFloat = 70
        
        
        func action(action: UserAction?, speed: RMFloat = 1,  args: Any? = nil) -> Bool {
            if let action = action {
                switch action {
                default:
                    return false
                }
            }
            return false;
        }
       
      
    }
}