#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AddBlock : public BlockBase
{
public:
	static AddBlock* create();

private:
	typedef BlockBase super;
	AddBlock();
	~AddBlock();

	void onEnter() override;
	void initializePositions() override;
};
