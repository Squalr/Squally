#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Portal;

class BridgeBehavior : public AttachedBehavior
{
public:
	static BridgeBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BridgeBehavior(GameObject* owner);
	virtual ~BridgeBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	GameObject* object;
	std::string group;
	cocos2d::Vec2 originalPosition;
	int bridgeIndex;

	static const std::string PropertyGroup;
	static const std::string PropertyBridgeIndex;
	static const std::string SaveKeyRaised;
};
