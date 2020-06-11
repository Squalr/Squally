#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class EntityTextOverlayBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	void runHealthDelta(int delta, bool zeroAsGreen);
	void runManaDelta(int delta, bool zeroAsBlue);
	void runLabelOverEntity(LocalizedLabel* label);

	PlatformerEntity* entity;
	cocos2d::Node* contentNode;
};
