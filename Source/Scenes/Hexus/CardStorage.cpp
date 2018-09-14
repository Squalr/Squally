#include "CardStorage.h"

CardStorage* CardStorage::create()
{
	CardStorage* instance = new CardStorage();

	instance->autorelease();

	return instance;
}

CardStorage::CardStorage()
{
}

CardStorage::~CardStorage()
{
}
