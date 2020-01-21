#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class SpeechBubble;
class LocalizedLabel;
class LocalizedString;

class HelpTotem : public InteractObject
{
public:
	static HelpTotem* create(cocos2d::ValueMap& properties);

	void deactivate();
	void activate();

protected:
	HelpTotem(cocos2d::ValueMap& properties);
	~HelpTotem();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract() override;
	void onEndCollision() override;
	void setHint(LocalizedString* hint);

private:
	typedef InteractObject super;

	void tryDisplayHint();
	
	bool isInactive;

	cocos2d::Sprite* totem;
	cocos2d::Sprite* totemInactive;
	SpeechBubble* speechBubble;
	LocalizedString* hint;
};
