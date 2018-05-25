#include "UILayer.h"

UILayer* UILayer::create()
{
	UILayer* instance = new UILayer();

	instance->autorelease();

	return instance;
}

UILayer::UILayer()
{
}

UILayer::~UILayer()
{
}

void UILayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	this->setPosition(cameraPosition - visibleSize / 2.0f);
}
