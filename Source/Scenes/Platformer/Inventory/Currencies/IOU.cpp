#include "IOU.h"

#include "Resources/ObjectResources.h"

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

std::string IOU::getIconResource()
{
	return IOU::getIOUIconResource();
}

std::string IOU::getSerializationKey()
{
	return IOU::getIOUIdentifier();
}

std::string IOU::getIOUIdentifier()
{
	return "IOU";
}

std::string IOU::getIOUIconResource()
{
	return ObjectResources::Collectables_Currency_IOU;
}

LocalizedString* IOU::getIOUString()
{
	return Strings::Items_Currency_IOUs::create();
}
