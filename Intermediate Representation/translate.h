namespace Translate;
class ISuntreeWrapper {
public:
	const Tree::Exp* ToExp() const = 0; // как Expr
	const Tree::Stm* ToStm() const = 0; // как Stm
	const Tree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const = 0; // как if/jump
}
