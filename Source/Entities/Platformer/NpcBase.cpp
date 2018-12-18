#include "NpcBase.h"

#include "Engine/UI/Controls/MenuSprite.h"

#include "Resources/UIResources.h"

NpcBase::NpcBase(ValueMap* initProperties, std::string scmlResource, PlatformerCollisionType collisionType, Size size, float scale, Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, collisionType, size, scale, collisionOffset)
{
	this->interactButton = MenuSprite::create(UIResources::Menus_Buttons_ChatButton, UIResources::Menus_Buttons_ChatButtonHover);
	this->interactButton->setClickCallback(CC_CALLBACK_1(NpcBase::onInteractButtonClick, this));

	this->interactButton->setPosition(Vec2(0.0f, 196.0f));

	this->addChild(this->interactButton);

	this->initializeCardData();
}

NpcBase::~NpcBase()
{
}

void NpcBase::update(float dt)
{
	PlatformerEntity::update(dt);
}

void NpcBase::onInteractButtonClick(MenuSprite* menuSprite)
{
	//// HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->deck, this->deck));
}
