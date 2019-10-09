#include "assert.h"
#include <Exit.h>

void assert(bool condition)
{
    if (!condition)
    {
	Exit();
    }
}

