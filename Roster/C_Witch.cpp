// Lin & Yin's Witchcraft 2020


#include "C_Witch.h"

#include "Witchcraft/C_WitchcraftStatics.h"

AC_Witch::AC_Witch()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void AC_Witch::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Witch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Witch::SetWitchStatsStruct(F_WitchStats statsStruct)
{
	m_WitchStats = statsStruct;

}

void AC_Witch::ToggleMapActivation(bool isActive)
{

}

void AC_Witch::AddStatsGrowth(E_WitchSkill skillStat, int32 inGrowth)
{
	switch (skillStat)
	{
	case E_WitchSkill::BREWING:
		m_WitchStats.brewing.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::ARCANOLOGY:
		m_WitchStats.arcanology.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::LORE:
		m_WitchStats.lore.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::DIPLOMACY:
		m_WitchStats.diplomacy.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::COMBAT:
		m_WitchStats.combat.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::MANAGEMENT:
		m_WitchStats.management.AddGrowth(inGrowth);
		break;
	case E_WitchSkill::SURVIVAL:
		m_WitchStats.survival.AddGrowth(inGrowth);
		break;


	}
}

F_WitchStaticData AC_Witch::GetWitchStaticData()
{
	return m_StaticData;

// Returns pointer to said data. Dereference to use.
// usableData = *pointerData;

// 	F_WitchStaticData* returnData = nullptr;
// 
// 	if (m_WitchDataTable)
// 	{
// 		FString contextString = "";
// 		returnData = m_WitchDataTable->FindRow<F_WitchStaticData>(UC_WitchcraftStatics::GetWitchName(inWitch), contextString);
// 	}
// 
// 	return returnData;
}

