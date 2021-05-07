// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_MenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WITCHCRAFT_API IC_MenuInterface
{
	GENERATED_BODY()

public:
	virtual void OnMoveUp(bool isUp) {};
	virtual void OnMoveRight(bool isRight) {};
	
	virtual void OnScrollUp(bool isUp) {};
	
	virtual void OnTabRight(bool isRight) {};

	virtual void OnPressStart() {};


};
