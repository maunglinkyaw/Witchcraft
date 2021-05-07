// Lin & Yin's Witchcraft 2020


#include "C_RegionManager.h"
#include "C_Region.h"
#include "C_Location.h"

#include "TimeEvents/C_TimeManager.h"

#include "UI/Region/CUI_RegionMenu.h"

#include "C_WitchcraftStatics.h"
#include "Witchcraft.h"

AC_RegionManager::AC_RegionManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AC_RegionManager::BeginPlay()
{
	Super::BeginPlay();

}

void AC_RegionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_RegionManager::InitRegionManager()
{
	UE_LOG(LogSystem, Display, TEXT("%s - InitRegionManager"), *GetName());

	m_RegionMenu->m_RegionManager = this;
// 	m_RegionMenu->InitRosterMenu();

}

void AC_RegionManager::ShowLocationMenu(AC_Location* inLocation)
{
	UE_LOG(LogSystem, Display, TEXT("%s - ShowLocationMenu - inLocation: %s"), *GetName(), *GetNameSafe(inLocation));

	if (m_RegionMenu && inLocation)
	{
		m_RegionMenu->ShowLocationMenu(inLocation);
	}
}

void AC_RegionManager::AddEventToCalendar()
{
	UE_LOG(LogSystem, Display, TEXT("%s - AddEventToCalendar - m_TimeManager: %s"), *GetName(), *GetNameSafe(m_TimeManager));

}

