#pragma once

#include "Engine/Components/Component.h"

class Item;
class LocalizedString;
class Squally;

class SquallyReceiveItemBehavior : public Component
{
public:
	static SquallyReceiveItemBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyReceiveItemBehavior(GameObject* owner);
	virtual ~SquallyReceiveItemBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void obtainItems(const std::vector<Item*>& items, LocalizedString* messageOverride, bool keepOpen);

	Squally* squally;
};
