#include "FilterEntry.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

using namespace cocos2d;

const Size FilterEntry::LabelSize = Size(288.0f, 32.0f);

FilterEntry::FilterEntry(LocalizedString* text, std::string spriteResource)
{
	this->labelNode = this->buildMenuLabel(text, spriteResource);

	this->addChild(this->labelNode);
}

FilterEntry::~FilterEntry()
{
}

void FilterEntry::onEnter()
{
	super::onEnter();
}

void FilterEntry::initializePositions()
{
	super::initializePositions();
}

cocos2d::Node* FilterEntry::buildMenuLabel(LocalizedString* text, std::string spriteResource)
{
	Node* contentNode = Node::create();

	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);

	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->enableOutline(Color4B::BLACK, 2);
	label->setPositionX(-FilterEntry::LabelSize.width / 2.0f);

	contentNode->addChild(label);

	if (!spriteResource.empty())
	{
		Sprite* icon = Sprite::create(spriteResource);

		label->setPositionX(label->getPositionX() + 40.0f);
		contentNode->addChild(icon);

		icon->setPositionX(-FilterEntry::LabelSize.width / 2.0f + 16.0f);
	}

	return contentNode;
}
