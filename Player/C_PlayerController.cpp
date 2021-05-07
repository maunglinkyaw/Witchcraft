// Lin & Yin's Witchcraft 2020


#include "C_PlayerController.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "GM_Witchcraft.h"
#include "Witchcraft.h"
#include "C_PlayerPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "UI/Gameplay/CUI_Gameplay.h"


AC_PlayerController::AC_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bAutoManageActiveCameraTarget = false;

	//SetInputMode(FInputModeGameAndUI());
}

void AC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_GameMode = GetWorld()->GetAuthGameMode<AGM_Witchcraft>();
	UE_LOG(LogSystem, Display, TEXT("%s - BeginPlay - m_GameMode: %s"), *GetName(), *GetNameSafe(m_GameMode));

	if (m_GameMode)
	{
		m_GameplayUI = m_GameMode->GetGameplayUI();
	}
	
	if (m_GameplayUI)
	{
		m_GameplayUI->m_Controller = this;
	}

	m_Pawn = Cast<AC_PlayerPawn>(GetPawn());

	if (m_Pawn)
	{
		SetViewTarget(m_Pawn);
	}
}

void AC_PlayerController::InitGameplayUI()
{
	if (m_GameplayUI)
	{

	}
}

void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	EvaluateMovementInput(DeltaTime);

}

void AC_PlayerController::GoToGameplayMenu(E_MenuPage menuPage)
{
	if (m_GameplayUI)
	{
		m_GameplayUI->GoToMenuPage(menuPage);
	}
}

void AC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MoveUp", IE_Pressed, this, &AC_PlayerController::OnPressUp);
	InputComponent->BindAction("MoveUp", IE_Released, this, &AC_PlayerController::OnReleaseUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &AC_PlayerController::OnPressDown);
	InputComponent->BindAction("MoveDown", IE_Released, this, &AC_PlayerController::OnReleaseDown);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &AC_PlayerController::OnPressRight);
	InputComponent->BindAction("MoveRight", IE_Released, this, &AC_PlayerController::OnReleaseRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AC_PlayerController::OnPressLeft);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &AC_PlayerController::OnReleaseLeft);

	InputComponent->BindAction("ConfirmAction", IE_Pressed, this, &AC_PlayerController::ConfirmAction);
	InputComponent->BindAction("CancelAction", IE_Pressed, this, &AC_PlayerController::CancelAction);
	InputComponent->BindAction("StartButton", IE_Pressed, this, &AC_PlayerController::StartButton);
	InputComponent->BindAction("EscapeButton", IE_Pressed, this, &AC_PlayerController::EscapeButton);
	
	InputComponent->BindAction("RosterMenu", IE_Pressed, this, &AC_PlayerController::RosterMenuButton);
	InputComponent->BindAction("CovenMenu", IE_Pressed, this, &AC_PlayerController::CovenMenuButton);

	InputComponent->BindAxis("MoveVertical", this, &AC_PlayerController::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &AC_PlayerController::MoveHorizontal);
	InputComponent->BindAxis("ZoomIn", this, &AC_PlayerController::ZoomIn);
}

void AC_PlayerController::EvaluateMovementInput(float deltaTime)
{
	if (m_IsPressingUp) MoveVertical(1.f);
	else if (m_IsPressingDown) MoveVertical(-1.f);
	
	if (m_IsPressingRight) MoveHorizontal(1.f);
	else if (m_IsPressingLeft) MoveHorizontal(-1.f);

}

void AC_PlayerController::OnPressUp()
{
	m_IsPressingUp = true;
}
void AC_PlayerController::OnReleaseUp()
{
	m_IsPressingUp = false;
}

void AC_PlayerController::OnPressDown()
{
	m_IsPressingDown = true;

}
void AC_PlayerController::OnReleaseDown()
{
	m_IsPressingDown = false;

}

void AC_PlayerController::OnPressRight()
{
	m_IsPressingRight = true;

}
void AC_PlayerController::OnReleaseRight()
{
	m_IsPressingRight = false;

}

void AC_PlayerController::OnPressLeft()
{
	m_IsPressingLeft = true;

}
void AC_PlayerController::OnReleaseLeft()
{
	m_IsPressingLeft = false;

}


void AC_PlayerController::RosterMenuButton()
{
	if (m_GameplayUI)
	{
		m_GameplayUI->ShortcutToPage(E_MenuPage::ROSTER_MENU);
	}
}

void AC_PlayerController::CovenMenuButton()
{

}

void AC_PlayerController::ConfirmAction()
{

}

void AC_PlayerController::CancelAction()
{

}

void AC_PlayerController::StartButton()
{

}

void AC_PlayerController::EscapeButton()
{

}

void AC_PlayerController::MoveVertical(float value)
{
	if (value > 0.f)
	{
		if (m_Pawn->GetActorLocation().X < (m_MaxX))// + m_XOffset))
		{
			m_Pawn->m_MovementComp->AddInputVector(FVector(1.f, 0.f, 0.f) * value);
		}
	}
	else if (value < 0.f)
	{
		if (m_Pawn->GetActorLocation().X > - (m_MaxX - m_XBottomOffset))
			m_Pawn->m_MovementComp->AddInputVector(FVector(1.f, 0.f, 0.f) * value);
	}
}

void AC_PlayerController::MoveHorizontal(float value)
{
	if (value > 0.f)
	{
		if (m_Pawn->GetActorLocation().Y < m_MaxY)
			m_Pawn->m_MovementComp->AddInputVector(FVector(0.f, 1.f, 0.f) * value);
	}
	else if (value < 0.f)
	{
		if (m_Pawn->GetActorLocation().Y > -m_MaxY)
			m_Pawn->m_MovementComp->AddInputVector(FVector(0.f, 1.f, 0.f) * value);
	}

}

void AC_PlayerController::ZoomIn(float value)
{

}
