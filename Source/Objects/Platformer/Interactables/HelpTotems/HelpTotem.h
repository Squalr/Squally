#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class CollisionObject;
class SpeechBubble;
class LocalizedLabel;
class LocalizedString;

class HelpTotem : public GameObject
{
public:
	static HelpTotem* create(cocos2d::ValueMap& properties);

protected:
	HelpTotem(cocos2d::ValueMap& properties);
	~HelpTotem();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void setHint(LocalizedString* hint);

private:
	typedef GameObject super;
	
	cocos2d::Sprite* totem;
	CollisionObject* hintCollision;
	SpeechBubble* speechBubble;
	LocalizedString* hint;
};
