#include "NpcBase.h"

#include "Engine/UI/Controls/MenuSprite.h"

#include "Resources/UIResources.h"

NpcBase::NpcBase(ValueMap* initProperties, std::string scmlResource, PlatformerCollisionType collisionType, Size size, float scale, Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, collisionType, size, scale, collisionOffset)
{
	this->chatBubbleSprite = Sprite::create(UIResources::Platformer_ChatBubble);

	this->interactButton = MenuSprite::create(Sprite::create(), Sprite::create());
	this->interactButton->setClickCallback(CC_CALLBACK_1(NpcBase::onInteractButtonClick, this));

	this->chatBubbleSprite->setPosition(Vec2(0.0f, 196.0f));

	this->addChild(this->chatBubbleSprite);
	this->addChild(this->interactButton);
}

NpcBase::~NpcBase()
{
}

void NpcBase::update(float dt)
{
	PlatformerEntity::update(dt);
}

void NpcBase::initializeCollisionEvents()
{
	PlatformerEntity::initializeCollisionEvents();

	this->whenCollidesWith({ (int)PlatformerCollisionType::Player, }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}

void NpcBase::onInteractButtonClick(MenuSprite* menuSprite)
{
	//// HexusEvents::startGame(HexusEvents::HexusGameEventArgs(this->deck, this->deck));
}
