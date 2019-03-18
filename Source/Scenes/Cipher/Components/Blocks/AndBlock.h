#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AndBlock : public BlockBase
{
public:
	static AndBlock* create();

private:
	typedef BlockBase super;
	AndBlock();
	~AndBlock();

	void onEnter() override;
	void initializePositions() override;
};
