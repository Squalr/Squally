#include "Hud.h"

#include "cocos/2d/CCCamera.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCRenderer.h"

using namespace cocos2d;

Hud* Hud::create()
{
	Hud* instance = new Hud();

	instance->autorelease();

	return instance;
}

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();
	float cameraHeight = Camera::getDefaultCamera()->getPositionZ();
	float initialCameraHeight = Director::getInstance()->getZEye();

	this->setPosition(cameraPosition - visibleSize / 2.0f);
	this->setPositionZ(cameraHeight - initialCameraHeight);

	SmartNode::visit(renderer, parentTransform, parentFlags);
}
