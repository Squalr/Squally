#pragma once
#include <string>

#include "Engine/SmartNode.h"

class Clippy;
class HackablePreview;
class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	int getRequiredHackFlag();
	float getElapsedDuration();
	float getDuration();
	bool isCooldownComplete();
	float getElapsedCooldown();
	float getCooldown();
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();
	virtual void* getPointer();
	Clippy* getClippy();

protected:
	HackableAttribute(int requiredHackFlags, float duration, float cooldown, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy = nullptr);
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
	bool isTimerPaused;
	int requiredHackFlag;
	float duration;
	float cooldown;
	float elapsedDuration;
	float elapsedCooldown;
	Clippy* clippy;
};
