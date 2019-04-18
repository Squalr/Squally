#pragma once
#include "cocos/math/Mat4.h"

#include "Engine/SmartNode.h"

class UIBoundObject : public SmartNode
{
public:
	static UIBoundObject* create(cocos2d::Node* referencedObject);

	cocos2d::Node* getReferencedObject();
	cocos2d::Node* getOriginalParent();
	static cocos2d::Vec3 getRealCoords(UIBoundObject* uiBoundObject);
	static float getRealScale(UIBoundObject* uiBoundObject);

private:
	typedef SmartNode super;

	UIBoundObject(cocos2d::Node* referencedObject);
	~UIBoundObject();
	void onEnter() override;
	void initializeListeners() override;
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	cocos2d::Node* referencedObject;
	cocos2d::Node* originalParent;
};
