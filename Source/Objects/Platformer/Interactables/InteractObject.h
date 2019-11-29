#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;

class InteractObject : public HackableObject
{
public:
	void enable();
	void disable();
	void setRequiresInteraction(bool requiresInteraction);
	void setOpenCallback(std::function<bool()> openCallback);

protected:
	enum class InteractType
	{
		None,
		Input,
		Collision,
	};

	InteractObject(cocos2d::ValueMap& properties, InteractType interactType, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	~InteractObject();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void updateInteractMenuVisibility();
	void tryInteractObject();
	virtual void onInteract();

	InteractType interactType;
	CollisionObject* interactCollision;

private:
	typedef HackableObject super;

	InteractMenu* interactMenu;

	bool requiresInteraction;
	bool disabled;
	bool canInteract;
	bool wasTripped;
	std::function<bool()> interactCallback;
};
