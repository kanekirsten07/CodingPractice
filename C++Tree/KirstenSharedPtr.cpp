#include "KirstenSharedPtr.h"

KirstenNode* KirstenSharedPtr::m_node = nullptr;
int KirstenSharedPtr::m_refCounter = 0;

KirstenNode* KirstenSharedPtr::Get()
{
	return KirstenSharedPtr::m_node;
}


KirstenSharedPtr KirstenSharedPtr::Make(const int& v)
{
	return KirstenSharedPtr(v);
}



