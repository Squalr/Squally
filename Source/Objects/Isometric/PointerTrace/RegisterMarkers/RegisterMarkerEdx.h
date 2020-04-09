#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEdx : public RegisterMarker
{
public:
	static RegisterMarkerEdx* create();

protected:
	RegisterMarkerEdx();
	virtual ~RegisterMarkerEdx();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
