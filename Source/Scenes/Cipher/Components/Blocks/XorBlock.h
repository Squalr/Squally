#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class XorBlock : public BlockBase
{
public:
	static XorBlock* create();

private:
	typedef BlockBase super;
	XorBlock();
	~XorBlock();

	void onEnter() override;
	void initializePositions() override;
};
