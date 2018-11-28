#include "Background.h"

Background* Background::create(ValueMap* initProperties, std::string name, Node* child)
{
	Background* instance = new Background(initProperties, name, child);

	instance->autorelease();

	return instance;
}

Background::Background(ValueMap* properties, std::string name, Node* child) : SerializableLayer(properties, name)
{
	this->addChild(child);
}

Background::~Background()
{
}

void Background::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = Camera::getDefaultCamera()->getPosition();

	this->setPosition(cameraPosition);

	SerializableLayer::visit(renderer, parentTransform, parentFlags);
}
