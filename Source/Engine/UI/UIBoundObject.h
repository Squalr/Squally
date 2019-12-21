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

protected:
	void onEnter() override;
	void initializeListeners() override;
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef SmartNode super;

	UIBoundObject(cocos2d::Node* referencedObject);
	~UIBoundObject();
	void scheduleUpdateTask();

	cocos2d::Node* referencedObject;
	SmartNode* originalParent;
	cocos2d::Node* scheduleTarget;

    cocos2d::Vec3 originalCoords;
    float originalScale;
    cocos2d::Vec3 realCoords;
    float realScale;
	std::string eventKey;
};
