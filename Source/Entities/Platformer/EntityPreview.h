#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class SmartAnimationNode;

class EntityPreview : public HackablePreview
{
public:
	static EntityPreview* create(PlatformerEntity* entity);

	HackablePreview* clone() override;

protected:
	EntityPreview(PlatformerEntity* entity);
	virtual ~EntityPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	PlatformerEntity* entityClone = nullptr;
	std::string animationResource;
	float scale = 0.0f;
	cocos2d::Vec2 offset = cocos2d::Vec2::ZERO;
	SmartAnimationNode* previewAnimation = nullptr;
};
