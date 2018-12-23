#include "LocalizedLabel.h"

#include "Engine/Localization/LocalizedString.h"

LocalizedLabel* LocalizedLabel::create(LocalizedString* localizedString)
{
	LocalizedLabel* label = new LocalizedLabel(localizedString);

	label->autorelease();

	return label;
}

LocalizedLabel::LocalizedLabel(LocalizedString* localizedString)
{
	this->localizedString = localizedString;
	this->addChild(this->localizedString); // Just adding this to retain it -- this has no visuals
}

LocalizedLabel::~LocalizedLabel()
{
}

void LocalizedLabel::onLocaleChange(std::string newString)
{
	this->setString(newString);
}
