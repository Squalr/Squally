#include "BackgroundBase.h"

BackgroundBase::BackgroundBase(ValueMap* properties, std::string name) : SerializableLayer(properties, name, nullptr)
{
}

BackgroundBase::~BackgroundBase()
{
}

void BackgroundBase::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	this->setPosition(cameraPosition - visibleSize / 2.0f);
}
