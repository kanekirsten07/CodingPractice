#include "KirstenSharedPtr.h"


const int* KirstenSharedPtr::Get()
{
	++m_refCounter;
	return KirstenSharedPtr::m_node;
}

