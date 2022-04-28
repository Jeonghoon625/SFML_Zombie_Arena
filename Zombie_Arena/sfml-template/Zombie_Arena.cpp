#include <iostream>
#include "Framework/Framework.h"

int main()
{
	Framework zombiArena;

	if (false == zombiArena.Initialize())
	{
		puts("Failed Initialize");

		return 1;
	}

	return zombiArena.Run();
}