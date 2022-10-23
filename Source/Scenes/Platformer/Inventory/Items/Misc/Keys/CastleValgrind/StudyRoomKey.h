#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class StudyRoomKey : public Key
{
public:
	static StudyRoomKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	StudyRoomKey();
	virtual ~StudyRoomKey();

private:
	typedef Key super;
};
