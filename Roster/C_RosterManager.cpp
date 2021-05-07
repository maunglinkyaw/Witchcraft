// Lin & Yin's Witchcraft 2020


#include "C_RosterManager.h"
#include "C_Witch.h"

#include "UI/Roster/CUI_RosterMenu.h"

#include "C_WitchcraftStatics.h"
#include "Witchcraft.h"

AC_RosterManager::AC_RosterManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AC_RosterManager::BeginPlay()
{
	Super::BeginPlay();
	
}


void AC_RosterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_RosterManager::InitRosterManager()
{
	UE_LOG(LogSystem, Display, TEXT("%s - InitRosterManager"), *GetName());

	SpawnAllWitches();

	m_RosterMenu->m_RosterManager = this;
	m_RosterMenu->InitRosterMenu();
}

void AC_RosterManager::SpawnAllWitches()
{
	UE_LOG(LogSystem, Display, TEXT("%s - SpawnAllWitches"), *GetName());

	for (const TPair<FName, TSubclassOf<AC_Witch>>& pair : m_WitchClassMap)
	{
		UE_LOG(LogSystem, Display, TEXT("%s - SpawnAllWitches - witchName: %s"), *GetName(), *pair.Key.ToString());
		
		AC_Witch* witch = SpawnWitch(pair.Key);

		if (witch)
		{
			m_AllWitchMap.Emplace(pair.Key, witch);
		}
	}
}


AC_Witch* AC_RosterManager::SpawnWitch(FName witchName)
{
	UE_LOG(LogSystem, Display, TEXT("%s - SpawnWitch - witchName: %s"), *GetName(), *witchName.ToString());

	if (m_WitchClassMap.Contains(witchName) && m_WitchClassMap[witchName])
	{
		AC_Witch* witch = GetWorld()->SpawnActor<AC_Witch>(m_WitchClassMap[witchName]);

		UE_LOG(LogSystem, Display, TEXT("%s - SpawnWitch - witch: %s"), *GetName(), *GetNameSafe(witch));

		if (witch)
		{
			// Init Witch here.
			witch->SetActorHiddenInGame(true);
		}

		return witch;
	}

	return nullptr;
}


void AC_RosterManager::AddWitchToRoster(FName witchName)
{
	UE_LOG(LogSystem, Display, TEXT("%s - AddWitchToRoster - witchName: %s"), *GetName(), *witchName.ToString());

	if (m_AllWitchMap.Contains(witchName) && m_AllWitchMap[witchName])
	{
		m_WitchRoster.Emplace(witchName, m_AllWitchMap[witchName]);

		m_RosterMenu->CreateRosterCard(m_AllWitchMap[witchName]);
	}
}

AC_Witch* AC_RosterManager::GetWitchByName(FName witchName)
{
	if (m_AllWitchMap.Contains(witchName))
	{
		return m_AllWitchMap[witchName];
	}

	return nullptr;
}

TArray<AC_Witch*> AC_RosterManager::GetWitchesArray()
{
	m_WitchesArray.Empty();

	for (const TPair<FName, AC_Witch*>& pair : m_AllWitchMap)
	{
// 		pair.Key;
// 		pair.Value;

		if (pair.Value)
		{
			m_WitchesArray.AddUnique(pair.Value);
		}
	}

	return m_WitchesArray;
}

void AC_RosterManager::ShowWitchDetails(FName witchName)
{
	if (m_AllWitchMap.Contains(witchName) && m_AllWitchMap[witchName])
	{
		m_RosterMenu->ShowWitchDetails(m_AllWitchMap[witchName]);
	}
}

