#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEcx : public RegisterMarker
{
public:
	static RegisterMarkerEcx* create();

protected:
	RegisterMarkerEcx();
	virtual ~RegisterMarkerEcx();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
