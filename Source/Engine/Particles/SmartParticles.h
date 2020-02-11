#pragma once
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class SmartParticles : public GameObject
{
public:

	struct CullInfo
	{
		bool cull;
		cocos2d::Size size;

		CullInfo() : cull(false), size(cocos2d::Size::ZERO) { }
		CullInfo(cocos2d::Size size) : cull(true), size(size) { }
	};

	static SmartParticles* create(std::string particleResource, CullInfo cullInfo = CullInfo());

	cocos2d::ParticleSystem* getParticles();
	void start();
	void restart();
	void stop(float disableUpdateAfter = 0.0f);
	bool isActive();
	void accelerate(float duration);

	void setGrouped();
	void setRelative();
	void setFree();

protected:
	SmartParticles(std::string particleResource, CullInfo cullInfo);
	virtual ~SmartParticles();

	void onEnter() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void optimizationHideOffscreenParticles();

	CullInfo cullInfo;

	cocos2d::Rect boundsRect;
	cocos2d::DrawNode* debugDrawNode;
	cocos2d::ParticleSystem* particles;
};
