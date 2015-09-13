//
//  RMXKeyMap.swift
//  AiCubo
//
//  Created by Max Bilbow on 13/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation


extension RMEvent {
    var rmxKey: (key: Int32, mod:Int32)? {
        if let key = self.characters {
            switch key {
            case "w":
                return (RMX_KEY_W, 0)
            case "s":
                return (RMX_KEY_S, 0)
            case "a":
                return (RMX_KEY_A, 0)
            case "d":
                return (RMX_KEY_D, 0)
            case "e":
                return (RMX_KEY_E, 0)
            case "q":
                return (RMX_KEY_Q, 0)
            case "g":
                return (RMX_KEY_G, 0)
            case "G":
                return (RMX_KEY_G, RMX_MOD_SHIFT)
            case "m":
                return (RMX_KEY_M, 0)
            case "M":
                return (RMX_KEY_M, RMX_MOD_SHIFT)
            case "l":
                return (RMX_KEY_L, 0)
            case "L":
                return (RMX_KEY_L, RMX_MOD_SHIFT)
            case "r":
                return (RMX_KEY_R, 0)
            case "R":
                return (RMX_KEY_R, RMX_MOD_SHIFT)
            case " ":
                return (RMX_KEY_SPACE, 0)
            default:
                return (RMX_KEY_UNKNOWN, 0)
            }
        }
        NSLog("RMXKey not found! Char: \(self.characters), keyCode: \(self.keyCode)")
        return nil
    }
}