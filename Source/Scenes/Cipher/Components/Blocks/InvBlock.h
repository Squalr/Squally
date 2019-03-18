#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class InvBlock : public BlockBase
{
public:
	static InvBlock* create();

private:
	typedef BlockBase super;
	InvBlock();
	~InvBlock();

	void onEnter() override;
	void initializePositions() override;
};
