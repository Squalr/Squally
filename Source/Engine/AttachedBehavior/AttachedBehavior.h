#pragma once

#include "Engine/Maps/GameObject.h"

class AttachedBehavior : public GameObject
{
public:
	std::string getAttachedBehaviorArgs();

protected:
	AttachedBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~AttachedBehavior();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;

private:
	typedef GameObject super;
	
	void updateState();

	GameObject* owner;
	std::string attachedBehaviorArgs;
};

