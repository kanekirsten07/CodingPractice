#include <thread>
#include "CoinAccount.h"
using namespace std;

int main()
{
	CoinAccount account = CoinAccount(20);

	//Start Thread
	//thread t1(account.AddBalance,50);
	//thread t2(account.RemoveBalance, 100);
}
