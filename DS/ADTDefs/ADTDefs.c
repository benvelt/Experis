/**************************************************************************************
    Author: Dudi Kahana
    Creation date :      1.9.10
    Last modified date:  10.6.18 by Alex Katz: names cleanup
    Description : ADT Error General definitions.
***************************************************************************************/
#include <stdio.h>

#include "ADTDefs.h"

const char* s_errDescription[ERR_ADT_MAX] =
{
    /* General ADT Errors - Description */
    "OK",
    "General error",
    "Not Initialized error",
    "Allocation error",
    "ReAllocation error",
    "Underflow error",
    "Overflow",
    "Wrong Index",
    /* Vector Errors */

    /* Stack  Errors */

    /* LinkedList  Errors */

    /* Bit Vector*/
    
	/* ADT_ERR_MAX */
};

void ADTErrPrint(ADTErr _errNum, const char* _usrMsg)
{
    if (0 == _errNum && _errNum >= ERR_ADT_MAX)
    {
		_errNum = ERR_ADT_MAX;
    }
    printf("Error: num=%d, description='%s', msg=%s\n",
               _errNum, s_errDescription[_errNum], _usrMsg);
}

