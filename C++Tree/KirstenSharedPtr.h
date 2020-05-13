#include <KirstenNode.h>
class KirstenSharedPtr
{
public:

	KirstenSharedPtr Make(int v);
	KirstenNode* Get();
private:
	KirstenNode* node;
	int refCounter;
	KirstenSharedPtr(int v)
	{
		node = new KirstenNode(v);
	}

	~KirstenSharedPtr()
	{
		--refCounter;
		if (refCounter == 0)
		{
			delete node;
		}
	}
};