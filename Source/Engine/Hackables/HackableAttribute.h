#pragma once
#include <string>

#include "Engine/SmartNode.h"

class Clippy;
class HackablePreview;
class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	int getRequiredEq();
	float getElapsedDuration();
	float getDuration();
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();
	virtual void* getPointer();
	Clippy* getClippy();

protected:
	HackableAttribute(int requiredEq, float duration, std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview, Clippy* clippy = nullptr);
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
	int requiredEq;
	float duration;
	float elapsedDuration;
	Clippy* clippy;
};
