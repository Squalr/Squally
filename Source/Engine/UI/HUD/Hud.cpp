#include "Hud.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCRenderer.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

Hud* Hud::create()
{
	Hud* instance = new Hud();

	instance->autorelease();

	return instance;
}

Hud::Hud()
{
	this->noHudParent = GameUtils::GetFirstParentOfType<Hud>(this) == nullptr;
	this->noCameraParent = GameUtils::GetFirstParentOfType<GameCamera>(this) == nullptr;
}

Hud::~Hud()
{
}

void Hud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Hud::update(float dt)
{
	super::update(dt);
}

void Hud::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	if (GameUtils::GetFirstParentOfType<Hud>(this) == nullptr)
	{
		static Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

		this->setPosition(cameraPosition - visibleSize / 2.0f);

		if (GameUtils::GetFirstParentOfType<GameCamera>(this) == nullptr)
		{
			float cameraHeight = Camera::getDefaultCamera()->getPositionZ();
			static float initialCameraHeight = Director::getInstance()->getZEye();

			this->setPositionZ(cameraHeight - initialCameraHeight);
		}
	}

	super::visit(renderer, parentTransform, parentFlags);
}
