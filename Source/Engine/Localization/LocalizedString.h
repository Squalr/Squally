#pragma once
#include <string>
#include <functional>

#include "Engine/SmartNode.h"

class LocalizedString : public SmartNode
{
public:
	static LocalizedString* create(std::function<void(std::string newString)> onLocaleChange);

	std::string getString();

private:
	LocalizedString(std::function<void(std::string newString)> onLocaleChange);
	~LocalizedString();

	void initializeListeners() override;

	std::string localizedString;
	std::function<void(std::string newString)> onLocaleChange;

	const std::string enString;
};
