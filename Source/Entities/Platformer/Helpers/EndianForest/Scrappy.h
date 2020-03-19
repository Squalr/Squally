#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;
class SmartAnimationSequenceNode;

// Note: not classified as a helper since they do not participate in combat
class Scrappy : public PlatformerFriendly
{
public:
	static Scrappy* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKey;
	
protected:
	Scrappy(cocos2d::ValueMap& properties);
	virtual ~Scrappy();

private:
	typedef PlatformerFriendly super;

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	SmartAnimationSequenceNode* fireAnimation;
};
