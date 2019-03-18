#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ModBlock : public BlockBase
{
public:
	static ModBlock* create();

private:
	typedef BlockBase super;
	ModBlock();
	~ModBlock();

	void onEnter() override;
	void initializePositions() override;
};
