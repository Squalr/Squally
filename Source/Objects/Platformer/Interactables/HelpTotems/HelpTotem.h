#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class SpeechBubble;
class LocalizedString;

class HelpTotem : public InteractObject
{
public:
	static HelpTotem* create(cocos2d::ValueMap& properties);

	void deactivate(bool instant = false);
	void activate();

protected:
	HelpTotem(cocos2d::ValueMap& properties);
	virtual ~HelpTotem();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;
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
