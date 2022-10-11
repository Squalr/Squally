#pragma once

#include "Engine/Components/GameComponent.h"
 
class ClickableNode;
class PlatformerEntity;

class EntityDeveloperBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	
	ClickableNode* resurrectButton = nullptr;
	ClickableNode* halfHealthButton = nullptr;
	ClickableNode* killButton = nullptr;
};
