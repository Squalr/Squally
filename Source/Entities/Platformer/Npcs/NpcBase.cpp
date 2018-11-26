#include "NpcBase.h"

NpcBase::NpcBase(ValueMap* initProperties, std::string scmlResource, CategoryName categoryName, Size size, float scale, Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, categoryName, size, scale, collisionOffset)
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

void NpcBase::initializeCardData()
{
	this->deck = nullptr;
}

bool NpcBase::contactBegin(CollisionData data)
{
	return false;
}

bool NpcBase::contactUpdate(CollisionData data)
{
	/*
	switch (data.other->getCategoryName())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		if (abs(data.normal.y) >= PlatformerEntity::normalJumpThreshold)
		{
			this->isOnGround = true;
		}

		return true;
	}
	*/
	return false;
}

bool NpcBase::contactEnd(CollisionData data)
{
	/*
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		this->isOnGround = false;
		return true;
	}
	*/

	return false;
}
