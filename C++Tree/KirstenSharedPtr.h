
#include <assert.h>  
class KirstenSharedPtr
{
private:
	int* m_refCounter = 0;
	int* m_node = nullptr;
	KirstenSharedPtr() {}
public:
	const int& Get() const
	{
		++(*m_refCounter);
		return *m_node;
	}
	void Set(const int& value) { *m_node = value; }
	const int GetRefCounter() { return *m_refCounter; }

	KirstenSharedPtr(const int& v)
	{
		m_node = new int(v);
		m_refCounter = new int(1);
	}

	KirstenSharedPtr(const KirstenSharedPtr& ptr)
	{
		++(*ptr.m_refCounter);
		m_refCounter = ptr.m_refCounter;
		m_node = ptr.m_node;
	}
	~KirstenSharedPtr()
	{
		--(*m_refCounter);

		assert(m_refCounter >= 0);

		delete m_node;
		delete m_refCounter;
	}
	
	const bool operator==(const KirstenSharedPtr& x)
	{
		return m_refCounter == x.m_refCounter && m_node == x.m_node;
	};

	const bool operator!=(const KirstenSharedPtr& x)
	{
		return m_refCounter == x.m_refCounter && m_node == x.m_node;
	};

	void operator = (const KirstenSharedPtr& k)
	{
		m_refCounter = k.m_refCounter;
		m_node = k.m_node;
	}


};