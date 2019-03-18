#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ImmediateBlock : public BlockBase
{
public:
	static ImmediateBlock* create();

private:
	typedef BlockBase super;
	ImmediateBlock();
	~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
};
