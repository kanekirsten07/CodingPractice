#include "KirstenSharedPtr.h"


KirstenNode* KirstenSharedPtr::Get()
{
	++m_refCounter;
	return KirstenSharedPtr::m_node;
}

