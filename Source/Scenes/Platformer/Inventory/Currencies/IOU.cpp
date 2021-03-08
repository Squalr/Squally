#include "IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

IOU* IOU::create()
{
	IOU* instance = new IOU();

	instance->autorelease();

	return instance;
}

IOU::IOU() : super()
{
}

IOU::~IOU()
{
}

LocalizedString* IOU::getString()
{
	return IOU::getIOUString();
}

LocalizedString* IOU::getStringPlural()
{
	return IOU::getIOUStringPlural();
}

const std::string& IOU::getIconResource()
{
	return IOU::getIOUIconResource();
}

const std::string& IOU::getSerializationKey()
{
	return IOU::getIOUIdentifier();
}

std::string IOU::getIOUIdentifier()
{
	return "IOU";
}

std::string IOU::getIOUIconResource()
{
	return ItemResources::Collectables_Currency_IOU;
}

LocalizedString* IOU::getIOUString()
{
	return Strings::Items_Currency_IOU::create();
}

LocalizedString* IOU::getIOUStringPlural()
{
	return Strings::Items_Currency_IOUs::create();
}
