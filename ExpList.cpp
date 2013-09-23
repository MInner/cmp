#include "ExpList.h"
#include <assert.h>

ExpList::ExpList( const Exp* exp_, const ExpList* expList_ ) :
exp( exp_ ), expList( expList_ )
{
    assert( exp_ != 0 );
}

