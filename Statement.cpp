#include "Statement.h"
#include "ExpList.h"
#include "Exp.h"
#include "Vartable.h"
#include <stdio.h>
#include <iostream>

using namespace std;

CompoundStatement::CompoundStatement( const Statement* first, const Statement* second ) :
firstStm( first ), secondStm( second )
{
    assert( firstStm != 0 );
    assert( secondStm != 0 );
}

const VarTable* CompoundStatement::Exec(const VarTable* table) const
{
    table = firstStm->Exec(table);
    table = secondStm->Exec(table);
    return table;
}

AssignStm::AssignStm( const string _id, const Exp* _exp ) :
id( _id ), exp( _exp )
{
    assert( _id != "" );
    assert( _exp != 0 );
}

const VarTable* AssignStm::Exec(const VarTable* table) const
{
    VarTable* t = new VarTable(*table);
    t->setVar(id, exp->Exec(table));
    return t;
}

PrintStm::PrintStm( const ExpList* expList) : expList( expList )
{
    assert( expList != 0 );
}

const VarTable* PrintStm::Exec(const VarTable* table) const
{
    const ExpList* l = new ExpList(*expList);
    while (l != NULL)
    {
        const Exp* cur = l->exp;
        printf("%d ", cur->Exec(table));
        l = l->expList;
    }
    return table;
}

Statement::~Statement() {}


