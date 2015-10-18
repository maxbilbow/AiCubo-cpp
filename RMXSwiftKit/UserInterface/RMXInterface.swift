//
//  RMXInterface.swift
//  RattleGLES
//
//  Created by Max Bilbow on 25/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import QuartzCore
import GLKit
//import RMXKit

import AVFoundation
import SceneKit
import SpriteKit

    typealias Interface = RMXInterface

    //@available(OSX 10.9, *)
    class RMXInterface : NSObject, RMSingleton {

        var lockCursor = false
        
    //    lazy var actionProcessor: RMSActionProcessor = RMSActionProcessor(interface: self)
        private let _isDebugging = false
        var debugData: String = "No Data"
        
    //    var gvc: GameViewController!
        
        var timer: NSTimer? //CADisplayLink?
        
        internal static let moveSpeed: RMFloat = 2
        
        
        
        var keyboard: KeyboardType = .UK
        //    private var _scoreboard: SKView! = nil
        var lines: [SKLabelNode] = [ SKLabelNode(text: "") , SKLabelNode(text: ""), SKLabelNode(text: ""), SKLabelNode(text: "") ]
        //    let line1 = SKLabelNode(text: "line1")
        //    let line2 = SKLabelNode(text: "line2")
        //    let line3 = SKLabelNode(text: "line3")
        
        
        
        var scoreboard: SKView!
        

        
        
        
        
        
        override required init() {
            super.init()
            if (Interface._current != nil) {
                fatalError("Singleton")
            } else {
                Interface._current = self
                self.setUpViews(withView: GameViewController.instance.view)
//                self.newGame(Interface.DEFAULT_GAME)
                self.viewDidLoad()
            }
        }
        
        func viewDidLoad() {
            
        }
        class func destroy() {
            if self === Interface._current {
                Interface._current = nil
            }
        }
        
        deinit {
            Interface.destroy()
        }
        
        private static var _current: Interface?
        
        class func singleton() -> Self {
            return self.init();
        }
        
        static var instance: Interface {
            return Interface._current ?? self.init()
        }

        //    var world2D: SKView?
        func startVideo(sender: AnyObject?){}
        
        
        
        private var _scoreboardRect: CGRect {
            var bounds = GameViewController.instance.view.bounds
            bounds.size.height = bounds.size.height * 0.3
            bounds.origin = CGPoint(x: bounds.size.width / 3, y: bounds.size.height / 3)
            return bounds
        }
        
        func setUpViews(withView view: RMView) {
            let bounds = _scoreboardRect
            let skScene: SKScene = SKScene(size: bounds.size)
            //            bounds.height =
            self.scoreboard = SKView(frame: bounds)
            self.scoreboard.presentScene(skScene)
            self.scoreboard.hidden = true
            for line in self.lines {
                self.scoreboard.scene?.addChild(line)
            }
            self.scoreboard.allowsTransparency = true
            GameViewController.instance.view.addSubview(self.scoreboard)
            self.scoreboard.hidden = true
            
            
        }
        
        func _limit(x: CGFloat, limit lim: CGFloat) -> CGFloat {
            let limit: CGFloat = lim// ?? 2// CGFloat(RMXInterface.moveSpeed)
            if x > limit {
                return limit
            } else if x < -limit {
                return -limit
            } else {
                return x
            }
        }
        
        
        
        func update() {
            RMXCpp.printLogToTerminal()
        }
        
    //    func destroyWorld() -> RMXScene? {
    //        return nil //_world?.destroy()
    //    }
        
       
        
        
      
        

        func animateHit(node: SCNNode){
            if let material = node.geometry?.firstMaterial {
                
                // highlight it
                SCNTransaction.begin()
                SCNTransaction.setAnimationDuration(0.5)
                
                // on completion - unhighlight
                SCNTransaction.setCompletionBlock {
                    SCNTransaction.begin()
                    SCNTransaction.setAnimationDuration(0.5)
                    
                    material.emission.contents = RMColor.blackColor()
                    
                    SCNTransaction.commit()
                }
                
                material.emission.contents = RMColor.redColor()
                
                SCNTransaction.commit()
            }
        }
        
        func resetButton() {
            RMLog("ResetBotton")
        }
        
        func processHit(point p: CGPoint, type: UserAction) -> Bool {
//            if let hitResults = GameViewController.instance.view.hitTest(p, withEvent: nil) where hitResults.count > 0,
//                let hit: SCNHitTestResult = hitResults[0] {
//                let tracked = type == .THROW_OR_GRAB_TRACKED
//                if RMXNode.current?.throwItem(at: hit, tracking: tracked) ?? false || RMXNode.current?.grabItem(hit.node) ?? false {
//                    self.animateHit(hit.node)
//                    return true
//                }
//            }
//            return false
            RMLog("ProcessHit")

//        }
            return true
        }
        
        

        ///Stop all inputs (i.e. no gestures received)
        ///@virtual
        func handleRelease(arg: AnyObject, args: AnyObject ...) { }

        
        ///@virtual
        func hideButtons(hide: Bool) {}
        
     
        ///When overriding, call super last
        func pauseGame(sender: AnyObject? = nil) -> Bool {
            self.hideButtons(true)
            
            return true
        }
        
        ///When overriding, call super last
        func unPauseGame(sender: AnyObject? = nil) -> Bool {
            self.scoreboard.hidden = true //self.action(action: RMXInterface.HIDE_SCORES, speed: 1)
            self.hideButtons(false)
//            _world?.unPause()
            return true
        }
        
        func optionsMenu(sender: AnyObject?) {
             CppBridge.sendMessage("Show Options")
            
        }
        
        func exitToMainMenu(sender: AnyObject?) {
             CppBridge.sendMessage("End Simulation")

        }
        

        func restartSession(sender: AnyObject?) {
//            self.newGame()
            CppBridge.sendMessage("restartSession")
        }
        
        func getRect(withinRect bounds: CGRect? = nil, row: (CGFloat, CGFloat), col: (CGFloat, CGFloat)) -> CGRect {
            let bounds = bounds ?? GameViewController.instance.view.bounds
            return CGRectMake(bounds.width * (col.0 - 1) / col.1, bounds.height * (row.0 - 1) / row.1, bounds.width / col.1, bounds.height / row.1)
        }
        
        private var _willUpdateScoreboard = false
        
        override func observeValueForKeyPath(keyPath: String?, ofObject object: AnyObject?, change: [String : AnyObject]?, context: UnsafeMutablePointer<Void>) {
            
                super.observeValueForKeyPath(keyPath, ofObject: object, change: change, context: context)
        }
    }
