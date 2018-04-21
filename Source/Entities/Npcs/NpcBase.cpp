#include "NpcBase.h"

NpcBase::NpcBase(std::string scmlResource, std::string entityName, bool isFlying, Size size, float scale, Vec2 collisionOffset)
	: Entity::Entity(scmlResource, entityName, isFlying, size, scale, collisionOffset)
{
	this->interactButton = MenuSprite::create(Resources::Menus_Buttons_ChatButton, Resources::Menus_Buttons_ChatButtonHover, Resources::Menus_Buttons_ChatButtonClick);
	this->interactButton->setClickCallback(CC_CALLBACK_1(NpcBase::onInteractButtonClick, this));

	this->interactButton->setPosition(Vec2(this->interactButton->getContentSize().width / 4.0f, 196.0f));

	this->addChild(this->interactButton);

	this->initializeCardData();
}

NpcBase::~NpcBase()
{
}

void NpcBase::update(float dt)
{
	Entity::update(dt);
}

void NpcBase::onInteractButtonClick(MenuSprite* menuSprite)
{
	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->deck, this->deck));
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
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		if (abs(data.normal.y) >= Entity::normalJumpThreshold)
		{
			this->isOnGround = true;
		}

		return true;
	}

	return false;
}

bool NpcBase::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		this->isOnGround = false;
		return true;
	}

	return false;
}
