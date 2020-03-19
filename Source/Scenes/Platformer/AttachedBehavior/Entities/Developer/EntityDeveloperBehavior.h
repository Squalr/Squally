#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"
 
class ClickableNode;
class PlatformerEntity;

class EntityDeveloperBehavior : public AttachedBehavior
{
public:
	static EntityDeveloperBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityDeveloperBehavior(GameObject* owner);
	virtual ~EntityDeveloperBehavior();

	void initializePositions() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	
	ClickableNode* resurrectButton;
	ClickableNode* halfHealthButton;
	ClickableNode* killButton;
};
