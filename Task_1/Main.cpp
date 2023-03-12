#include "WatchJSON.h"

int main()
{
	WatchJSON wj;

	wj.Start();
	wj.Loop();

	return 0;
}