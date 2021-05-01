#pragma once

#include "Engine/Components/Component.h"

class WorldSound;

class BridgeBehavior : public Component
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
	typedef Component super;

	enum class AudioMode
	{
		None,
		Post,
		Pre
	};

	GameObject* object;
	std::string group;
	cocos2d::Vec2 originalPosition;
	int bridgeIndex;
	float bridgeDelta;
	float bridgeSpeed;
	AudioMode audioMode;
	WorldSound* raiseSound;

	static const float DefaultDelta;
	static const float DefaultSpeed;
	static const std::string PropertyGroup;
	static const std::string PropertyBridgeIndex;
	static const std::string PropertyDelta;
	static const std::string PropertySpeed;
	static const std::string PropertyAudioMode;
	static const std::string SaveKeyRaised;
};
