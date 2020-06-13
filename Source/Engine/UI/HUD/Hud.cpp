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
	this->noHudParent = GameUtils::getFirstParentOfType<Hud>(this) == nullptr;
	this->noCameraParent = GameUtils::getFirstParentOfType<GameCamera>(this) == nullptr;
	this->renderPosition = Vec3::ZERO;
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

Vec3 Hud::getRenderPosition()
{
	return this->renderPosition;
}

void Hud::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	if (GameUtils::getFirstParentOfType<Hud>(this) == nullptr)
	{
		static Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

		this->setPosition(cameraPosition - visibleSize / 2.0f);

		if (GameUtils::getFirstParentOfType<GameCamera>(this) == nullptr)
		{
			float cameraHeight = Camera::getDefaultCamera()->getPositionZ();
			static float initialCameraHeight = Director::getInstance()->getZEye();

			this->setPositionZ(cameraHeight - initialCameraHeight);
		}
	}

	this->renderPosition = this->getPosition3D();

	super::visit(renderer, parentTransform, parentFlags);

	this->setPosition3D(Vec3::ZERO);
}
