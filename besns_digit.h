//
//  besns_digit.h
//
//  File contains constants and types necessary to work with BESNS numbers.
//  BESNS is Binary Excessive Signed Numeral System.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_digit_h
#define besns_digit_h

#include <tuple>

namespace besns
{

// char digits representation
const char BESNS_DIGIT_POS_ONE = '1';
const char BESNS_DIGIT_ZERO = '0';
const char BESNS_DIGIT_NEG_ONE = '|';

// enum to use digits in number
enum Besns_digit
{
undefined = 2, // allows to determine incorrect number state
pos_one = 1,
zero = 0,
neg_one = -1
};

// types for specific operations in summation, multiplication, etc.
typedef std::tuple<Besns_digit, Besns_digit, Besns_digit> Besns_triad;
typedef std::tuple<Besns_digit, Besns_digit> Besns_dyad;
    
}

#endif /* besns_digit_h */
