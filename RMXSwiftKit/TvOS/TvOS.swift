//
//  TvOS.swift
//  AiCubo
//
//  Created by Max Bilbow on 17/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import UIKit
import SceneKit

public typealias RMFloat = Float
public typealias RMButton = UIButton
public typealias RMView = UIView
public typealias RMColor = UIColor
public typealias RMDataView = UITextView
public typealias RMLabel = UIButton
public typealias RMImage = UIImage
public typealias RMEvent = UIEvent

public func * (lhs: SCNVector3, rhs: CGFloat) -> SCNVector3 {
    return lhs * Float(rhs)
}
