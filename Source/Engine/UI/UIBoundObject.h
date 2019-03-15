#pragma once
#include "cocos/math/Mat4.h"

#include "Engine/SmartNode.h"

class UIBoundObject : public SmartNode
{
public:
	static UIBoundObject* create(cocos2d::Node* referencedObject);

	cocos2d::Node* getObjectReference();

private:
	typedef SmartNode super;

	UIBoundObject(cocos2d::Node* referencedObject);
	~UIBoundObject();
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	cocos2d::Node* referencedObject;
};
