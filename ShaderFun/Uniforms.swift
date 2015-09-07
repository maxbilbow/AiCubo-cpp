//
//  Uniforms.swift
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import GLKit

struct Uniform {
    
    init(keys: (key:String,length:Int)...) {
        for v in keys {
            self.keys[v.key] = _bytes.count
            for var i = 0; i < v.length; ++i {
                _bytes.append(0)
            }
        }
    }
    
    init(width: Float, height: Float, vars: (key:String,length:Int)...) {
        var keys: [(key:String,length:Int)] = [("viewMatrix",16),("projectionMatrix",16)]
        keys += vars
        for v in keys {
            self.keys[v.key] = _bytes.count
            for var i = 0; i < v.length; ++i {
                _bytes.append(0)
            }
        }
        
        let projection = GLKMatrix4MakePerspective(45.0, width / height, 0.01, 1000.0)
        let view = GLKMatrix4Identity
        self.setView(matrix: view)
        self.setProjection(matrix: projection)
    }
    
    var bytes: [Float] {
        return _bytes
    }
    
    private var _bytes: [Float] = []
    
    private var keys: [String : Int] = [:]
    
    mutating func setValue(forKey key: String, value: Float) {
        if let key = keys[key] {
            _bytes[key] = value
        } else {
            NSLog("WARNING: the key '\(key)' was not recognised")
        }
    }
    mutating func setValue(forKey key: String, array: [Float]) {
        if let key = keys[key] {
            for var i = 0; i < array.count; ++i {
                _bytes[key + i] = array[i]
            }
        } else {
            NSLog("WARNING: the key '\(key)' was not recognised")
        }
    }
    mutating func setValue(forKey key: String, matrix4 m: GLKMatrix4) {
        if let key = keys[key] {
            _bytes[key + 00] = m.m00; _bytes[key + 01] = m.m01; _bytes[key + 02] = m.m02; _bytes[key + 03] = m.m03
            _bytes[key + 04] = m.m10; _bytes[key + 05] = m.m11; _bytes[key + 06] = m.m12; _bytes[key + 07] = m.m13
            _bytes[key + 08] = m.m20; _bytes[key + 09] = m.m21; _bytes[key + 10] = m.m22; _bytes[key + 11] = m.m23
            _bytes[key + 12] = m.m30; _bytes[key + 13] = m.m31; _bytes[key + 14] = m.m32; _bytes[key + 15] = m.m33
        } else {
            NSLog("WARNING: the key '\(key)' was not recognised")
        }
    }
    
    mutating func setValue(forKey key: String, vector3 v: GLKVector3) {
        if let key = keys[key] {
            _bytes[key + 0] = v.x; _bytes[key + 1] = v.y; _bytes[key + 2] = v.z
        } else {
            NSLog("WARNING: the key '\(key)' was not recognised")
        }
    }
    
    func getValue(key: String) -> Float? {
        if let key = keys[key] {
            return _bytes[key]
        } else {
            NSLog("WARNING: the key '\(key)' was not recognised")
            return nil
        }
    }
    
//    private mutating func setViewProjection(matrix m: GLKMatrix4) {
//        if viewMatrix != nil && projectionMatrix != nil {
//            _bytes[00] = m.m00; _bytes[01] = m.m01; _bytes[02] = m.m02; _bytes[03] = m.m03
//            _bytes[04] = m.m10; _bytes[05] = m.m11; _bytes[06] = m.m12; _bytes[07] = m.m13
//            _bytes[08] = m.m20; _bytes[09] = m.m21; _bytes[10] = m.m22; _bytes[11] = m.m23
//            _bytes[12] = m.m30; _bytes[13] = m.m31; _bytes[14] = m.m32; _bytes[15] = m.m33
//        }
//    }
    
    mutating func setView(matrix m: GLKMatrix4) {
        self.setValue(forKey: "viewMatrix", matrix4: m)
    }
    
    mutating func setProjection(matrix m: GLKMatrix4) {
        self.setValue(forKey: "projectionMatrix", matrix4: m)
    }
    
    mutating func setModel(matrix m: GLKMatrix4) {
        self.setValue(forKey: "modelMatrix", matrix4: m)
    }
    
    mutating func setScale(scale v: GLKVector3) {
        self.setValue(forKey: "scale", vector3: v)
    }
    
    
    var print:String {
        var col = 0; var first = true
        var s = "\(_bytes[00].print)"
        for byte in _bytes {
            if first {
                first = false
            } else if ++col == 4 {
                s += "\n\(byte.print)"
                col = 0
            } else {
                s += ", \(byte.print)"
            }
        }
        return s
    }
    
    var size: size_t {
        return sizeofValue(_bytes[0]) * (_bytes.count)// + vars.count)
    }
    
    mutating func addKey(keys: (key:String,length:Int)...) {
        for v in keys {
            self.keys[v.key] = _bytes.count
            for var i = 0; i < v.length; ++i {
                _bytes.append(0)
            }
        }
    }
    
    static func newSharedUniform(view: RMView? = nil, keys: [(key:String,length:Int)]? = nil) -> Uniform {
        let bounds = view?.bounds ?? CGRect(x: 0, y: 0, width: 1, height: 1)
        var u = Uniform(width: Float(bounds.width), height: Float(bounds.height))
        if let keys = keys {
            for key in keys {
                u.addKey(key)
            }
        }
        return u
    }
    
    static func newInstanceUniform() -> Uniform {
        return Uniform(keys: ("modelMatrix",16), ("scale",3))
    }
}
