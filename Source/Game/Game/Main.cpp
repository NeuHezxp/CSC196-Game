#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>

using namespace std;

void* operator new(size_t size)
{
	std::cout << "allocation: " << size << endl;

	return malloc(size);
}

void operator delete(void* address, size_t size)
{
	std::cout << "deallocation: " << size << endl;

	free(address);
}

int main()
{
	// memory
	//void* p = malloc(sizeof(int));
	//int* ip = (int*)p;
	//if (ip)
	//{
	//	*ip = 4;
	//	std::cout << ip << std::endl;
	//	std::cout << *ip << std::endl;
	//}
	//free(p);

	int* p = new int;
	delete p;

	cout << kiko::getFilePath() << endl;


	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 3; i++)
	{
		cout << kiko::random(5, 10) << endl;
	}
}
