#include "stm.h"
#include "ExpList.h"
#include "Exp.h"

CompoundStatement::CompoundStatement( const Statement* first, const Statement* second ) :
firstStm( first ), secondStm( second )
{
    assert( firstStm != 0 );
    assert( secondStm != 0 );
}

AssignStm::AssignStm( const string _id, const Exp* _exp ) :
id( _id ), exp( _exp )
{
    assert( _id != "" );
    assert( _exp != 0 );
}

PrintStm::PrintStm( const ExpList* expList) :
expList( expList )
{
    assert( expList != 0 );
}

