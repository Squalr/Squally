#pragma once
#include <string>

#include "Engine/SmartNode.h"

class HackablePreview;
class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	float getDuration();
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();

protected:
	HackableAttribute(float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview);
	virtual ~HackableAttribute();

	void onEnter() override;
	void update(float dt) override;
	void resetTimer();
	virtual void restoreState();

private:
	typedef SmartNode super;

	LocalizedString* name;
	std::string iconResource;
	HackablePreview* hackablePreview;
	float duration;
	float elapsedDuration;
};
