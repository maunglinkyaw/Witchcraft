// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UI/CUI_Button.h"
#include "CUI_RosterCard.generated.h"

class UImage;
class UTextBlock;

class UCUI_RosterMenu;
class AC_Witch;

UCLASS()
class WITCHCRAFT_API UCUI_RosterCard : public UCUI_Button
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* PortraitImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* NotifyIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* LevelUpIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NameText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ActivityText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LocationText;

	UPROPERTY(BlueprintReadOnly)
	UCUI_RosterMenu* m_RosterMenu = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AC_Witch* m_Witch = nullptr;
	UPROPERTY(BlueprintReadOnly)
	FName m_WitchName;

	void InitRosterCard(AC_Witch* inWitch);

	void OnButtonPressed() override;
};
