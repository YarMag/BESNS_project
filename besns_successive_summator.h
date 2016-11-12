//
//  besns_successive_summator.h
//
//  File contains Besns_successive_summator class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_successive_summator_h
#define besns_successive_summator_h

#include "besns_number.h"

namespace besns
{

//
// Besns_successive_summator class
//
// Static class implements summation with successive method.
//
class Besns_successive_summator
{
public:
    // gets sum for two numbers
    // param first: first summand
    // param second: second summand
    // returns: sum number
    static Besns_number get_sum(const Besns_number& first, const Besns_number& second); // exception
    
private:
    // corrects triad according to arithmetic rules
    static void _correct_triad(Besns_triad& triad);
    
    // shift triad - throw away first digit and add zero as new third
    static void _shift_triad(Besns_triad& triad);
};

}

#endif /* besns_successive_summator_h */
