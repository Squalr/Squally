#pragma once

#include "Engine/Components/GameComponent.h"

class WorldSound;

class BridgeBehavior : public GameComponent
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
	typedef GameComponent super;

	void raiseBridge(bool playAnims, bool playAudio);

	enum class AudioMode
	{
		None,
		Post,
		Pre
	};

	GameObject* object = nullptr;
	std::string group;
	cocos2d::Vec2 originalPosition;
	int bridgeIndex = 0;
	float bridgeDelta = 0.0f;
	float bridgeSpeed = 0.0f;
	AudioMode audioMode = AudioMode::None;
	WorldSound* raiseSound = nullptr;

	static const float DefaultDelta;
	static const float DefaultSpeed;
	static const std::string PropertyGroup;
	static const std::string PropertyBridgeIndex;
	static const std::string PropertyDelta;
	static const std::string PropertySpeed;
	static const std::string PropertyAudioMode;
	static const std::string PropertyInitRaised;
	static const std::string SaveKeyRaised;
};
