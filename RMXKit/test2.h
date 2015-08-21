//
//  test2.hpp
//  RMXKit
//
//  Created by Max Bilbow on 17/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef test2_hpp
#define test2_hpp

#include <stdio.h>

#endif /* test2_hpp */

int runTest2();

namespace rmx {

class IntegerPairs {
public:
    struct Pair {
        int x,y;
        
        Pair(int x, int y) {
            this->x = x;
            this->y = y;
        }
        
        std::string toString() {
            return std::to_string(x) + " + " + std::to_string(y) + " = " + std::to_string(y + y);
        }
    };
    
public:
    Pair * solve(int[] array, int sum) {
        HashMap<Integer, Integer> pairs = new HashMap<>();
        ArrayList<Pair> result = new ArrayList<>();
        for(int i=0;i<array.length;i++){
            if(pairs.containsKey(array[i]))
                result.add(
                           new Pair(array[i],pairs.get(array[i]))
                           );
            else
                pairs.put(sum-array[i], array[i]);
        }
        return result.toArray();
    }
    
}

}