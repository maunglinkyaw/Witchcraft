// Lin & Yin's Witchcraft 2020

#include "C_WitchcraftStatics.h"
#include "Kismet/GameplayStatics.h"

#include "Player/C_PlayerController.h"

#include "Roster/C_RosterManager.h"

#include "Region/C_RegionManager.h"

#include "TimeEvents/C_TimeManager.h"

#include "C_LevelScript.h"

FName UC_WitchcraftStatics::GetWitchName(E_Witch witchEnum)
{
	switch (witchEnum)
	{
	case E_Witch::LIRILILIA:
		return FName(TEXT("wit_lirililia"));
		break;

	case E_Witch::CELESTE:
		return FName(TEXT("wit_celeste"));
		break;
	
	case E_Witch::SCOUT:
		return FName(TEXT("wit_scout"));
		break;

	}

	return FName(TEXT("NoName"));
}

AC_PlayerController* UC_WitchcraftStatics::GetPlayerController(UWorld* inWorld)
{
	if (inWorld)
	{
		AC_PlayerController* pc = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(inWorld, 0));

		return pc;
	}

	return nullptr;
}

AC_RegionManager* UC_WitchcraftStatics::GetRegionManager(UWorld* inWorld)
{
	if (inWorld)
	{
		AC_LevelScript* levelScript = Cast<AC_LevelScript>(inWorld->GetLevelScriptActor());

		if (levelScript)
			return levelScript->m_RegionManager;
	}

	return nullptr;
}

AC_RosterManager* UC_WitchcraftStatics::GetRosterManager(UWorld* inWorld)
{
	if (inWorld)
	{
		AC_LevelScript* levelScript = Cast<AC_LevelScript>(inWorld->GetLevelScriptActor());

		if (levelScript)
			return levelScript->m_RosterManager;
	}

	return nullptr;

}

AC_TimeManager* UC_WitchcraftStatics::GetTimeManager(UWorld* inWorld)
{
	if (inWorld)
	{
		AC_LevelScript* levelScript = Cast<AC_LevelScript>(inWorld->GetLevelScriptActor());

		if (levelScript)
			return levelScript->m_TimeManager;
	}

	return nullptr;

}

AC_ItemManager* UC_WitchcraftStatics::GetItemManager(UWorld* inWorld)
{
	if (inWorld)
	{
		AC_LevelScript* levelScript = Cast<AC_LevelScript>(inWorld->GetLevelScriptActor());

		if (levelScript)
			return levelScript->m_ItemManager;
	}

	return nullptr;

}
