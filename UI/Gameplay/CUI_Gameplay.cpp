// Lin & Yin's Witchcraft 2020


#include "CUI_Gameplay.h"
#include "Witchcraft.h"

#include "Player/C_PlayerController.h"

#include "UI/CUI_Menu.h"
#include "UI/Roster/CUI_RosterMenu.h"
#include "UI/Roster/CUI_WitchDetails.h"
#include "UI/Region/CUI_RegionMenu.h"


void UCUI_Gameplay::NativeConstruct()
{
	Super::NativeConstruct();

	m_MenuMap.Emplace(E_MenuPage::ROSTER_MENU, RosterMenu);
	m_MenuMap.Emplace(E_MenuPage::WITCH_MENU, WitchDetails);
	m_MenuMap.Emplace(E_MenuPage::REGION_MENU, RegionMenu);

	RosterMenu->m_GameplayUI = this;
	RosterMenu->m_WitchDetails = WitchDetails;

	WitchDetails->m_GameplayUI = this;
	
	RegionMenu->m_GameplayUI = this;
}

void UCUI_Gameplay::GoToMenuPage(E_MenuPage menuPage, bool purgeHistory)
{
	UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - %s"), *GetName(), *E_CommonEnums::EnumToString(E_MenuPage, menuPage));

	if (!m_MenuMap.Contains(menuPage) || !m_MenuMap[menuPage])
	{
		UE_LOG(LogMenu, Warning, TEXT("%s - GoToMenuPage - MISSING MENU!"), *GetName());
		return;
	}

	if (m_CurrentMenu == m_MenuMap[menuPage])
	{
		UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - Re-entering Page: %s"), *GetName(), *GetNameSafe(m_CurrentMenu));

		if (m_CurrentMenu)
			m_CurrentMenu->ReenterPage();

		return;
	}

	if (purgeHistory)
	{
		UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - PURGING HISTORY"), *GetName());
		ClearAllMenuPages();
	}

	m_CurrentMenu = m_MenuMap[menuPage];

	// First check if the current Menu is already in our History. If yes remove all layers above it.
	if (m_MenuLayers.Contains(m_CurrentMenu)) 
	{
		m_CurrentLayer = m_MenuLayers.Find(m_CurrentMenu);

		UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - CONTAINS - m_CurrentLayer: %d"), *GetName(), m_CurrentLayer);

		if (m_MenuLayers.Num() > m_CurrentLayer)
		{
			int32 removalIndex = m_CurrentLayer + 1;
			int32 removalCount = m_MenuLayers.Num() - removalIndex;

			UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - CONTAINS - removalIndex: %d, removalCount: %d"), *GetName(), removalIndex, removalCount);

			m_MenuLayers.RemoveAt(removalIndex, removalCount);
		}
		
	}
	// If the current page isn't in history, add it at the end.
	else
	{
		m_CurrentLayer = m_MenuLayers.Emplace(m_CurrentMenu);

		UE_LOG(LogMenu, Display, TEXT("%s - GoToMenuPage - m_CurrentLayer: %d"), *GetName(), m_CurrentLayer);
	}

	m_CurrentMenu->EnterPage(m_CurrentLayer);
}

void UCUI_Gameplay::GoBackMenuPage()
{
	UE_LOG(LogMenu, Display, TEXT("%s - GoBackMenuPage - m_CurrentMenu: %s"), *GetName(), *GetNameSafe(m_CurrentMenu));

	if (m_CurrentMenu)
	{
		m_CurrentMenu->ExitPage();
		m_CurrentMenu = nullptr;
		m_MenuLayers.Pop();

		m_CurrentLayer = m_MenuLayers.Num() - 1;
	}

	UE_LOG(LogMenu, Display, TEXT("%s - GoBackMenuPage - m_CurrentLayer: %d"), *GetName(), m_CurrentLayer);

	if (m_MenuLayers.Num() > 0)
	{
		m_CurrentMenu = m_MenuLayers[m_CurrentLayer];

		if (m_CurrentMenu)
		{
			m_CurrentMenu->EnterPage(m_CurrentLayer);
		}
		else
		{

		}
	}
}

void UCUI_Gameplay::ShortcutToPage(E_MenuPage menuPage)
{
	UE_LOG(LogMenu, Display, TEXT("%s - ShortcutToPage - %s"), *GetName(), *E_CommonEnums::EnumToString(E_MenuPage, menuPage));

	if (!m_MenuMap.Contains(menuPage) || !m_MenuMap[menuPage])
	{
		UE_LOG(LogMenu, Warning, TEXT("%s - ShortcutToPage - MISSING MENU!"), *GetName());
		return;
	}

	if (m_CurrentMenu == m_MenuMap[menuPage])
	{
		ClearAllMenuPages();
	}
	else
	{
		GoToMenuPage(menuPage, true);
	}
}

void UCUI_Gameplay::ClearAllMenuPages()
{
	for (int32 i = 0; i < m_MenuLayers.Num(); i++)
	{
		m_MenuLayers[i]->ExitPage();
	}

	m_CurrentMenu = nullptr;

	m_MenuLayers.Empty();
	m_CurrentLayer = 0;
}
