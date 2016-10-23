//
//  besns_corrector.cpp
//
//  File contains Besns_corrector class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_corrector.h"

namespace besns
{

// Besns_corrector class
//

// fixes fictive overflow in besns number
// param number: besns number to fix
void Besns_corrector::fix_fictive_overflow(Besns_number& number)
{
    // basically they are -1 and 0, but who knows, rules could be changed...
    int32_t lowest_auxiliary_digit_index = number.get_lowest_index();
    int32_t highest_auxiliary_digit_index = lowest_auxiliary_digit_index + Besns_number::s_auxiliary_digits_number - 1;
    
    // correct by replacing neighbor digits
    // must execute this operation for auxiliary digits and for the highest number digit
    for (int32_t i = lowest_auxiliary_digit_index; i <= highest_auxiliary_digit_index; i++)
    {
        Besns_digit high_digit = number.get_digit(i);
        Besns_digit low_digit = number.get_digit(i + 1);
        
        // fictive overflow occurs when we have combinations 1-1 or -11
        // they should be replaced with 01 and 0-1 respectively
        if (high_digit == Besns_digit::pos_one && low_digit == Besns_digit::neg_one)
        {
            // if we have 01 combination, overflow is fact
            // we have to correct it by moving to the closes -1 and replacing digits with 1
            // for optimization we don't put 1 to hightest index, put zero instead
            // we should do it according to correction
            number.set_digit(i, Besns_digit::zero);
            number.set_digit(i+1, Besns_digit::pos_one);
        }
        else if (high_digit == Besns_digit::neg_one && low_digit == Besns_digit::pos_one)
        {
            number.set_digit(i, Besns_digit::zero);
            number.set_digit(i + 1, Besns_digit::neg_one);
        }
		else
			; // do nothing, no other special cases for fictive overflow
    }
}

// corrects real overflow in besns number
// param number: besns number to correct
void Besns_corrector::perform_overflow_correction(Besns_number& number)
{
    // basically it is 0, but who knows, rules could be changed...
    int32_t highest_auxiliary_digit_index = number.get_lowest_index() + Besns_number::s_auxiliary_digits_number - 1;
    
	// now we do correction only if number contains 1 right before the highest number digit
    if (number.get_digit(highest_auxiliary_digit_index) == Besns_digit::pos_one)
    {
        // correction is done by moving to the closest -1 and replacing digits with 1
		// also we replace 1 with 0 in the problematic digit
        number.set_digit(highest_auxiliary_digit_index, Besns_digit::zero);
        
        bool is_overflow_fixed = false;
        
		// iterate until overflow is fixed
        for (int32_t i = highest_auxiliary_digit_index + 1; i <= number.get_highest_index(); i++)
        {
			// always set 1 for digits, but leave if -1 was reached
            switch (number.get_digit(i))
            {
                case Besns_digit::neg_one:
                    number.set_digit(i, Besns_digit::pos_one);
                    is_overflow_fixed = true;
                    break;
                case Besns_digit::zero:
                    number.set_digit(i, Besns_digit::pos_one);
                    break;
                default:
                    break;
            }
            
            // leave if overflow is fixed
            if (is_overflow_fixed)
            {
                break;
            }
        }
    }
    else
        ; // no need to correct, do nothing
}

// corrects real overflow in string besns number
// param besns_string: besns number in string format to correct
void Besns_corrector::perform_overflow_correction(std::string& besns_string)
{
    const size_t dot_index = besns_string.find('.');
    
    if (dot_index == std::string::npos)
        return; // if no dot - str is unacceptable, immediate return
    
    // check digit right before the dot
    if (besns_string[dot_index - 1] == BESNS_DIGIT_POS_ONE)
    {
        bool is_overflow_fixed = false;
        
        // start from digit right after the dot
        for (uint32_t i = static_cast<uint32_t>(dot_index + 1); i < besns_string.size(); i++)
        {
			// always set 1 for digits, but leave if -1 was reached
            switch (besns_string[i])
            {
                case BESNS_DIGIT_ZERO:
                    besns_string[i] = BESNS_DIGIT_POS_ONE;
                    break;
                case BESNS_DIGIT_NEG_ONE:
                    // -1 is found, overflow is fixed
                    besns_string[i] = BESNS_DIGIT_POS_ONE;
                    is_overflow_fixed = true;
                    break;
                default:
                    break;
            }
            
            // leave if overflow is fixed
            if (is_overflow_fixed)
            {
                break;
            }
        }
    }
    else
        ; // do nothing, no overflow
}

}
