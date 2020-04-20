#pragma once
#include <string>

#include "Engine/Hackables/HackableBase.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;
class LocalizedString;

class HackActivatedAbility : public HackableBase
{
public:
	static HackActivatedAbility* create(
		std::string hackableIdentifier,
		std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int hackFlags,
		float duration,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);

	void activate();

protected:
	HackActivatedAbility(
		std::string hackableIdentifier,
		std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int hackFlags, 
		float duration,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);
	virtual ~HackActivatedAbility();
	
	void restoreState() override;

private:
	typedef HackableBase super;

	std::function<void()> onActivate;
	std::function<void()> onDeactivate;
};
