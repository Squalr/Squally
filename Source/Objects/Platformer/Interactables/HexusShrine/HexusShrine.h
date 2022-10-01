#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartParticles;

class HexusShrine : public InteractObject
{
public:
	static HexusShrine* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HexusShrine(cocos2d::ValueMap& properties);
	virtual ~HexusShrine();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	void refreshPuzzleState();

	cocos2d::Sprite* shrine = nullptr;
	cocos2d::Node* iconNode = nullptr;
	cocos2d::Node* undefeatedContainer = nullptr;
	cocos2d::Node* defeatedContainer = nullptr;

	SmartParticles* hackParticles1 = nullptr;
	SmartParticles* hackParticles2 = nullptr;
	SmartParticles* hackParticles3 = nullptr;
	SmartParticles* hackParticles4 = nullptr;
	SmartParticles* hackParticles5 = nullptr;

	PlatformerEntity* entity = nullptr;
	std::string entityTag;

	static const std::string PropertyEntityTag;
};
