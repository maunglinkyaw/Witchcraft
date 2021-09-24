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
		SetCurrentInput(m_Pawn);
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

	InputComponent->BindAction("ConfirmAction", IE_Pressed, this, &AC_PlayerController::ConfirmAction);
	InputComponent->BindAction("CancelAction", IE_Pressed, this, &AC_PlayerController::CancelAction);
	InputComponent->BindAction("StartButton", IE_Pressed, this, &AC_PlayerController::StartButton);
	InputComponent->BindAction("EscapeButton", IE_Pressed, this, &AC_PlayerController::EscapeButton);
	
	InputComponent->BindAction("RosterMenu", IE_Pressed, this, &AC_PlayerController::RosterMenuButton);
	InputComponent->BindAction("CovenMenu", IE_Pressed, this, &AC_PlayerController::CovenMenuButton);

	InputComponent->BindAxis("ZoomIn", this, &AC_PlayerController::ZoomIn);
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

void AC_PlayerController::ZoomIn(float value)
{

}
