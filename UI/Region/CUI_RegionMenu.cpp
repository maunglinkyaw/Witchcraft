// Lin & Yin's Witchcraft 2020


#include "CUI_RegionMenu.h"
#include "Witchcraft.h"

#include "UI/Gameplay/CUI_Gameplay.h"

#include "Region/C_RegionManager.h"
#include "Region/C_Region.h"
#include "Region/C_Location.h"

#include "Roster/C_RosterManager.h"
#include "Roster/C_Witch.h"


void UCUI_RegionMenu::ShowLocationMenu(AC_Location* inLocation)
{
	UE_LOG(LogMenu, Display, TEXT("%s - ShowLocation - inLocation: %s"), *GetName(), *GetNameSafe(inLocation));

	LoadRegion(inLocation->m_Region);

	if (m_GameplayUI)
	{
		m_GameplayUI->GoToMenuPage(E_MenuPage::REGION_MENU);
	}
}

void UCUI_RegionMenu::AddNewActivity()
{

}



void UCUI_RegionMenu::LoadRegion(AC_Region* inRegion)
{
	UE_LOG(LogMenu, Display, TEXT("%s - LoadRegion - inRegion: %s"), *GetName(), *GetNameSafe(inRegion));
	
	if (!inRegion) return;

	if (m_CurrentRegion != inRegion)
	{
		m_CurrentRegion = inRegion;

		BlueprintLoadRegion(m_CurrentRegion);
	}
}

void UCUI_RegionMenu::LoadLocation(AC_Location* inLocation)
{
	UE_LOG(LogMenu, Display, TEXT("%s - LoadLocation - inLocation: %s"), *GetName(), *GetNameSafe(inLocation));

	if (!inLocation) return;

	if (m_CurrentLocation != inLocation)
	{
		m_CurrentLocation = inLocation;

		BlueprintLoadLocation(m_CurrentLocation);
	}

}
