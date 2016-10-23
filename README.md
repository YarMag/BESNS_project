# BESNS_project
This repository contains C++ implementation of the BESNS (also known as ДИЗСС). Bug reports and design remarks are really appreciated. 

To start using numbers in BESNS, include file "besns_number.h".

You could create besns numbers in different ways (see header file for constructors).
For example, number could be created directly from BESNS string, like:

Besns_number first("00.0|||||11");

Here '|' char represents '-1' digit. You could change this char by editing corresponding constant in file "besns_digit.h".

To create number directly from double value, You have to use converter declared in "besns_converter.h". For now constructor with double argument is not supported. Example for creating number with the converter's help:

double input_number;
std::cin>>number;
uint32_t digits_after_point = 8;
Besns_number second(Besns_converter::double_to_besns_str(number, digits_after_point));

To operate with numbers, use summators and multiplier. Include files "besns_successive_summator.h", "besns_parallel_summator.h" and "besns_succ_par_multiplier.h" one by one, or place them in common header. Summation might look like this:

Besns_summator\* summator = new Besns_successive_summator();
Besns_number result = summator->get_sum(first, second);

Other operations could be done in similar way.

To print besns number, next methods might be used to_str(), which returns string representation, or to_double(), returning double value.

There are also some other help files. File "besns_arithmetic_helper.h" contains static class with all operations, necessary for arithmetic computations. File "besns_corrector.h" contains static class with overflow correction logic (not sure if it is complete, this code might be changed in future).

Use this code as You want, extend it, rewrite in the other programming languages, or contribute to this project. Next generations must forget a headache with sh\*t such as BESNS (ДИЗСС). Enjoy :)
