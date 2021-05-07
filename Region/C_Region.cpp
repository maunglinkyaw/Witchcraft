// Lin & Yin's Witchcraft 2020

#include "C_Region.h"
#include "C_RegionManager.h"
#include "C_Location.h"

#include "Witchcraft.h"
#include "C_WitchcraftStatics.h"


AC_Region::AC_Region()
{
	PrimaryActorTick.bCanEverTick = false;


}


void AC_Region::RegisterLocation(AC_Location* inLocation)
{
	if (!m_Locations.Contains(inLocation))
	{
		m_Locations.AddUnique(inLocation);

		m_Locations.Sort([](const AC_Location& A, const AC_Location& B) {
			return A.m_DisplayName.CompareTo(B.m_DisplayName) < 0;
		});
// 		m_Locations.Sort([](const AC_Location& A, const AC_Location& B) {
// 			return A.m_DisplayName.ToString() < B.m_DisplayName.ToString();
// 		});
	}
}

void AC_Region::UpdateRegionDetails()
{
	UE_LOG(LogSystem, Display, TEXT("%s - UpdateLocationDetails"), *GetName());

	m_Locations.Sort([](const AC_Location& A, const AC_Location& B) {
		return A.m_DisplayName.CompareTo(B.m_DisplayName) < 0;
	});

}

void AC_Region::BeginPlay()
{
	Super::BeginPlay();
	
}


void AC_Region::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

