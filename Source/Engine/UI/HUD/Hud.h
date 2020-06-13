#pragma once
#include "cocos/math/Mat4.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Renderer;
}

class Hud : public SmartNode
{
public:
	static Hud* create();

	cocos2d::Vec3 getRenderPosition();

protected:
	Hud();
	virtual ~Hud();
	void onEnter() override;
	void update(float dt) override;
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef SmartNode super;

	bool noHudParent;
	bool noCameraParent;

	cocos2d::Vec3 renderPosition;
};
