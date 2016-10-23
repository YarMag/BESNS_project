//
//  besns_corrector.h
//
//  File contains Besns_corrector class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_corrector_h
#define besns_corrector_h

#include "besns_number.h"

namespace besns
{

//
// Besns_corrector class
//
// Static class implements logic for besns numbers correction.
//
class Besns_corrector
{
public:
    // fixes fictive overflow in besns number
	// param number: besns number to fix
    static void fix_fictive_overflow(Besns_number& number);

	// corrects real overflow in besns number
	// param number: besns number to correct
    static void perform_overflow_correction(Besns_number& number);

	// corrects real overflow in string besns number
	// param besns_string: besns number in string format to correct
    static void perform_overflow_correction(std::string& besns_string);
};

}

#endif /* besns_corrector_h */
