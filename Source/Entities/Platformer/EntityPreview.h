#pragma once

#include "Engine/Hackables/HackablePreview.h"

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

private:
	typedef HackablePreview super;

	EntityPreview(PlatformerEntity* entity);
	~EntityPreview();
	void onEnter() override;
	void initializePositions() override;

	PlatformerEntity* entityRef;
	std::string animationResource;
	float scale;

	SmartAnimationNode* previewAnimation;
};
