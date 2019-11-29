#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class PhysicsBody;
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class HexusPuzzleShrine : public InteractObject
{
public:
	static HexusPuzzleShrine* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHexusPuzzleShrine;

protected:
	HexusPuzzleShrine(cocos2d::ValueMap& properties);
	~HexusPuzzleShrine();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef InteractObject super;

	void runHealAnimation(bool reRun = false);

	cocos2d::Sprite* shrine;
	cocos2d::Node* floatContainer;
	cocos2d::Sprite* floatingPuzzle;
	SmartAnimationSequenceNode* healAnimation;
	WorldSound* healSound;
	
	bool isAnimating;
};
