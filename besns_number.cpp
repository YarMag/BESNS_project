//
//  besns_number.h
//
//  File contains Besns_number class implementation.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#include "besns_number.h"
#include "besns_converter.h"


namespace besns
{
    
// Besns_number class
//

// constants
const uint32_t Besns_number::s_auxiliary_digits_number = 2;
const uint32_t Besns_number::s_default_dimension = 10; // 2 for auxiliary digits, 8 for number
const int32_t Besns_number::s_lowest_number_index = -1;

// constructors
Besns_number::Besns_number(void) // exception
{
    m_dimension = s_default_dimension;
    m_number.resize(m_dimension); // exception
    
    _init_with_zeros();
    m_number_changed = true;
}

// param dimension: an amount of digits after auxiliary digits
Besns_number::Besns_number(uint32_t dimension)
{
    m_dimension = dimension;
    m_number.resize(m_dimension); // exception
    
    _init_with_zeros();
    m_number_changed = true;
}

// param besns_str: besns str to be represented as number
Besns_number::Besns_number(const std::string& besns_str) // exception
{
    _construct_with_string(besns_str); // exception
}

// param number: double number to represent
// param required_dimension: an amount of digits which are followed by auxiliary digits
Besns_number::Besns_number(double number, uint32_t required_dimension) // exception
{
    // create besns str with converter
    const std::string besns_str = Besns_converter::double_to_besns_str(number, required_dimension); // exception

    _construct_with_string(besns_str); // exception
}

// destructor
Besns_number::~Besns_number(void)
{
}

// digits access
//

Besns_digit Besns_number::get_digit(int32_t index) const
{
    uint32_t result_index = _convert_index(index);
    return m_number[result_index];
}

void Besns_number::set_digit(int32_t index, Besns_digit digit)
{
    uint32_t result_index = _convert_index(index);
    m_number[result_index] = digit;
    m_number_changed = true;
}

// returns: number's lowest possible digit index
int32_t Besns_number::get_lowest_index(void) const
{
    return s_lowest_number_index;
}

// returns: number's highest possible digit index
int32_t Besns_number::get_highest_index(void) const
{
    return m_dimension - s_auxiliary_digits_number;
}

// returns: dimension including auixiliary digits and number digits
uint32_t Besns_number::get_dimension(void) const
{
    return m_dimension;
}

// returns: str representation for current number
const std::string& Besns_number::to_str(void) // exception
{
    // if number's string representation was changed - cache it again
    if (m_number_changed)
    {
        _cache_str_representation(); // exception
        m_number_changed = false;
    }
    else
        ; // do nothing, number is actual
    
    return m_cached_str;
}

// returns: double representation for current number
double Besns_number::to_double(void)
{
    return Besns_converter::besns_str_to_double(to_str());
}

// inits
//

// fills current number with zeros
void Besns_number::_init_with_zeros(void)
{
    for (uint32_t i = 0; i < m_number.size(); i++)
    {
        m_number[i] = Besns_digit::zero;
    }
}

// performs constructor actions for string with besns number
// param besns_str: string which contains besns number
void Besns_number::_construct_with_string(const std::string& str) // exception
{
    // suppose that string is valid and have necessary amount of auxiliary digits, dot and other digits
    // if string has incorrect format, exception will be thrown during initialization
    m_dimension = static_cast<uint32_t>(str.size() - 1);
    m_number.resize(m_dimension); // exception
    
    _init_with_string(str); // exception
    m_number_changed = true;
}

// inits number with passed besns string
void Besns_number::_init_with_string(const std::string& str) // exception
{
    // str shouln't contain chars more than current number dimension with dot
    if (str.size() > m_number.size() + 1)
        throw std::runtime_error(""); // exception
    
    std::string str_to_convert = str; // exception
    const size_t dot_index = str_to_convert.find('.');
    
    // dot must persist in parsed string
    if (dot_index != std::string::npos)
    {
        // remove dot, we don't store it for number
        str_to_convert.erase(str_to_convert.begin() + dot_index);
    }
    else
        throw std::runtime_error(""); // exception
    
    uint32_t handled_digits = 0;
    
    // conversion
    for (uint32_t i = 0; i < str_to_convert.size(); i++)
    {
        m_number[i] = _convert_char(str_to_convert[i]); // exception
        handled_digits++;
    }
    
    // if we've handled not enough digits - need to complement the rest of number with zeros
    if (handled_digits != m_dimension)
    {
        for (uint32_t i = handled_digits - 1; i < m_dimension; i++)
        {
            m_number[i] = Besns_digit::zero;
        }
    }
    else
        ; // do nothing, we've handled all digits
}

// caches string which represents current besns representation
void Besns_number::_cache_str_representation(void) // exception
{
    m_cached_str.clear();
    
    // string must contain whole number with dot
    m_cached_str.resize(m_dimension + 1); // exception
    
    uint32_t handled_chars_index = 0;
    
    // cache auxiliary part
    for (uint32_t i = 0 ; i < s_auxiliary_digits_number; i++)
    {
        m_cached_str[handled_chars_index] = _convert_digit(m_number[i]); // exception
        handled_chars_index++;
    }
    
    // set dot
    m_cached_str[handled_chars_index] = '.';
    handled_chars_index++;
    
    // cache the rest part of the number
    for (uint32_t i = s_auxiliary_digits_number; i < m_dimension; i++)
    {
        m_cached_str[handled_chars_index] = _convert_digit(m_number[i]); // exception
        handled_chars_index++;
    }
}

// converts specified char to corresponding besns digit
// param ch: char to convert
// returns: besns digit
Besns_digit Besns_number::_convert_char(char ch) const // exception
{
    Besns_digit digit = Besns_digit::undefined;
    
    switch (ch)
    {
        case BESNS_DIGIT_POS_ONE:
            digit = Besns_digit::pos_one;
            break;
        case BESNS_DIGIT_ZERO:
            digit = Besns_digit::zero;
            break;
        case BESNS_DIGIT_NEG_ONE:
            digit = Besns_digit::neg_one;
            break;
        default:
            throw std::runtime_error(""); // exception
    }
    
    return digit;
}

// converts specified besns digit to corresponding char representation
// param digit: digit to be converted
// returns: char for besns digit
char Besns_number::_convert_digit(Besns_digit digit) const // exception
{
    char ch;
    
    switch (digit)
    {
        case Besns_digit::pos_one:
            ch = BESNS_DIGIT_POS_ONE;
            break;
        case Besns_digit::zero:
            ch = BESNS_DIGIT_ZERO;
            break;
        case Besns_digit::neg_one:
            ch = BESNS_DIGIT_NEG_ONE;
            break;
        default:
            throw std::runtime_error(""); // exception
    }
    
    return ch;
}

// converts client external index to internal vector's index
// param index: client index to convert (might be less than zero)
// returns: index in number's vector
uint32_t Besns_number::_convert_index(int32_t index) const
{
    // client can request -1-th digit, and this is allowed
    // but since vector's numeration starts from 0, must perform additional convertation
    // must shift passed index according to number of auxiliary digits
    return index + s_auxiliary_digits_number - 1;
}
    
}
