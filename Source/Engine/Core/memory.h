#pragma once

namespace kiko
{
	struct MemoryAllocation //like a class but stores a data structure
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker //tracks memory that's been allocated
	{
	public:
		void Add(void* address, size_t size); //adds allocation to the list
		void Remove(void* address, size_t);

		void DisplayInfo();

	private:
		size_t m_bytesAllocated = 0;
		size_t m_numAllocations = 0;
	};
	extern kiko::MemoryTracker g_memoryTracker;
}
