//
//  besns_multiplier.h
//
//  File contains Besns_multiplier class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_multiplier_h
#define besns_multiplier_h

#include "besns_number.h"

namespace besns
{

//
// Besns_multiplier class
//
// Abstract interface for multipliers.
//
class Besns_multiplier
{
public:
	// gets multiplication of two numbers
	// param first: first operand
	// param second: second operand
	// returns: product of the specified operands
    virtual Besns_number get_mul(const Besns_number& first, const Besns_number& second) = 0;
};

}

#endif /* besns_multiplier_h */
