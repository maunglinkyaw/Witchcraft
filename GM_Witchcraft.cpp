#include "GM_Witchcraft.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "Witchcraft.h"
#include "E_CommonEnums.h"
#include "C_LevelScript.h"
#include "C_WitchcraftSave.h"
#include "WitchcraftGameInstance.h"

#include "TimeEvents/C_TimeManager.h"
#include "Inventory/C_ItemManager.h"
#include "Player/C_PlayerController.h"
#include "Player/C_PlayerPawn.h"
#include "Roster/C_RosterManager.h"
#include "Roster/C_Witch.h"
#include "Region/C_RegionManager.h"

#include "UI/Gameplay/CUI_Gameplay.h"
#include "UI/Roster/CUI_RosterMenu.h"



AGM_Witchcraft::AGM_Witchcraft()
{
	PlayerControllerClass = AC_PlayerController::StaticClass();
	DefaultPawnClass = AC_PlayerPawn::StaticClass();
}


void AGM_Witchcraft::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogSystem, Display, TEXT("%s - BeginPlay - ProjectDir: %s"), *GetName(), *FPaths::ProjectDir());

	m_GameInstance = GetGameInstance<UWitchcraftGameInstance>();

	if (m_GameInstance)
	{
		m_SaveGameName = m_GameInstance->m_SaveSlotToLoad;

		UE_LOG(LogSystem, Display, TEXT("%s - BeginPlay - m_CurrentSaveGameName: %s"), *GetName(), *m_SaveGameName);

		if (m_UseDebugData)
		{
			UE_LOG(LogSystem, Display, TEXT("%s - BeginPlay - Using Debug Data"), *GetName());
			InitCurrentGameplaySession();
		}
		else
		{
			if (UGameplayStatics::DoesSaveGameExist(m_SaveGameName, 0))
			{
				LoadGame(m_SaveGameName);
			}
			else
			{
				InitCurrentGameplaySession();
			}
		}
	}
}


void AGM_Witchcraft::InitCurrentGameplaySession()
{
	UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - m_GameplaySessionData.playerName: %s"), *GetName(), *m_GameplaySessionData.playerName);

	if (m_GameplayUIClass && !m_GameplayUI)
	{
		GetGameplayUI();
	}

	m_LevelScript = Cast<AC_LevelScript>(GetWorld()->GetLevelScriptActor());

	if (m_LevelScript)
	{
		m_TimeManager = m_LevelScript->m_TimeManager;
		m_RosterManager = m_LevelScript->m_RosterManager;
		m_RegionManager = m_LevelScript->m_RegionManager;
	}

	if (m_TimeManager)
	{
		m_TimeManager->m_GameplayUI = m_GameplayUI;
		m_TimeManager->m_CalendarUI = m_GameplayUI->CalendarUI;
		m_TimeManager->InitTimeManager();
	}

	if (m_RosterManager)
	{
		m_RosterManager->m_RosterMenu = m_GameplayUI->RosterMenu;
		
		m_RosterManager->InitRosterManager();
		
		for (const TPair<FName, F_WitchStats>& pair : m_GameplaySessionData.witchStatsMap)
		{
			UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - nameString: %s"), *GetName(), *pair.Key.ToString());
			
			AC_Witch* witch = m_RosterManager->GetWitchByName(pair.Key);
			
			if (witch)
			{
				witch->SetWitchStatsStruct(pair.Value);
			}

			m_RosterManager->AddWitchToRoster(pair.Key);
		}
	}

	if (m_RegionManager)
	{
		m_RegionManager->m_RegionMenu = m_GameplayUI->RegionMenu;
		m_RegionManager->InitRegionManager();

	}
}


void AGM_Witchcraft::SearchGameplayTag()
{
// 	for (const TPair<FGameplayTag, F_WitchStats>& pair : m_GameplaySessionData.witchTagMap)
// 	{
// 		// 		pair.Key;
// 		// 		pair.Value;
// 
// 		FString tagString = pair.Key.ToString();
// 		UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - gameplayTag: %s"), *GetName(), *tagString);
// 
// 		FGameplayTag tempTag = FGameplayTag::RequestGameplayTag(FName("Witch"));
// 
// 		if (pair.Key.MatchesTag(tempTag))
// 		{
// 			UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - Matches Tag: %s"), *GetName(), *tempTag.ToString());
// 		}
// 	}
}

UCUI_Gameplay* AGM_Witchcraft::GetGameplayUI()
{
	UE_LOG(LogSystem, Display, TEXT("%s - GetGameplayUI - m_GameplayUI: %s"), *GetName(), *GetNameSafe(m_GameplayUI));

	if (m_GameplayUI)
	{
		return m_GameplayUI;
	}
	else
	{
		UE_LOG(LogSystem, Display, TEXT("%s - GetGameplayUI - Creating new GameplayUI: %s"), *GetName(), *GetNameSafe(m_GameplayUIClass));

		if (m_GameplayUIClass)
		{
			m_GameplayUI = CreateWidget<UCUI_Gameplay>(GetWorld(), m_GameplayUIClass, "GameplayUI");
			m_GameplayUI->m_GameMode = this;
			m_GameplayUI->AddToViewport();
		}

		return m_GameplayUI;
	}
}

void AGM_Witchcraft::SaveGame()
{
	if (!m_CurrentSaveGame)
	{
		m_CurrentSaveGame = Cast<UC_WitchcraftSave>(UGameplayStatics::CreateSaveGameObject(UC_WitchcraftSave::StaticClass()));
	}

	if (m_CurrentSaveGame)
	{
		UE_LOG(LogSystem, Display, TEXT("%s - SaveGame - m_CurrentSaveGameName: %s"), *GetName(), *m_SaveGameName);

		// Set up the (optional) delegate.
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &AGM_Witchcraft::OnSaveGameDone);

		// Set data on the savegame object.
		m_CurrentSaveGame->m_PlayerName = TEXT("PlayerOne");

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(m_CurrentSaveGame, m_SaveGameName, 0, SavedDelegate);
	}
}

void AGM_Witchcraft::OnSaveGameDone(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{

}

void AGM_Witchcraft::LoadGame(FString slotName)
{
	// Set up the delegate.
	FAsyncLoadGameFromSlotDelegate loadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	loadedDelegate.BindUObject(this, &AGM_Witchcraft::OnLoadGameDone);
	UGameplayStatics::AsyncLoadGameFromSlot(slotName, 0, loadedDelegate);
}

void AGM_Witchcraft::OnLoadGameDone(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UE_LOG(LogSystem, Display, TEXT("%s - OnLoadGameDone - LoadedGameData: %s"), *GetName(), *GetNameSafe(LoadedGameData));

	m_CurrentSaveGame = Cast<UC_WitchcraftSave>(LoadedGameData);

	if (!m_CurrentSaveGame)
	{
		UE_LOG(LogSystem, Display, TEXT("%s - OnLoadGameDone - MISSING m_CurrentSaveGame"), *GetName());
		return;
	}

	InitCurrentGameplaySession();
}
