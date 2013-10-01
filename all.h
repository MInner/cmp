#pragma once

#include <utility>

class Exp;
class IdExp;
class NumExp;
class OpExp;
class EseqExp;
class Statement;
class CompoundStatement;
class PrintStm;
class AssignStm;
class ExpList;
class VarTable;

typedef std::pair<int, const VarTable*> IVPair;
