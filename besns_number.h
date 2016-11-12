//
//  besns_number.h
//
//  File contains Besns_number class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_number_h
#define besns_number_h

#include <stdint.h>
#include <string>
#include <vector>

#include "besns_digit.h"

namespace besns
{

//
// Besns_number class
//
// Class represents BESNS number.
//
class Besns_number
{
public:
    // constants
    static const uint32_t s_auxiliary_digits_number;
public:
    // constructors
    Besns_number(void); // exception
    
    // param dimension: an amount of digits after auxiliary digits
    Besns_number(uint32_t dimension); // exception
    
    // param besns_str: besns str to be represented as number
    Besns_number(const std::string& besns_str); // exception

	// param number: double number to represent
	// param required_dimension: an amount of digits which are followed by auxiliary digits
	Besns_number(double number, uint32_t required_dimension); // exception

    // destructor
    ~Besns_number(void);
    
    // digits access
    Besns_digit get_digit(int32_t index) const; // exception
    void set_digit(int32_t index, Besns_digit digit);
    
    // returns: number's lowest possible digit index
    int32_t get_lowest_index(void) const;
    
    // returns: number's highest possible digit index
    int32_t get_highest_index(void) const;
    
    // returns: dimension including auixiliary digits and number digits
    uint32_t get_dimension(void) const;
    
	// returns: true if number has zeros only
	bool is_zero(void) const;

    // conversion methods
    
    // returns: str representation for current number
    const std::string& to_str(void); // exception
    
    // returns: double representation for current number
    double to_double(void);
    
private:
    // inits
    
    // fills current number with zeros
    void _init_with_zeros(void);
    
	// performs constructor actions for string with besns number
	// param besns_str: string which contains besns number
	void _construct_with_string(const std::string& besns_str); // exception

    // inits number with passed besns string
    void _init_with_string(const std::string& str); // exception
    
    // helpers
    
    // caches string which represents current besns representation
    void _cache_str_representation(void); // exception
    
    // converts specified char to corresponding besns digit
    // param ch: char to convert
    // returns: besns digit
    Besns_digit _convert_char(char ch) const; // exception
    
    // converts specified besns digit to corresponding char representation
    // param digit: digit to be converted
    // returns: char for besns digit
    char _convert_digit(Besns_digit digit) const; // exception
    
    // converts client external index to internal vector's index
    // param index: client index to convert (might be less than zero)
    // returns: index in number's vector
    uint32_t _convert_index(int32_t index) const;
    
private:
    // constants
    static const uint32_t s_default_dimension; // default dimension for number
    static const int32_t s_lowest_number_index; // lowest possible client index to access digit

private:
    uint32_t m_dimension; // number's dimension, must take into account both number's digits and auxiliary ones
    std::vector<Besns_digit> m_number; // vector stores besns digits representing current number
    
    // utilities
    std::string m_cached_str; // cached string representation
    bool m_number_changed; // true if number has changed since last caching was done
};
    
}

#endif /* besns_number_h */
