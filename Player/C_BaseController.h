// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_InputInterface.h"
#include "C_BaseController.generated.h"


UCLASS()
class WITCHCRAFT_API AC_BaseController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnActionInput(E_InputAction actionInput, bool isPress);
	UFUNCTION()
		virtual void PressKbConfirm() {};
	UFUNCTION()
		virtual void PressKbCancel() {};

	void SetCurrentInput(IC_InputInterface* newInput);

	// Menus will call this when they have full-exit. This must be overridden by all children.
	virtual void ResetCurrentInput() PURE_VIRTUAL(AC_BaseController::ResetCurrentInput, );

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	IC_InputInterface* m_CurrentInput = nullptr;

	void EvaluateMovementInput();
	// Static names for axis bindings
	static const FName m_MoveUpBinding;
	static const FName m_MoveRightBinding;

};
