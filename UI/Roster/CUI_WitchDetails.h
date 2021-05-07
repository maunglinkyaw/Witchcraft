// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UI/CUI_Menu.h"
#include "Roster/C_Witch.h"
#include "CUI_WitchDetails.generated.h"

class UImage;
class UTextBlock;

class UCUI_RosterMenu;
class UCUI_NumberedStat;

class AC_Witch;
class AC_RosterManager;

UCLASS()
class WITCHCRAFT_API UCUI_WitchDetails : public UCUI_Menu
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* PortraitImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* WitchNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* BrewingStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* ArcanologyStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* LoreStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* DiplomacyStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* ManagementStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* CombatStat;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCUI_NumberedStat* SurvivalStat;

	UPROPERTY(BlueprintReadOnly)
	TMap<E_WitchSkill, UCUI_NumberedStat*> m_SkillsMap;

	UPROPERTY(BlueprintReadOnly)
	UCUI_RosterMenu* m_RosterMenu = nullptr;
	UPROPERTY(BlueprintReadOnly)
	AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(BlueprintReadOnly)
	AC_Witch* m_CurrentWitch = nullptr;

	void InitWidget();

	void LoadWitchDetails(AC_Witch* inWitch);
	
	void ShowWitchDetails();

};
