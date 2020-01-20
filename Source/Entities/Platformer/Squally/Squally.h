#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class Squally : public PlatformerFriendly
{
public:
	static Squally* create();
	static Squally* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;
	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	std::string getSwimAnimation() override;

	static const std::string MapKeySqually;
	static const std::string BattleTag;

protected:

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	
	Squally(cocos2d::ValueMap& properties);
	~Squally();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onHackerModeEnable(int hackFlags) override;

	static const float SquallyScale;
};
