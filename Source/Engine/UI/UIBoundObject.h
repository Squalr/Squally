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
	void pushRealPosition();
	void popRealPosition();

protected:
	UIBoundObject(cocos2d::Node* referencedObject);
	virtual ~UIBoundObject();

	void onEnter() override;
	void initializeListeners() override;
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef SmartNode super;

	void scheduleUpdateTask();

	cocos2d::Node* referencedObject = nullptr;
	SmartNode* originalParent = nullptr;
	cocos2d::Node* scheduleTarget = nullptr;

    cocos2d::Vec3 originalCoords;
    float originalScale = 1.0f;
    cocos2d::Vec3 realCoords;
    float realScale = 1.0f;
	std::string eventKey;

	static unsigned long long TaskId;
};
