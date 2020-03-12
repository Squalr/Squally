#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class EntityTextOverlayBehavior : public AttachedBehavior
{
public:
	static EntityTextOverlayBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityTextOverlayBehavior(GameObject* owner);
	virtual ~EntityTextOverlayBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void runDelta(int delta, bool zeroAsGreen);
	void runLabelOverEntity(LocalizedLabel* label);

	PlatformerEntity* entity;
	cocos2d::Node* contentNode;
};
