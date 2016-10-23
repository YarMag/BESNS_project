//
//  besns_converter.cpp
//
//  File contains Besns_converter class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_converter.h"
#include "besns_number.h"
#include "besns_corrector.h"

#include <algorithm> // reverse(...) function
#include <cmath> // pow(...) and abs(...) functions

namespace besns
{

// Besns_converter class
//

// constants
const char Besns_converter::s_zero_char = '0';
const char Besns_converter::s_one_char = '1';

// converts double number to string besns representation
// param number: number to convert, its absolute value must be in range [0;1)
// param required_dimension: an amount of digits which are followed by auxiliary digits
// returns: besns string for passed number
std::string Besns_converter::double_to_besns_str(double number, uint32_t required_dimension)
{
    // by definition, besns is used to represent numbers in range [0;1)
    if (std::abs(number) > 1)
        throw std::runtime_error(""); // exception
    
    // get binary code first - we will handle it to represent besns number
    std::string str_to_convert = _get_binary_code_string(number, required_dimension); // exception
    
    // if number is negative, we must work with its two's complement
    if (number < 0)
    {
        str_to_convert = _get_twos_complement(str_to_convert); // exception
    }
    else
        ; // do nothing
    
    // final conversion
    str_to_convert = _get_besns_string(str_to_convert); // exception
    
    // there might be overflow occurred
    Besns_corrector::perform_overflow_correction(str_to_convert);
    
    return str_to_convert;
}

// converts besns string number to its double equivalent
// param besns_str: besns string to convert
// returns: double number with absolute value in range [0;1)
double Besns_converter::besns_str_to_double(const std::string& besns_str) // exception
{
    // validation - there must be dot dividing auxiliary bits from actual number
    if (besns_str.find('.') == std::string::npos)
        throw std::runtime_error(""); // exception
    
    // we must split source number into its positive and negative part
    std::string positive_number_string;
    std::string negative_number_string;
    
    // here we split number into binary numbers
    // if digit contains 1, we write 1 to positive number string
    // if contains -1, write 1 to negative number string
    // in other cases - write 0 and move to next digit
    // since we make binary code, don't handle auxiliary digits except last one
    for (uint32_t i = Besns_number::s_auxiliary_digits_number - 1; i < besns_str.size(); i++)
    {
        // handle current digit
        switch (besns_str[i])
        {
            case BESNS_DIGIT_ZERO:
                positive_number_string += s_zero_char;
                negative_number_string += s_zero_char;
                break;
            case BESNS_DIGIT_NEG_ONE:
                positive_number_string += s_zero_char;
                negative_number_string += s_one_char;
                break;
            case BESNS_DIGIT_POS_ONE:
                positive_number_string += s_one_char;
                negative_number_string += s_zero_char;
                break;
            case '.':
                positive_number_string += '.';
                negative_number_string += '.';
                break;
            default:
                // no other chars is allowed
                throw std::runtime_error(""); // exception
        }
    }
    
    // convert both strings to double numbers
    double negative_number = (-1) * _get_number(negative_number_string); // exception
    double positive_number = _get_number(positive_number_string); // exception
    
    return positive_number + negative_number;
}

// gets binary representation of the specified number
// param number: number to present in binary code
// param required_dimension: an amount of digits followed by sign bit
// returns: string with binary code
std::string Besns_converter::_get_binary_code_string(double number, uint32_t required_dimension) // exception
{
    // negative numbers are not supported
    if (number < 0)
        throw std::runtime_error(""); // exception
    
    // initial string - sign with dot
    std::string encoded_string = "0.";
    uint32_t current_dimension = 0;
    double current_number = number;
    
    while (current_dimension != required_dimension)
    {
        current_number = current_number * 2;
        
        // if current product has 1 in its integer part - write 1 to its binary representation
        if (current_number > 1)
        {
            encoded_string += s_one_char;
            
            // trick - substract integer part to get fractional only
            // we don't have to do it if integer part is zero
            // it would be more clear to place this line after if-block, but this way looks more optimal
            current_number = current_number - (int32_t)current_number;
        }
        else
        {
            encoded_string += s_zero_char;
        }
        
        current_dimension++;
    }
    
    return encoded_string;
}

// decodes binary code string to double number
// param binary_code_string: string to decode
// returns: double number less than 1 encoded in passed string
double Besns_converter::_get_number(const std::string& binary_code_string)
{
    const size_t dot_index = binary_code_string.find('.');
    
    // binary code must contain dot
    if (dot_index == std::string::npos)
        throw std::runtime_error(""); // exception
    
    // indicates current binary digit we're working with
    int32_t current_digit = 1;
    
    // will accumulate necessary number
    double result = 0;
    
    // skip sign and dot and go through the rest of string
    for (uint32_t i = static_cast<uint32_t>(dot_index) + 1; i < binary_code_string.size(); i++)
    {
        // if digit is meaning - convert and add to result
        if (binary_code_string[i] == s_one_char)
        {
            result += pow(2, -current_digit);
        }
        else
            ; // do nothing for zero
        
        current_digit++;
    }
    
    return result;
}

// get two's complement for passed binary code, i.e. binary code for negative number
// param binary_code_string: source string for two's complement
// returns: number's two's complement string
std::string Besns_converter::_get_twos_complement(const std::string& binary_code_string) // exception
{
    // copy string to make complement
    std::string encoded_string = binary_code_string; // exception

    // string must have format x.xxxxxxxx, no matter how many digits after dot
    if (encoded_string.find('.') != 1)
        throw std::runtime_error(""); // exception

    // set sign bit to one since two's complement by definition represents negative numbers
    encoded_string[0] = s_one_char;

    // inverse string
    // skip sign and dot, start from 2-nd position 
    for (uint32_t i = 2; i < encoded_string.size(); i++)
    {
        switch (encoded_string[i])
        {
        case s_zero_char:
            encoded_string[i] = s_one_char;
            break;
        case s_one_char:
            encoded_string[i] = s_zero_char;
            break;
        default:
            throw std::runtime_error(""); // exception
        }
    }

    // now we must add 1 to the number to get two's complement
    // add 1 to the end and move back, coverting all digits
    // WARNING: overflow case isn't handled here
    for (uint32_t i = static_cast<uint32_t>(encoded_string.size()-1); i > 1; i--)
    {
        if (encoded_string[i] == s_zero_char)
        {
            // found zero, finish with adding, leave loop
            encoded_string[i] = s_one_char;
            break;
        }
        else
        {
            // act like in real addition - set char to zero and move to next digit
            encoded_string[i] = s_zero_char;
        }
    }

    return encoded_string;
}

// converts passed string with binary code to besns string
// param str_to_convert: string for conversion
// returns: besns string
std::string Besns_converter::_get_besns_string(const std::string& str_to_convert) // exception
{		
    std::string temp_string = str_to_convert; // exception
    const size_t dot_index = temp_string.find('.');

    // binary code must keep dot on 1-st position
    if (dot_index == std::string::npos || dot_index != 1)
        throw std::runtime_error(""); // exception

    temp_string.erase(temp_string.begin() + dot_index); // exception

    std::string encoded_string;
    // first auxiliary digit must be added here since it is not processed below
    encoded_string += BESNS_DIGIT_ZERO;

    // add absent zero to binary representation if necessary
    if (temp_string.size() % 2 != 0)
    {
        temp_string.push_back(s_zero_char);
    }
    else
        ; // do nothing, we have even digit pairs count

    // iterate through source string copy until pre-last char is handled
    // we get current digit, its next neighbor and then write to string corresponding besns digit
    for (uint32_t i = 0; i < temp_string.size() - 1; i++)
    {
        encoded_string += _get_besns_char_for_digits(temp_string[i], temp_string[i+1]); // exception
    }

    // must insert dot after auxiliary digits
    encoded_string.insert(encoded_string.begin() + Besns_number::s_auxiliary_digits_number, '.'); // exception

    return encoded_string;
}

// gets besns digit for passed bits
// method is using when convert binary code to besns code
// param first: first digit
// param second: second digit
// returns: besns digit matching combination of specified arguments
char Besns_converter::_get_besns_char_for_digits(char first, char second) // exception
{
    char result;

    // nested switches to get corresponding besns digit
    switch (first)
    {
    case s_zero_char:
        switch (second)
        {
        case s_zero_char:
            result = BESNS_DIGIT_ZERO;
            break;
        case s_one_char:
            result = BESNS_DIGIT_POS_ONE;
            break;
        default:
            throw std::runtime_error(""); // exception
        }
        break;
    case s_one_char:
        switch (second)
        {
        case s_zero_char:
            result = BESNS_DIGIT_NEG_ONE;
            break;
        case s_one_char:
            result = BESNS_DIGIT_ZERO;
            break;
        default:
            throw std::runtime_error(""); // exception
        }
        break;
    default:
        throw std::runtime_error(""); // exception
    }

    return result;
}

}
