//
//  RMXDebugger.swift
//  RattleGL
//
//  Created by Max Bilbow on 15/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


import Foundation

public func RMLog(
    message: AnyObject? = "poke", logID: String = "DEFAULT",
    method: NSString = __FUNCTION__,
    file: NSString = __FILE__,
    line: Int = __LINE__,
    col: Int = __COLUMN__) {
        #if RMXCpp
        RMXCpp.logMessage(
            message?.description ?? "poke",
            from: "\(file.lastPathComponent)::\(method)",
            withID: logID
        )
        #endif

}

