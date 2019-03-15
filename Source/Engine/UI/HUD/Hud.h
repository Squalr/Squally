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

protected:
	Hud();
	virtual ~Hud();
	void visit(cocos2d::Renderer* renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef SmartNode super;	
};
