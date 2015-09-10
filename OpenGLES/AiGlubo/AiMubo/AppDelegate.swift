//
//  AppDelegate.swift
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {
    
    @IBOutlet weak var window: Window!
    
    func applicationDidFinishLaunching(aNotification: NSNotification) {
            
    }

    func applicationWillTerminate(aNotification: NSNotification) {
        
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(sender: NSApplication) -> Bool {
        return true;
    }
 
    
    
}


class Window : NSWindow {
    override func keyUp(event: NSEvent) {
        switch GameViewController.instance.mode {
        case .Test:
            GameViewController.instance.keyDown(event)
            return
        case .Engine:
            switch event.characters! {
//            case "w":
//                CppBridge.moveWithDirection("forward", withForce: -1.0)
//                break
//            case "s":
//                CppBridge.moveWithDirection("forward", withForce: 1.0)
//                break
//            case "a":
//                CppBridge.moveWithDirection("left", withForce: -1.0)
//                break
//            case "d":
//                CppBridge.moveWithDirection("left", withForce: 1.0)
//                break
//            case "e":
//                CppBridge.moveWithDirection("up", withForce: 1.0)
//                break
//            case "q":
//                CppBridge.moveWithDirection("up", withForce: -1.0)
//                break
            case "g":
                CppBridge.sendMessage("setEffectedByGravity", withBool: true)
                break
            case "G":
                CppBridge.sendMessage("setEffectedByGravity", withBool: false)
                break
            case " ":
                CppBridge.sendMessage("jump", withScale: 1.0)
                break
            default:
                return
//                super.keyDown(event)
            }
            return
        }
    }
    
    override func keyDown(event: NSEvent) {
        switch GameViewController.instance.mode {
        case .Test:
            GameViewController.instance.keyDown(event)
            return
        case .Engine:
            switch event.characters! {
            case "w":
                 CppBridge.moveWithDirection("forward", withForce: -1.0)
                break
            case "s":
                CppBridge.moveWithDirection("forward", withForce: 1.0)
                break
            case "a":
                CppBridge.moveWithDirection("left", withForce: -1.0)
                break
            case "d":
                CppBridge.moveWithDirection("left", withForce: 1.0)
                break
            case "e":
                CppBridge.moveWithDirection("up", withForce: 1.0)
                break
            case "q":
                CppBridge.moveWithDirection("up", withForce: -1.0)
                break
            case " ":
                CppBridge.sendMessage("jump", withScale: 0)
                break
            default:
                super.keyDown(event)
            }
            return
        }
        
    }
    
    
}