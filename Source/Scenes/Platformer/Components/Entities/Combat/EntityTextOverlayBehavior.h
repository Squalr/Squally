#pragma once

#include "Engine/Components/GameComponent.h"

class LocalizedLabel;
class PlatformerEntity;

class EntityTextOverlayBehavior : public GameComponent
{
public:
	static EntityTextOverlayBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityTextOverlayBehavior(GameObject* owner);
	virtual ~EntityTextOverlayBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void runHealthDelta(int delta, bool zeroAsGreen, bool overflowMin, bool overflowMax);
	void runManaDelta(int delta, bool zeroAsBlue, bool overflowMin, bool overflowMax);
	void runLabelOverEntity(LocalizedLabel* label);

	PlatformerEntity* entity = nullptr;
	cocos2d::Node* contentNode = nullptr;
};
