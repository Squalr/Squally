#include "LocalizedLabel.h"

#include "Engine/Localization/LocalizedString.h"

LocalizedLabel* LocalizedLabel::create()
{
	LocalizedLabel* label = new LocalizedLabel();

	label->autorelease();

	return label;
}

LocalizedLabel::LocalizedLabel()
{
	this->localizedString = LocalizedString::create(CC_CALLBACK_1(LocalizedLabel::onLocaleChange, this));

	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onLocaleChange(std::string newString)
{
	this->setString(newString);
}
