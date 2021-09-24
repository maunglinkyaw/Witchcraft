// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_InputInterface.generated.h"

UENUM(BlueprintType)
enum class E_InputAction : uint8
{
	NoInput = 0		UMETA(DisplayName = "No Input"),
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_InputInterface : public UInterface
{
	GENERATED_BODY()
};

class WITCHCRAFT_API IC_InputInterface
{
	GENERATED_BODY() 

public:
	virtual void OnInputAction(E_InputAction inInput, bool isPress) {};

	virtual void OnMoveUp(float value) {};
	virtual void OnMoveRight(float value) {};

	virtual void OnPressConfirm() {};
	virtual void OnPressCancel() {};

	// OLD

	virtual void OnMoveUp(bool isUp) {};
	virtual void OnMoveRight(bool isRight) {};
	
	virtual void OnScrollUp(bool isUp) {};
	
	virtual void OnTabRight(bool isRight) {};

	virtual void OnPressStart() {};


};
