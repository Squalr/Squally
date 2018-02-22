#include "NpcBase.h"

NpcBase::NpcBase() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->interactButton = MenuSprite::create(Resources::Menus_Buttons_ChatButton, Resources::Menus_Buttons_ChatButtonHover, Resources::Menus_Buttons_ChatButtonClick);
	this->interactButton->setClickCallback(CC_CALLBACK_1(NpcBase::onInteractButtonClick, this));

	this->interactButton->setPosition(Vec2(this->interactButton->getContentSize().width / 4.0f, 196.0f));

	this->addChild(this->interactButton);
}

NpcBase::~NpcBase()
{
}

void NpcBase::update(float dt)
{
	Entity::update(dt);
}

void NpcBase::onInteractButtonClick(MenuSprite* menuSprite) {

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
