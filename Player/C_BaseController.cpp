// Lin & Yin's Witchcraft 2020


#include "C_BaseController.h"

#include "Witchcraft/Player/C_InputInterface.h"

#include "Witchcraft/Witchcraft.h"

const FName AC_BaseController::m_MoveUpBinding("MoveUp");
const FName AC_BaseController::m_MoveRightBinding("MoveRight");

void AC_BaseController::SetCurrentInput(IC_InputInterface* newInput)
{
	m_CurrentInput = newInput;
}

void AC_BaseController::BeginPlay()
{
	Super::BeginPlay();
}

void AC_BaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("KbConfirm", IE_Pressed, this, &AC_BaseController::PressKbConfirm);
	InputComponent->BindAction("KbCancel", IE_Pressed, this, &AC_BaseController::PressKbCancel);

// 	BindAxis("MoveUp", this, &AC_BaseController::OnMoveUp).bExecuteWhenPaused = true;
// 	BindAxis("MoveRight", this, &AC_BaseController::OnMoveRight).bExecuteWhenPaused = true;

	InputComponent->BindAxis(m_MoveUpBinding);
	InputComponent->BindAxis(m_MoveRightBinding);
}

void AC_BaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_CurrentInput)
		EvaluateMovementInput();
}

void AC_BaseController::OnActionInput(E_InputAction actionInput, bool isPress)
{
	switch (actionInput)
	{
	case E_InputAction::NoInput:

		break;

	}
}

void AC_BaseController::EvaluateMovementInput()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, FString::Printf(TEXT("%s - EvaluateMovementInput"), *GetName()));

	if (m_CurrentInput)
	{
		// Find movement direction
		const float upValue = GetInputAxisValue(m_MoveUpBinding);
		const float rightValue = GetInputAxisValue(m_MoveRightBinding);
		m_CurrentInput->OnMoveUp(upValue);
		m_CurrentInput->OnMoveRight(rightValue);

		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, FString::Printf(TEXT("%s - EvaluateMovementInput - upValue: %f, rightValue: %f"), *GetName(), upValue, rightValue));

		// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
		//const FVector moveDirection = FVector(upValue, rightValue, 0.f).GetClampedToMaxSize(1.0f);
	}
}
