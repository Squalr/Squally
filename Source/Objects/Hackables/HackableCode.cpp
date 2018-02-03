#include "HackableCode.h"

HackableCode * HackableCode::create(std::string name, void* codeStart, int codeLength)
{
	HackableCode* hackableCode = new HackableCode(name, codeStart, codeLength);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(std::string name, void* codeStart, int codeLength)
{
	this->functionName = name;
	this->codePointer = (byte*)codeStart;
	this->codeOriginalLength = codeLength;
	this->allocations = new std::map<void*, int>();
}

void* HackableCode::allocateMemory(int allocationSize)
{
	void* allocation = malloc(allocationSize);
	this->allocations->insert_or_assign(allocation, allocationSize);

	return allocation;
}

HackableCode::~HackableCode()
{
	for (auto iterator = this->allocations->begin(); iterator != this->allocations->end(); iterator++)
	{
		delete(iterator->first);
	}

	delete(this->allocations);
}
