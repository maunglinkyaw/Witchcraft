// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "E_CommonEnums.h"
#include "CUI_Gameplay.generated.h"

class UCUI_Menu;

UCLASS()
class WITCHCRAFT_API UCUI_Gameplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCUI_Calendar* CalendarUI;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCUI_RegionMenu* RegionMenu;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCUI_RosterMenu* RosterMenu;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCUI_WitchDetails* WitchDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TMap<E_MenuPage, UCUI_Menu*> m_MenuMap;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Debug")
	class AGM_Witchcraft* m_GameMode = nullptr;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Debug")
	class AC_PlayerController* m_Controller = nullptr;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Debug")
	TArray<UCUI_Menu*> m_MenuLayers;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Debug")
	int32 m_CurrentLayer = 0;
	UPROPERTY()
	UCUI_Menu* m_CurrentMenu = nullptr;

	virtual void NativeConstruct() override;

	// GoToMenuPage leaves a history trail, allowing you to use GoBackMenuPage().
	// @purgeHistory will clean the history trail and restart the navigation.
	UFUNCTION(BlueprintCallable)
	void GoToMenuPage(E_MenuPage menuPage, bool purgeHistory = false);
	UFUNCTION(BlueprintCallable)
	void GoBackMenuPage();

	// Shortcut to Page is for when the shortcut key is used.
	UFUNCTION(BlueprintCallable)
	void ShortcutToPage(E_MenuPage menuPage);

	void ClearAllMenuPages();
};
