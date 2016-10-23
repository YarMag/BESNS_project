//
//  besns_succ_par_multiplier.h
//
//  File contains Besns_succ_par_multiplier class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_succ_par_multiplier_h
#define besns_succ_par_multiplier_h

#include "besns_multiplier.h"

namespace besns
{

//
// Besns_succ_par_multiplier class
//
// Class implements multiplication with successive-parallel method.
//
class Besns_succ_par_multiplier: public Besns_multiplier
{
public:
	// constructor/destructor
    Besns_succ_par_multiplier(void);
    virtual ~Besns_succ_par_multiplier(void);
    
	// gets multiplication of two numbers
	// param first: first operand
	// param second: second operand
	// returns: product of the specified operands
    Besns_number get_mul(const Besns_number& first, const Besns_number& second);

};
    
}

#endif /* besns_succ_par_multiplier_h */
