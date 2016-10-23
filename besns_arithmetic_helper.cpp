//
//  besns_arithmetic_helper.cpp
//
//  File contains Besns_arithmetic_helper class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include <stdint.h>

#include "besns_arithmetic_helper.h"

namespace besns
{

// Besns_arithmetic_helper class
//

// gets digits sum as triad
// use it in successive summation and parallel summation's second level
// param first: first digit
// param second: second digit
// returns: besns digits triad
Besns_triad Besns_arithmetic_helper::get_triad_sum(Besns_digit first, Besns_digit second)
{
    Besns_triad triad = std::make_tuple(Besns_digit::undefined, Besns_digit::undefined, Besns_digit::undefined);
    
    // nested switches, they represent arithmetic table
    switch (first)
    {
        case Besns_digit::neg_one:
            switch (second)
            {
                case Besns_digit::neg_one:
                    std::get<0>(triad) = Besns_digit::zero;
                    std::get<1>(triad) = Besns_digit::neg_one;
                    std::get<2>(triad) = Besns_digit::zero;
                    break;
                case Besns_digit::zero:
                    std::get<0>(triad) = Besns_digit::zero;
                    std::get<1>(triad) = Besns_digit::neg_one;
                    std::get<2>(triad) = Besns_digit::pos_one;
                    break;
                case Besns_digit::pos_one:
                    std::get<0>(triad) = Besns_digit::zero;
                    std::get<1>(triad) = Besns_digit::zero;
                    std::get<2>(triad) = Besns_digit::zero;
                    break;
                default:
                    break;
            }
            break;
        case Besns_digit::zero:
            switch (second)
            {
            case Besns_digit::neg_one:
                std::get<0>(triad) = Besns_digit::zero;
                std::get<1>(triad) = Besns_digit::neg_one;
                std::get<2>(triad) = Besns_digit::pos_one;
                break;
            case Besns_digit::zero:
                std::get<0>(triad) = Besns_digit::zero;
                std::get<1>(triad) = Besns_digit::zero;
                std::get<2>(triad) = Besns_digit::zero;
                break;
            case Besns_digit::pos_one:
                std::get<0>(triad) = Besns_digit::zero;
                std::get<1>(triad) = Besns_digit::zero;
                std::get<2>(triad) = Besns_digit::pos_one;
                break;
            default:
                break;
            }
            break;
        case Besns_digit::pos_one:
            switch (second)
            {
            case Besns_digit::neg_one:
                std::get<0>(triad) = Besns_digit::zero;
                std::get<1>(triad) = Besns_digit::zero;
                std::get<2>(triad) = Besns_digit::zero;
                break;
            case Besns_digit::zero:
                std::get<0>(triad) = Besns_digit::zero;
                std::get<1>(triad) = Besns_digit::zero;
                std::get<2>(triad) = Besns_digit::pos_one;
                break;
            case Besns_digit::pos_one:
                std::get<0>(triad) = Besns_digit::pos_one;
                std::get<1>(triad) = Besns_digit::neg_one;
                std::get<2>(triad) = Besns_digit::zero;
                break;
            default:
                break;
            }
            break;
        default:
            break;
    }
    
    return triad;
}

// gets digits sum as dyad
// use it in parallel summation on second level
// param first: first digit
// param second: second digit
// returns: besns digits dyad
Besns_dyad Besns_arithmetic_helper::get_dyad_sum(Besns_digit first, Besns_digit second)
{
    Besns_dyad dyad = std::make_tuple(Besns_digit::undefined, Besns_digit::undefined);
    
    // nested switches, represent arithmetic table
    switch (first)
    {
        case Besns_digit::neg_one:
            switch (second)
            {
                case Besns_digit::neg_one:
                    // not allowed combination, leave undefined digits
                    break;
                case Besns_digit::zero:
                    std::get<0>(dyad) = Besns_digit::zero;
                    std::get<1>(dyad) = Besns_digit::neg_one;
                    break;
                case Besns_digit::pos_one:
                    std::get<0>(dyad) = Besns_digit::zero;
                    std::get<1>(dyad) = Besns_digit::zero;
                    break;
                default:
                    break;
            }
            break;
        case Besns_digit::zero:
            switch (second)
            {
                case Besns_digit::neg_one:
                    std::get<0>(dyad) = Besns_digit::zero;
                    std::get<1>(dyad) = Besns_digit::neg_one;
                    break;
                case Besns_digit::zero:
                    std::get<0>(dyad) = Besns_digit::zero;
                    std::get<1>(dyad) = Besns_digit::zero;
                    break;
                case Besns_digit::pos_one:
                    std::get<0>(dyad) = Besns_digit::pos_one;
                    std::get<1>(dyad) = Besns_digit::neg_one;
                    break;
                default:
                    break;
            }
            break;
        case Besns_digit::pos_one:
            switch (second)
            {
                case Besns_digit::neg_one:
                    std::get<0>(dyad) = Besns_digit::zero;
                    std::get<1>(dyad) = Besns_digit::zero;
                    break;
                case Besns_digit::zero:
                    std::get<0>(dyad) = Besns_digit::pos_one;
                    std::get<1>(dyad) = Besns_digit::neg_one;
                    break;
                case Besns_digit::pos_one:
                    // not allowed combination, leave undefined digits
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    return dyad;
}

// gets digits sum
// use it in successive summation for triads
// param first: first digit
// param second: second digit
// returns: besns digit
Besns_digit Besns_arithmetic_helper::get_digit_sum(Besns_digit first, Besns_digit second)
{
    Besns_digit digit = Besns_digit::undefined;
    
    // simple typecasting, no need for switch
    int32_t result_sum = (int32_t)first + (int32_t)second;
    digit = static_cast<Besns_digit>(result_sum);
    
    return digit;
}

// gets digits sum from three arguments
// use it in parallel summation on the third level
// param first: first digit
// param second: second digit
// returns: besns digit
Besns_digit Besns_arithmetic_helper::get_par_summation_digit_sum(Besns_digit first, Besns_digit second, Besns_digit third)
{
    Besns_digit digit = Besns_digit::undefined;
    
    // according to rules, we can't sum if at least two digits are positive ones
    bool is_unallowed_combination = (first == pos_one && second == pos_one) ||
                                    (first == pos_one && third == pos_one) ||
                                    (second == pos_one && third == pos_one);
    
    if (!is_unallowed_combination)
    {
        int32_t result_sum = (int32_t)first + (int32_t)second + (int32_t)third;
        
        // straightforward type-safe casting
        digit = static_cast<Besns_digit>(result_sum);
    }
    else
        ; // leave digit in the undefined state
    
    return digit;
}

// gets digits multiplicaton
// use it in multiplier
// param first: first digit
// param second: second digit
// returns: besns digit
Besns_digit Besns_arithmetic_helper::get_digit_mul(Besns_digit first, Besns_digit second)
{
    Besns_digit digit = Besns_digit::undefined;
    
    // nested switches, represent arithmetic table
    switch (first)
    {
        case Besns_digit::neg_one:
            switch (second)
            {
                case Besns_digit::neg_one:
                    digit = Besns_digit::pos_one;
                    break;
                case Besns_digit::zero:
                    digit = Besns_digit::zero;
                    break;
                case Besns_digit::pos_one:
                    digit = Besns_digit::neg_one;
                    break;
                default:
                    break;
            }
            break;
        case Besns_digit::zero:
            // no matter what is second digit if we multiply with zero
            digit = Besns_digit::zero;
            break;
        case Besns_digit::pos_one:
            switch (second)
            {
                case Besns_digit::neg_one:
                    digit = Besns_digit::neg_one;
                    break;
                case Besns_digit::zero:
                    digit = Besns_digit::zero;
                    break;
                case Besns_digit::pos_one:
                    digit = Besns_digit::pos_one;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    return digit;
}
    
}
