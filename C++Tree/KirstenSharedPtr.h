#include "KirstenNode.h"
class KirstenSharedPtr
{
public:
	static int m_refCounter;
	static KirstenNode* m_node;
	static KirstenSharedPtr Make(const int& v);
	static KirstenNode* Get();

	KirstenSharedPtr(const int& v)
	{
		m_node = new KirstenNode(v);
	}

	KirstenSharedPtr(const KirstenSharedPtr& ptr)
	{
		++m_refCounter;
		m_node = ptr.m_node;
	}
	~KirstenSharedPtr()
	{
		--m_refCounter;
		if (m_refCounter == 0)
		{
			delete m_node;
		}
	}

private:

	KirstenSharedPtr() {}

};