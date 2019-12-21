#pragma once
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class ParticleObject : public GameObject
{
public:
	static ParticleObject* create(std::string particleResource, cocos2d::Size size);

	cocos2d::ParticleSystem* getParticles();

protected:
	ParticleObject(std::string particleResource, cocos2d::Size size);
	~ParticleObject();

	void onEnter() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void optimizationHideOffscreenParticles();

	cocos2d::Rect boundsRect;
	cocos2d::ParticleSystem* particles;
	cocos2d::DrawNode* debugDrawNode;
};
