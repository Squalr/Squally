#include "BackgroundBase.h"

BackgroundBase::BackgroundBase(ValueMap* properties, std::string name) : SerializableLayer(properties, name, nullptr)
{
}

BackgroundBase::~BackgroundBase()
{
}

void BackgroundBase::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	this->setPosition(cameraPosition - visibleSize / 2.0f);

	SerializableLayer::visit(renderer, parentTransform, parentFlags);
}
