//
//  AppDelegate.swift
//  AiGlubo-es
//
//  Created by Max Bilbow on 03/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    @IBOutlet weak var window: NSWindow!



    func applicationDidFinishLaunching(aNotification: NSNotification) {
        // Insert code here to initialize your application
//        window.addChildWindow(NSWindow(contentViewController: GameViewController()), ordered: NSWindowOrderingMode.Above)
        
    }

    func applicationWillTerminate(aNotification: NSNotification) {
        // Insert code here to tear down your application
    }


}



