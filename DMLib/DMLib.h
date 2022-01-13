/* Drayton Monkman, 2022
 *
 * This header enables all subheaders and namespaces to be 
 * included with a single as a single include. This does not prevent
 * individual modules from being included as standalone headers
 * however, and they have been designed to include all required 
 * components to work as such.
 * 
 * This library acts as an assortment of miscellaneous functions, data structures,
 * and algorithm implementations. If ever I want to quickly code something in C++ or Assembly, 
 * I will implement it as a part of this library to avoid the hassle of creating 
 * small standalone projects. If eventually something I work on grows large and I see 
 * it as potentially useful to others, I will move it into it's own standalone project. 
 * 
*/


#ifndef DMLIB_
#define DMLIB_

#include "DMLib_Functions.h" 
using namespace DMLib::Functions;

#include "DMLib_Datatypes.h" 

#include "DMLib_PESolutions.h" 
using namespace DMLib::PESolutions;




#endif // !DMLIB

