// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UI/CUI_Menu.h"
#include "CUI_RegionMenu.generated.h"


class AC_Location;
class AC_Region;
class UImage;
class UTextBlock;

UCLASS()
class WITCHCRAFT_API UCUI_RegionMenu : public UCUI_Menu
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* LocationImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LocationText;

	UPROPERTY(BlueprintReadOnly)
	class AC_RegionManager* m_RegionManager = nullptr;
	UPROPERTY(BlueprintReadOnly)
	AC_Region* m_CurrentRegion = nullptr;
	UPROPERTY(BlueprintReadOnly)
	AC_Location* m_CurrentLocation = nullptr;

	void ShowLocationMenu(AC_Location* inLocation);

	UFUNCTION(BlueprintCallable)
	void AddNewActivity();


protected:
	void LoadRegion(AC_Region* inRegion);
	void LoadLocation(AC_Location* inLocation);

	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintLoadRegion(AC_Region* inRegion);
	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintLoadLocation(AC_Location* inLocation);

	UFUNCTION(BlueprintImplementableEvent)
		void ToggleActivityButton();

};
