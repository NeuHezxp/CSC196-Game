#include "Core/Random.h"
#include "Core/FileIO.h"
#include "core/memory.h"
#include "core/Time.h"
#include <Renderer/Renderer.h>
#include <iostream>

using namespace std;

int main()
{
	kiko::CreateWindow("CSC196", 800, 600);
	cin.get(); //pause

	/*kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	cout << timer.GetElapsedNanoseconds() << endl;*/

	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 60000000; ++i) {}
	auto end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/

	//cout << kiko::getFilePath() << endl;
	//kiko::setFilePath("Assets");
	//cout << kiko::getFilePath() << endl;
	//size_t size;
	//kiko::getFileSize("game.txt", size);
	//cout << size << endl;

	//std::string s;
	//kiko::readFile("game.txt", s);
	//cout << s << endl;

	////kiko::seedRandom((unsigned int)time(nullptr));
	////for (int i = 0; i < 3; i++)
	////{
	////	cout << kiko::random(5, 10) << endl;
	////}
}