#include "KirstenNode.h"
class KirstenSharedPtr
{
private:
	int* m_refCounter;
	KirstenSharedPtr() {}

public:
	KirstenNode* m_node;
	KirstenNode* Get();
	int GetRefCounter() { return *m_refCounter; }

	KirstenSharedPtr(const int& v)
	{
		m_node = new KirstenNode(v);
		m_refCounter = new int(1);
	}

	KirstenSharedPtr(const KirstenSharedPtr& ptr)
	{
		(*ptr.m_refCounter)++;
		m_refCounter = ptr.m_refCounter;
		m_node = ptr.m_node;
	}
	~KirstenSharedPtr()
	{
		(*m_refCounter)--;
		if (m_refCounter <= 0)
		{
			delete m_node;
			delete m_refCounter;
		}
	}
	
	bool operator==(const KirstenSharedPtr& x)
	{
		return m_refCounter == x.m_refCounter && m_node == x.m_node;
	};

	bool operator!=(const KirstenSharedPtr& x)
	{
		return m_refCounter != x.m_refCounter || m_node != x.m_node;
	};

	void operator = (const KirstenSharedPtr& k)
	{
		m_refCounter = k.m_refCounter;
		m_node = k.m_node;
	}


};