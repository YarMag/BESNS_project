//
//  besns_successive_summator.cpp
//
//  File contains Besns_successive_summator class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_successive_summator.h"
#include "besns_arithmetic_helper.h"
#include "besns_corrector.h"

namespace besns
{

// Besns_successive_summator class
//

// constructor/destructor
Besns_successive_summator::Besns_successive_summator(void)
{
}

Besns_successive_summator::~Besns_successive_summator(void)
{
}

// gets sum for two numbers
// param first: first summand
// param second: second summand
// returns: sum number
Besns_number Besns_successive_summator::get_sum(const Besns_number& first, const Besns_number& second)
{
    uint32_t number_dimension = std::max(first.get_dimension(), second.get_dimension());
    Besns_number result(number_dimension); // exception
    
    // we must start from lowest digit for result
	int32_t current_result_digit_index = first.get_lowest_index();
    
    // here we accumulate summation results
    Besns_triad current_triad = std::make_tuple(Besns_digit::zero, Besns_digit::zero, Besns_digit::zero);
	uint32_t number_highest_index = std::max(first.get_highest_index(), second.get_highest_index());
    
    // run loop to sum all digits in numbers
    // for summands we skip auxiliary digits
	for (uint32_t cur_summand_digit_index = current_result_digit_index + Besns_number::s_auxiliary_digits_number; cur_summand_digit_index <= number_highest_index; cur_summand_digit_index++)
    {
        Besns_triad new_triad = Besns_arithmetic_helper::get_triad_sum(first.get_digit(cur_summand_digit_index), second.get_digit(cur_summand_digit_index));
        
        std::get<0>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<0>(current_triad), std::get<0>(new_triad));
        std::get<1>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<1>(current_triad), std::get<1>(new_triad));
        std::get<2>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<2>(current_triad), std::get<2>(new_triad));
        
        // there might be incorrect result in 1-st triad's digit
        _correct_triad(current_triad);
        
        // add new digit to result
        result.set_digit(current_result_digit_index, std::get<0>(current_triad));
        
        // go to next digit
        current_result_digit_index++;
        _shift_triad(current_triad);
    }
    
    // now we must add 000-triad twice
    // no need to create triad, just pass to helper 0-digit
    for (uint32_t i = 0; i < 2; i++)
    {
        std::get<0>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<0>(current_triad), Besns_digit::zero);
        std::get<1>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<1>(current_triad), Besns_digit::zero);
        std::get<2>(current_triad) = Besns_arithmetic_helper::get_digit_sum(std::get<2>(current_triad), Besns_digit::zero);
        _correct_triad(current_triad);
        
        result.set_digit(current_result_digit_index, std::get<0>(current_triad));
        current_result_digit_index++;
        _shift_triad(current_triad);
    }
    
    // deal with fictive and fact overflow
    Besns_corrector::fix_fictive_overflow(result);
    Besns_corrector::perform_overflow_correction(result);
    
    return result;
}

// corrects triad according to arithmetic rules
void Besns_successive_summator::_correct_triad(Besns_triad& triad) const
{
    // positive values in the middle aren't allowed, so replace them
    if (std::get<0>(triad) == Besns_digit::zero && std::get<1>(triad) == Besns_digit::pos_one)
    {
        std::get<0>(triad) = Besns_digit::pos_one;
        std::get<1>(triad) = Besns_digit::neg_one;
    }
    else
        ; // add correction on demand
}

// shift triad - throw away first digit and add zero as new third
void Besns_successive_summator::_shift_triad(Besns_triad& triad) const
{
    // create new triad without 0-th digit
    triad = std::make_tuple(std::get<1>(triad), std::get<2>(triad), Besns_digit::zero);
}

}
