//
//  besns_arithmetic_helper.h
//
//  File contains Besns_arithmetic_helper class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_arithmetic_helper_h
#define besns_arithmetic_helper_h

#include <tuple>

#include "besns_digit.h"

namespace besns
{

//
// Besns_arithmetic_helper class
//
// Static class stores all rules for basic arithmetic operations and performs necessary calculations based on digits.
//
class Besns_arithmetic_helper
{
public:    
    // gets digits sum as triad
    // use it in successive summation and parallel summation's second level
    // param first: first digit
    // param second: second digit
    // returns: besns digits triad
    static Besns_triad get_triad_sum(Besns_digit first, Besns_digit second);
    
    // gets digits sum as dyad
    // use it in parallel summation on second level
    // param first: first digit
    // param second: second digit
    // returns: besns digits dyad
    static Besns_dyad get_dyad_sum(Besns_digit first, Besns_digit second);
    
    // gets digits sum
    // use it in successive summation for triads
    // param first: first digit
    // param second: second digit
    // returns: besns digit
    static Besns_digit get_digit_sum(Besns_digit first, Besns_digit second);
    
    // gets digits sum from three arguments
    // use it in parallel summation on the third level
    // param first: first digit
    // param second: second digit
    // returns: besns digit
    static Besns_digit get_par_summation_digit_sum(Besns_digit first, Besns_digit second, Besns_digit third);
    
    // gets digits multiplicaton
    // use it in multiplier
    // param first: first digit
    // param second: second digit
    // returns: besns digit
    static Besns_digit get_digit_mul(Besns_digit first, Besns_digit second);
};
    
}

#endif /* besns_arithmetic_helper_h */
