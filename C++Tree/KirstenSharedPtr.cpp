#include "KirstenSharedPtr.h"

KirstenNode* KirstenSharedPtr::Get()
{
	++refCounter;
	return node;
}


KirstenSharedPtr KirstenSharedPtr::Make(int v)
{
	return KirstenSharedPtr(v);
}

