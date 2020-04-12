#pragma once
#include <string>

#include "Engine/SmartNode.h"

class Clippy;
class HackablePreview;
class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	enum class HackBarColor
	{
		Blue,
		Gray,
		Green,
		Orange,
		Pink,
		Purple,
		Red,
		Teal,
		Yellow
	};

	std::string getHackableIdentifier();
	int getRequiredHackFlag();
	float getElapsedDuration();
	float getDuration();
	bool isComplete();
	bool isCooldownComplete();
	float getElapsedCooldown();
	float getCooldown();
	std::string getHackBarResource();
	HackBarColor getHackBarColor();
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();
	virtual void* getPointer();
	Clippy* getClippy();
	virtual void restoreState();
	void restoreStateIfUnique();

protected:
	friend class SmartScene;

	HackableAttribute(
		std::string hackableIdentifier,
		int requiredHackFlags,
		float duration,
		float cooldown,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr
	);
	virtual ~HackableAttribute();

	void onEnter() override;
	void initializeListeners() override;
	void resetTimer();
	static void UpdateSharedState(float dt);
	static void CleanUpGlobalState();

	static bool HackTimersPaused;

private:
	typedef SmartNode super;

	struct SharedState
	{
		float duration;
		float cooldown;
		float elapsedDuration;
		float elapsedCooldown;

		SharedState() : duration(0.0f), cooldown(0.0f), elapsedDuration(0.0f), elapsedCooldown(0.0f) { }
		SharedState(float duration, float cooldown) : duration(duration), cooldown(cooldown), elapsedDuration(duration), elapsedCooldown(duration) { }
	};

	SharedState* getSharedState();

	static void TryRegisterSharedState(HackableAttribute* attribute, SharedState sharedState);

	std::string hackableIdentifier;
	LocalizedString* name;
	HackBarColor hackBarColor;
	std::string iconResource;
	HackablePreview* hackablePreview;
	int requiredHackFlag;
	Clippy* clippy;

	static std::map<std::string, SharedState> SharedStateMap;
};
