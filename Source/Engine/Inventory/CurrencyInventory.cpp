#include "CurrencyInventory.h"

using namespace cocos2d;

CurrencyInventory::CurrencyInventory(std::string saveKey, int capacity) : super(saveKey, capacity)
{
	this->load();
}

CurrencyInventory::~CurrencyInventory()
{
}

void CurrencyInventory::onEnter()
{
	super::onEnter();
}

void CurrencyInventory::initializeListeners()
{
	super::initializeListeners();
}
