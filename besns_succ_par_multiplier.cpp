//
//  besns_succ_par_multiplier.cpp
//
//  File contains Besns_succ_par_multiplier class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_succ_par_multiplier.h"
#include "besns_arithmetic_helper.h"
#include "besns_parallel_summator.h"
#include "besns_corrector.h"

namespace besns
{

// constructor/destructor
Besns_succ_par_multiplier::Besns_succ_par_multiplier(void)
{
}

Besns_succ_par_multiplier::~Besns_succ_par_multiplier(void)
{
}

// gets multiplication of two numbers
// param first: first operand
// param second: second operand
// returns: product of the specified operands
Besns_number Besns_succ_par_multiplier::get_mul(const Besns_number& first, const Besns_number& second)
{
    uint32_t number_dimension = first.get_dimension() + second.get_dimension() - Besns_number::s_auxiliary_digits_number;
    
    // start with not lowest index - in multiplication we skip auxiliary digits
    const int32_t start_index = second.get_lowest_index() + Besns_number::s_auxiliary_digits_number;
    const int32_t end_index = second.get_highest_index();
    
    Besns_number result(number_dimension);
    
    // copy auxiliary digits - they are not the result of the multiplication
    for ( int32_t result_index = first.get_lowest_index(); result_index < start_index; result_index++)
    {
        result.set_digit(result_index, first.get_digit(result_index));
    }
    
    Besns_parallel_summator helper_summator;
    
	// multiplication
    for ( int32_t current_index = start_index; current_index <= end_index; current_index++)
    {
        Besns_digit current_digit = second.get_digit(current_index);
        
        // multiply with non-zero only
        if (current_digit != Besns_digit::zero)
        {
            // partial product to store result of the current multiplication
            Besns_number partial_product(number_dimension);
            
            // perform local multiplication
            for ( int32_t multiplier_index = first.get_lowest_index() + Besns_number::s_auxiliary_digits_number; multiplier_index <= first.get_highest_index(); multiplier_index++)
            {
                // trick - add (current_index-1) for digit index to immediately get 'shifted' number
                partial_product.set_digit(multiplier_index + (current_index), Besns_arithmetic_helper::get_digit_mul(current_digit, first.get_digit(multiplier_index)));
            }
            
            // use parallel summator to get multiplication
            result = helper_summator.get_sum(result, partial_product);
        }
        else
            ; // no need to multiply, sum, etc., since current digit is zero
    }
    
    // deal with fictive and fact overflow
    Besns_corrector::fix_fictive_overflow(result);
    Besns_corrector::perform_overflow_correction(result);
    
    return result;
}
    
}
