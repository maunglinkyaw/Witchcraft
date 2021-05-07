// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "UI/CUI_Menu.h"
#include "CUI_RosterMenu.generated.h"

class UUniformGridPanel;

class UCUI_Gameplay;
class UCUI_RosterCard;
class UCUI_WitchDetails;

class AC_Witch;

UCLASS()
class WITCHCRAFT_API UCUI_RosterMenu : public UCUI_Menu
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* RosterGrid;
// 	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
// 	UCUI_WitchDetails* WitchDetails;
	
	UPROPERTY(BlueprintReadOnly)
	UCUI_WitchDetails* m_WitchDetails = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<UCUI_RosterCard> m_RosterCardClass = nullptr;

	UPROPERTY()
	TMap<FName, UCUI_RosterCard*> m_RosterCardMap;
	UPROPERTY()
	class AC_RosterManager* m_RosterManager = nullptr;

	UCUI_RosterCard* m_TempCard = nullptr;
	TArray<UCUI_RosterCard*> m_RosterCardArray;
	
	int32 m_CurrentRow = 0;
	int32 m_CurrentColumn = 0;

	void InitRosterMenu();
	void CreateRosterCard(AC_Witch* inWitch);

	void ShowWitchDetails(AC_Witch* witch);

};
