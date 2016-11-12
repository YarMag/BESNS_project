//
//  besns_parallel_summator.cpp
//
//  File contains Besns_parallel_summator class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_parallel_summator.h"
#include "besns_arithmetic_helper.h"
#include "besns_corrector.h"

namespace besns
{

// Besns_parallel_summator class
//

// gets sum for two numbers
// param first: first summand
// param second: second summand
// returns: sum number
Besns_number Besns_parallel_summator::get_sum(const Besns_number& first, const Besns_number& second) // exception
{
	// sometimes there are errors when sum with zero - summation result is incorrect
	// to deal with such issue, just return argument which differs from zero
	bool is_first_zero = first.is_zero();
	bool is_second_zero = second.is_zero();

	if (is_first_zero && !is_second_zero)
	{
		// if first is zero and second is not - return second number's copy
		return Besns_number(second);
	}
	else if (is_second_zero)
	{
		// optimization trick - no need to check first number
		// we do not care if first is zero or not - returning first number's copy is correct anyway
		// it would be a copy of zero (if both are zeros) or a copy of some value (if second is zero and first is not)
		return Besns_number(first);
	}
	else
		; // do nothing, calculate in usual way

	return _calculate_sum(first, second); // exception
}

Besns_number Besns_parallel_summator::_calculate_sum(const Besns_number& first, const Besns_number& second) // exception
{
	uint32_t number_dimension = std::max(first.get_dimension(), second.get_dimension());
	
    // helpers
    // first summation level
    Besns_number current_sum(number_dimension); // exception
    Besns_number current_digit_transfer(number_dimension); // exception
    Besns_number current_over_digit_transfer(number_dimension); // exception
    
    // second summation level
	Besns_number sum_digit_transfer_first_digits(number_dimension); // exception
	Besns_number sum_digit_transfer_second_digits(number_dimension); // exception
    
    // third level, i.e. result
    Besns_number result(number_dimension); // exception
    
	// perform parallel summation in three stages
    _calculate_first_summation_level(first, second, current_sum, current_digit_transfer, current_over_digit_transfer);
    _calculate_second_summation_level(current_sum, current_digit_transfer, sum_digit_transfer_first_digits, sum_digit_transfer_second_digits);
    _calculate_third_summation_level(current_over_digit_transfer, sum_digit_transfer_first_digits, sum_digit_transfer_second_digits, result);
    
    // deal with fictive and fact overflow
    Besns_corrector::fix_fictive_overflow(result);
    Besns_corrector::perform_overflow_correction(result);
    
    return result;
}

// calculates vectors for the first summation level
// param first: first besns summand
// param second: second besns summand
// param sum_number: output param for storing current sum digits
// param digit_transfer_number: output param for storing current digit trasfers
// param over_digit_transfer_number: output param for storing current transfers over digit
void Besns_parallel_summator::_calculate_first_summation_level(const Besns_number& first, const Besns_number& second, Besns_number& sum_number, Besns_number& digit_transfer_number, Besns_number& over_digit_transfer_number)
{
    // since code uses shift to 2 digits, must set corresponding constraint
    const int32_t lowest_acceptable_index = first.get_lowest_index() + 2;
    
    // start from last digit, i.e. the lowest one
	for ( int32_t current_digit = first.get_highest_index(); current_digit >= lowest_acceptable_index; current_digit-- )
    {
        Besns_triad current_triad = Besns_arithmetic_helper::get_triad_sum(first.get_digit(current_digit), second.get_digit(current_digit));
        
		// set triad's digits to corresponding vectors
		// for digits where set operation won't be executed, there must be zeros by default
        sum_number.set_digit(current_digit, std::get<2>(current_triad));
        digit_transfer_number.set_digit(current_digit-1, std::get<1>(current_triad));
        over_digit_transfer_number.set_digit(current_digit-2, std::get<0>(current_triad));
    }
}

// calculates vectors for the second summation level
// param sum_number: vector storing current sum digits
// param digit_transfer_number: vector storing current digit trasfers
// param sum_digit_transfer_first_digits: output param for storing low dyad's digits which are the result of summation input operands
// param sum_digit_transfer_second_digits: output param for storing high dyad's digits which are the result of summation input operands
void Besns_parallel_summator::_calculate_second_summation_level(const Besns_number& sum_number, const Besns_number& digit_transfer_number, Besns_number& sum_digit_transfer_first_digits, Besns_number& sum_digit_transfer_second_digits)
{
    // since code uses shift to 1 digits, must set corresponding constraint
    const int32_t lowest_acceptable_index = sum_number.get_lowest_index() + 1;
    
    // handle digits until -1 index is reached to avoid 
	for ( int32_t current_digit = sum_number.get_highest_index(); current_digit >= lowest_acceptable_index; current_digit-- )
    {
        Besns_dyad current_dyad = Besns_arithmetic_helper::get_dyad_sum(sum_number.get_digit(current_digit), digit_transfer_number.get_digit(current_digit));
        
		// set dyad's digits to corresponding vectors
		// for digits where set operation won't be executed, there must be zeros by default
        sum_digit_transfer_second_digits.set_digit(current_digit, std::get<1>(current_dyad));
        sum_digit_transfer_first_digits.set_digit(current_digit - 1, std::get<0>(current_dyad));
    }
}

// calculates result vector
// param over_digit_transfer_number: vector storing current transfers over digit
// param sum_digit_transfer_first_digits: vector storing low dyad's digits which are the result of summation input operands
// param sum_digit_transfer_second_digits: vector storing high dyad's digits which are the result of summation input operands
// param result: output param for total summation result
void Besns_parallel_summator::_calculate_third_summation_level(const Besns_number& over_digit_transfer_number, const Besns_number& sum_digit_transfer_first_digits, const Besns_number& sum_digit_transfer_second_digits, Besns_number& result)
{
    // unlike first and second level calculations, here we don't shift digits and just get result as is
    const int32_t lowest_acceptable_index = over_digit_transfer_number.get_lowest_index();
    
    // sum all digits from arguments
	for ( int32_t current_digit = over_digit_transfer_number.get_highest_index(); current_digit >= lowest_acceptable_index; current_digit--)
    {
		// sum digits from all the three vectors
        Besns_digit result_digit = Besns_arithmetic_helper::get_par_summation_digit_sum(over_digit_transfer_number.get_digit(current_digit), sum_digit_transfer_first_digits.get_digit(current_digit), sum_digit_transfer_second_digits.get_digit(current_digit));
        
        result.set_digit(current_digit, result_digit);
    }
}

}
