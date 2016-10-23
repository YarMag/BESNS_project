//
//  besns_successive_summator.h
//
//  File contains Besns_successive_summator class interface.
//
//  Copyright (c) 2016 Magin Yaroslav. All rights reserved.
//

#ifndef besns_successive_summator_h
#define besns_successive_summator_h

#include "besns_summator.h"

namespace besns
{

//
// Besns_successive_summator class
//
// Class implements summation with successive method.
//
class Besns_successive_summator: public Besns_summator
{
public:
    // constructor/destructor
    Besns_successive_summator(void);
    virtual ~Besns_successive_summator(void);
    
    // gets sum for two numbers
    // param first: first summand
    // param second: second summand
    // returns: sum number
    virtual Besns_number get_sum(const Besns_number& first, const Besns_number& second);
    
private:
    // corrects triad according to arithmetic rules
    void _correct_triad(Besns_triad& triad) const;
    
    // shift triad - throw away first digit and add zero as new third
    void _shift_triad(Besns_triad& triad) const;
};

}

#endif /* besns_successive_summator_h */
