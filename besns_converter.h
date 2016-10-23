//
//  besns_converter.h
//
//  File contains Besns_converter class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_converter_h
#define besns_converter_h

#include <stdint.h>
#include <string>

namespace besns
{

//
// Besns_converter class
//
// Static class allows to convert double number to string representation in BESNS and back.
//
class Besns_converter
{
public:
    // converts double number to string besns representation
    // param number: number to convert, its absolute value must be in range [0;1)
    // param required_dimension: an amount of digits which are followed by auxiliary digits
    // returns: besns string for passed number
	static std::string double_to_besns_str(double number, uint32_t required_dimension); // exception
    
    // converts besns string number to its double equivalent
    // param besns_str: besns string to convert
    // returns: double number with absolute value in range [0;1)
    static double besns_str_to_double(const std::string& besns_str); // exception
    
private:
    
    // gets binary representation of the specified number
    // param number: number to present in binary code
    // param required_dimension: an amount of digits followed by sign bit
    // returns: string with binary code
    static std::string _get_binary_code_string(double number, uint32_t required_dimension); // exception
    
    // decodes binary code string to double number
    // param binary_code_string: string to decode
    // returns: double number less than 1 encoded in passed string
    static double _get_number(const std::string& binary_code_string);
    
    // get two's complement for passed binary code, i.e. binary code for negative number
    // param binary_code_string: source string for two's complement
    // returns: number's two's complement string
	static std::string _get_twos_complement(const std::string& binary_code_string); // exception
    
    // converts passed string with binary code to besns string
    // param str_to_convert: string for conversion
    // returns: besns string
	static std::string _get_besns_string(const std::string& str_to_convert); // exception
    
    // gets besns digit for passed bits
    // method is using when convert binary code to besns code
    // param first: first digit
    // param second: second digit
    // returns: besns digit matching combination of specified arguments
	static char _get_besns_char_for_digits(char first, char second);
    
private:
    // constants
	static const char s_zero_char; // char using to represent 0 in binary code
	static const char s_one_char; // char using to represent 1 in binary code
};

}

#endif
