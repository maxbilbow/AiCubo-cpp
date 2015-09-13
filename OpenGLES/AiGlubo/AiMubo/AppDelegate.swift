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
        if let key = event.rmxKey {
            CppBridge.setKey(key.key, action: RMX_RELEASE, withMods: key.mod)
        }
    }
    
    override func keyDown(event: NSEvent) {
        if let key = event.rmxKey {
            CppBridge.setKey(key.key, action: RMX_PRESS, withMods: key.mod)
        }
    }
    
    override func rotateWithEvent(event: NSEvent) {
        CppBridge.turnAboutAxis("roll", withForce: event.rotation * PI_OVER_180f)
    }

    override func scrollWheel(event: NSEvent) {
        CppBridge.cursorDelta(Double(event.deltaX), dy: Double(event.deltaY))
    }
    
    override func mouseDragged(event: NSEvent) {
        NSLog(event.description)
    }

    override func magnifyWithEvent(event: NSEvent) {
        NSLog("\(event.magnification)")
    }
    
    
}