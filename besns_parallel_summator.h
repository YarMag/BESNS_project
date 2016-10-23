//
//  besns_parallel_summator.h
//
//  File contains Besns_parallel_summator class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_parallel_summator_h
#define besns_parallel_summator_h

#include "besns_summator.h"

namespace besns
{

//
// Besns_parallel_summator class
//
// Class implements summation with parallel method.
//
class Besns_parallel_summator: public Besns_summator
{
public:
	// constructor/destructor
    Besns_parallel_summator(void);
    virtual ~Besns_parallel_summator(void);
    
	// gets sum for two numbers
    // param first: first summand
    // param second: second summand
    // returns: sum number
    virtual Besns_number get_sum(const Besns_number& first, const Besns_number& second);
    
private:
    // calculates vectors for the first summation level
	// param first: first besns summand
	// param second: second besns summand
	// param sum_number: output param for storing current sum digits
	// param digit_transfer_number: output param for storing current digit trasfers
	// param over_digit_transfer_number: output param for storing current transfers over digit
    void _calculate_first_summation_level(const Besns_number& first, const Besns_number& second, Besns_number& sum_number, Besns_number& digit_transfer_number, Besns_number& over_digit_transfer_number);
    
	// calculates vectors for the second summation level
	// param sum_number: vector storing current sum digits
	// param digit_transfer_number: vector storing current digit trasfers
	// param sum_digit_transfer_first_digits: output param for storing low dyad's digits which are the result of summation input operands
	// param sum_digit_transfer_second_digits: output param for storing high dyad's digits which are the result of summation input operands
	void _calculate_second_summation_level(const Besns_number& sum_number, const Besns_number& digit_transfer_number, Besns_number& sum_digit_transfer_first_digits, Besns_number& sum_digit_transfer_second_digits);
    
	// calculates result vector
	// param over_digit_transfer_number: vector storing current transfers over digit
	// param sum_digit_transfer_first_digits: vector storing low dyad's digits which are the result of summation input operands
	// param sum_digit_transfer_second_digits: vector storing high dyad's digits which are the result of summation input operands
	// param result: output param for total summation result
	void _calculate_third_summation_level(const Besns_number& over_digit_transfer_number, const Besns_number& sum_digit_transfer_first_digits, const Besns_number& sum_digit_transfer_second_digits, Besns_number& result);
};

}

#endif /* besns_parallel_summator_h */
