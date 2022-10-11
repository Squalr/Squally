#pragma once

#include "Engine/Components/GameComponent.h"

class ClickableNode;

class ObjectSelectionBehavior : public GameComponent
{
public:
	static ObjectSelectionBehavior* create(GameObject* owner);
	
	void setObjectClickCallbacks(std::function<void()> onClick, std::function<void()> onMouseOver = nullptr, std::function<void()> onMouseOut = nullptr);
	void setClickModifier(cocos2d::InputEvents::KeyCode modifier);
	void setClickableCallback(std::function<bool()> canClickCallback);
	void clearObjectClickCallbacks();
	ClickableNode* getHitbox();
	cocos2d::CSize getObjectSize() const;

	static const std::string MapKey;

protected:
	ObjectSelectionBehavior(GameObject* owner);
	virtual ~ObjectSelectionBehavior();
	
	void update(float dt) override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	ClickableNode* clickHitbox = nullptr;
	cocos2d::Vec3 savedWorldCoords;
	cocos2d::CSize objectSize;
	std::function<bool()> canClickCallback = nullptr;
};
