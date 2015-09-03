//
//  GameView.swift
//  AiCubo
//
//  Created by Max Bilbow on 03/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation


class GameViewController : NSViewController {
    private static var _instance: GameViewController!
    static var instance: GameViewController {
        return _instance ?? GameViewController()
    }
    
    
    
    override func viewDidLoad() {
        GameViewController._instance = self
        
    }
}