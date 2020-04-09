#include "Currency.h"


using namespace cocos2d;

Currency::Currency()
{
	this->count = 0;
}

Currency::~Currency()
{
}

void Currency::setCount(int count)
{
	this->count = count;
}

int Currency::getCount()
{
	return this->count;
}
