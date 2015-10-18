//
//  RMXTvInput.swift
//  AiCubo
//
//  Created by Max Bilbow on 17/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import GLKit
//import RMXKit

//import CoreMotion
import UIKit
import AVFoundation

extension RMX {
    typealias DPadOrKeys = RMXTvInput

}
typealias RMXInput = RMXTvInput
class RMXTvInput : RMXInterface {
    
    let _testing = false
    let _hasMotion = true
    var grav: Bool = true
    let rollSpeed: RMFloat = -0.01
    
//    var moveButtonPad: UIImageView?// = RMXModels.getImage()
//    var moveButton: UIView?
    var topBar: UIView?
    var menuAccessBar: UIView?
    var pauseMenu: UIView?
    var moveSpeed: Float = 0.4 //-0.01 //-0.4
    var lookSpeed: Float = 0.2
    var turnSpeed: Float = 0.08//002
    
    override func viewDidLoad(){
        super.viewDidLoad()
        if _hasMotion {
//            self.motionManager.startAccelerometerUpdates()
//            self.motionManager.startDeviceMotionUpdates()
//            self.motionManager.startGyroUpdates()
//            self.motionManager.startMagnetometerUpdates()
        }
        
        
        
        
        
    }
    
    
    
    override func update() {
        super.update();
    }
    
    private var _count: Int = 0
    
    
    
    
    func makeButton(title: String? = nil, selector: String? = nil, view: UIView? = nil, row: (CGFloat, CGFloat), col: (CGFloat, CGFloat)) -> UIButton {
        let view = view ?? GameViewController.instance.view
        let btn = UIButton(frame: getRect(withinRect: view?.bounds, row: row, col: col))//(view!.bounds.width * col.0 / col.1, view!.bounds.height * row.0 / row.1, view!.bounds.width / col.1, view!.bounds.height / row.1))
        if let title = title {
            btn.setTitle(title, forState:UIControlState.Normal)
        }
        if let selector = selector {
            btn.addTarget(self, action: Selector(selector), forControlEvents:UIControlEvents.TouchDown)
        }
        
        btn.enabled = true
        view?.addSubview(btn)
        return btn
    }
    
    func showTopBar(recogniser: UIGestureRecognizer) {
        if let topBar = self.topBar {
            topBar.hidden = !topBar.hidden
            self.menuAccessBar!.hidden = !self.menuAccessBar!.hidden
        }
    }
    
    override func hideButtons(hide: Bool) {
//        self.moveButton?.hidden = hide
//        self.moveButtonPad?.hidden = hide
//        self.jumpButton?.hidden = hide
//        self.boomButton?.hidden = hide
        super.hideButtons(hide)
    }
    
    override func pauseGame(sender: AnyObject? = nil) -> Bool {
        self.pauseMenu?.hidden = false
        self.menuAccessBar?.hidden = true
        return super.pauseGame(sender)
        
    }
    
    override func unPauseGame(sender: AnyObject? = nil) -> Bool {
        self.pauseMenu?.hidden = true
        self.menuAccessBar?.hidden = false
        return super.unPauseGame(sender)
    }
    
    override func optionsMenu(sender: AnyObject?) {
        super.optionsMenu(sender)
    }
    
    override func exitToMainMenu(sender: AnyObject?) {
        super.exitToMainMenu(sender)
    }
    
    override func restartSession(sender: AnyObject?) {
        super.restartSession(sender)
    }
    
    
    
    private let topColumns: CGFloat = 7
    
   
    override func setUpViews(withView view: UIView) {
        super.setUpViews(withView: view)
        
        
//        let topBar = self.topBar!
        
        self.scoreboard.alpha = 0.5
//        
//        let w = view.bounds.size.width
//        let h = view.bounds.size.height - topBar.bounds.height
//        //        let leftView: UIView = UIImageView(frame: CGRectMake(0, topBar.bounds.height, w/2, h))
//        let rightView: UIView = UIImageView(frame: CGRectMake(w / 3, topBar.bounds.height, w * 2 / 3, h))
//        rightView.userInteractionEnabled = true
//        
//        
//        let view = GameViewController.instance.view;
//        
//        // add a tap gesture recognizer
//        view.addGestureRecognizer(UITapGestureRecognizer(target: self, action: "grabOrThrow:"))
//        rightView.addGestureRecognizer(UIPanGestureRecognizer(target: self,action: "handleOrientation:"))
//        view.addSubview(rightView)
//        
        
        // add a tap gesture recognizer
        let tapGesture = UITapGestureRecognizer(target: self, action: "jump:")
        let longPressGesture = UIPanGestureRecognizer(target: self, action: "handleOrientation:")
        var gestureRecognizers = [UIGestureRecognizer]()
        gestureRecognizers.append(tapGesture)
        gestureRecognizers.append(longPressGesture)
        if let existingGestureRecognizers = view.gestureRecognizers {
            gestureRecognizers.appendContentsOf(existingGestureRecognizers)
            
        }
        for gr in gestureRecognizers {
            print(gr.description)
        }
        view.gestureRecognizers = gestureRecognizers
    }
    
    
    var i = 0
    var moveOrigin: CGPoint = CGPoint(x: 0,y: 0)
    var lookOrigin: CGPoint = CGPoint(x: 0,y: 0)
    

    var lastPos: CGPoint?
    func handleOrientation(recogniser: UILongPressGestureRecognizer) {
        //        let dx = recogniser.locationInView(<#T##view: UIView?##UIView?#>)
        if recogniser.state == .Began {
            lastPos = recogniser.locationInView(recogniser.view)
        } else if recogniser.state == .Ended {
            lastPos = nil
        } else if let lastPos = lastPos {
//            let node = controllMode == .Floor ? floor : cameras.first!
            let newPos = recogniser.locationInView(recogniser.view)
            let dx = newPos.x - lastPos.x
            let dy = newPos.y - lastPos.y
            self.lastPos = newPos
            
//            print("orientation: \(dx), \(dy)")
            CppBridge.cursorDelta(Double(self.turnSpeed) * Double(dx), dy: Double(self.lookSpeed) * Double(dy))
//            node.eulerAngles.x += Float(dy) * 0.0005
//            node.eulerAngles.z += Float(dx) * -0.0005
            
        }

        
        
        
    }
}


    

