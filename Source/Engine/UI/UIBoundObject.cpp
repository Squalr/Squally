#include "UIBoundObject.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

UIBoundObject* UIBoundObject::create(cocos2d::Node* referencedObject)
{
    UIBoundObject* instance = new UIBoundObject(referencedObject);

    instance->autorelease();

    return instance;
}

UIBoundObject::UIBoundObject(cocos2d::Node* referencedObject)
{
    this->referencedObject = referencedObject;

    this->setPosition3D(this->referencedObject->getPosition3D());
}

UIBoundObject::~UIBoundObject()
{
}

Node* UIBoundObject::getObjectReference()
{
    return this->referencedObject;
}

void UIBoundObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    this->referencedObject->setPosition3D(GameUtils::getWorldCoords3D(this));

	super::visit(renderer, parentTransform, parentFlags);
}