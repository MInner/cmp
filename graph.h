#include <list>

template< class T >
class Node
{
public:
	T* data;
	std::list< Node< T >* > in_nodes;
	std::list< Node< T >* > out_nodes;
	Node(T* item)
	{
		data = item;
	}
	Node<T>* addChild(T* item)
	{
		Node<T>* ch = new Node<T>(item);
		ch->in_nodes.push_back(this);
		out_nodes.push_back(ch);
	}

};