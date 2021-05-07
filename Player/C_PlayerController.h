// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "E_CommonEnums.h"
#include "C_PlayerController.generated.h"

class UCUI_Menu;
class UCUI_Gameplay;

UCLASS()
class WITCHCRAFT_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AC_PlayerController();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	class AC_PlayerPawn* m_Pawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float m_MaxX = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float m_MaxY = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float m_XBottomOffset = 500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	bool m_IsPressingUp = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	bool m_IsPressingDown = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	bool m_IsPressingRight = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	bool m_IsPressingLeft = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	UCUI_Menu* m_ActiveMenu = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UCUI_Gameplay* m_GameplayUI = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Managers")
	class AGM_Witchcraft* m_GameMode = nullptr;

	void GoToGameplayMenu(E_MenuPage menuPage);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void InitGameplayUI();

	void EvaluateMovementInput(float deltaTime);

	UFUNCTION()
	void ConfirmAction();
	UFUNCTION()
	void CancelAction();
	UFUNCTION()
	void StartButton();
	UFUNCTION()
	void EscapeButton();
	UFUNCTION()
	void OnPressUp();
	UFUNCTION()
	void OnReleaseUp();
	UFUNCTION()
	void OnPressDown();
	UFUNCTION()
	void OnReleaseDown();
	UFUNCTION()
	void OnPressRight();
	UFUNCTION()
	void OnReleaseRight();
	UFUNCTION()
	void OnPressLeft();
	UFUNCTION()
	void OnReleaseLeft();

	UFUNCTION()
	void RosterMenuButton();
	UFUNCTION()
	void CovenMenuButton();

	UFUNCTION()
	void MoveVertical(float value);
	UFUNCTION()
	void MoveHorizontal(float value);
	UFUNCTION()
	void ZoomIn(float value);


};
