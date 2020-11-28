#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

template <class T>
class LazyNode;

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap& properties);

protected:
	PlatformerDecorObject(cocos2d::ValueMap& properties);
	virtual ~PlatformerDecorObject();

	void onEnter() override;
	void update(float dt) override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	
private:
	typedef HackableObject super;

	void runBounce();
	void optimizationHideOffscreenDecor();
	cocos2d::Sprite* buildSprite();
	
	std::string filePath;
	cocos2d::Size objectSize;
	LazyNode<cocos2d::Sprite>* sprite;
};
