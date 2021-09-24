// Lin & Yin 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Witchcraft/Player/C_InputInterface.h"
#include "CUI_MasterMenu.generated.h"

UENUM(Blueprintable)
enum class E_GameMenu : uint8
{
	NO_MENU = 0			UMETA(DisplayName = "No Menu"),
	PAUSE_MENU			UMETA(DisplayName = "Pause Menu"),
	DIALOGUE_MENU		UMETA(DisplayName = "Dialogue"),
	CHARACTER_MENU		UMETA(DisplayName = "Character Menu"),
	INVENTORY_MENU		UMETA(DisplayName = "Inventory Menu"),
};

class UCUI_Menu;

/**
 * This is the main UI that will hold the other widgets.
 * It is not a menu per se, more of a unified UI container.
 */
UCLASS()
class WITCHCRAFT_API UCUI_MasterMenu : public UUserWidget, public IC_InputInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class AC_BaseController* m_Controller = nullptr;
	// Active Menu is a major menu, like Inventory or Dialogue, that is currently in focus and accepting input.
	// Only 1 Active Menu will be shown at 1 time.
	UPROPERTY()
	UCUI_Menu* m_ActiveMenu = nullptr;
	// Override Menu does not hide or swap an Active Menu if there is one showing, but it will always appear on top.
	// Meant for small mini-menus like Confirmations and Warnings.
	UPROPERTY()
	UCUI_Menu* m_OverrideMenu = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NaviMenu|Setup")
	TMap<FName, UCUI_Menu*> m_MenuMap;

public:
	void ShowMenu(FName menuName);
	void ShowOverrideMenu(FName menuName);

	UFUNCTION(BlueprintImplementableEvent)
	UCUI_Menu* BlueprintShowMenu(FName menuName);
	UFUNCTION(BlueprintImplementableEvent)
	UCUI_Menu* BlueprintShowOverrideMenu(FName menuName);


	// Input Interface Overrides
	virtual void OnMoveUp(float value) override;
	virtual void OnMoveRight(float value) override;

	virtual void OnPressConfirm() override;
	virtual void OnPressCancel() override;

};
