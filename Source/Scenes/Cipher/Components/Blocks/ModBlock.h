#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ModBlock : public BlockBase
{
public:
	static ModBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ModBlock(bool isToolBoxItem);
	~ModBlock();

	void onEnter() override;
	void initializePositions() override;
};
