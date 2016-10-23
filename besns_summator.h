//
//  besns_summator.h
//
//  File contains Besns_summator class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_summator_h
#define besns_summator_h

#include "besns_number.h"

namespace besns
{

//
// Besns_summator class
//
// Abstract interface for summators.
//
class Besns_summator
{
public:
    // gets sum for two numbers
    // param first: first summand
    // param second: second summand
    // returns: sum number
    virtual Besns_number get_sum(const Besns_number& first, const Besns_number& second) = 0;
};

}

#endif /* besns_summator_h */
