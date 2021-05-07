// Lin & Yin's Witchcraft 2020


#include "CUI_RosterMenu.h"
#include "CUI_RosterCard.h"
#include "CUI_WitchDetails.h"

#include "UI/Gameplay/CUI_Gameplay.h"

#include "Roster/C_RosterManager.h"
#include "Roster/C_Witch.h"

#include "UniformGridPanel.h"
#include "UniformGridSlot.h"

#include "Witchcraft.h"


void UCUI_RosterMenu::InitRosterMenu()
{
	UE_LOG(LogMenu, Display, TEXT("%s - InitRosterMenu"), *GetName());

	m_WitchDetails->m_RosterMenu = this;
	m_WitchDetails->m_RosterManager = m_RosterManager;
	m_WitchDetails->InitWidget();

	RosterGrid->ClearChildren();
}

void UCUI_RosterMenu::CreateRosterCard(AC_Witch* inWitch)
{
	UE_LOG(LogMenu, Display, TEXT("%s - CreateRosterCard - inWitch: %s"), *GetName(), *GetNameSafe(inWitch));

	if (m_RosterCardMap.Contains(inWitch->m_StaticData.witchName))
	{
		if (m_RosterCardMap[inWitch->m_StaticData.witchName]->m_WitchName == inWitch->m_StaticData.witchName)
		{
			return;
		}
	}

	UE_LOG(LogMenu, Display, TEXT("%s - CreateRosterCard - m_RosterCardClass: %s"), *GetName(), *GetNameSafe(m_RosterCardClass));
	if (m_RosterCardClass)
	{
		m_TempCard = CreateWidget<UCUI_RosterCard>(this, m_RosterCardClass);

		UE_LOG(LogMenu, Display, TEXT("%s - CreateRosterCard - m_TempCard: %s"), *GetName(), *GetNameSafe(m_TempCard));

		if (m_TempCard)
		{
			m_TempCard->m_RosterMenu = this;
			m_TempCard->InitRosterCard(inWitch);

			m_RosterCardMap.Add(inWitch->m_StaticData.witchName, m_TempCard);
			m_RosterCardArray.AddUnique(m_TempCard);

			int32 totalCards = m_RosterCardArray.Num();
			
			float tempFloat = (float)(totalCards - 1) / 2.f;

			m_CurrentRow = FMath::RoundToZero(tempFloat);
			m_CurrentColumn = (totalCards % 2) != 1;

			UE_LOG(LogMenu, Display, TEXT("%s - CreateRosterCard - m_CurrentRow: %d, m_CurrentColumn: %d"), *GetName(), m_CurrentRow, m_CurrentColumn);

			UUniformGridSlot* tempSlot = RosterGrid->AddChildToUniformGrid(m_TempCard, m_CurrentRow, m_CurrentColumn);
		}
	}

}

void UCUI_RosterMenu::ShowWitchDetails(AC_Witch* witch)
{
	if (m_WitchDetails && m_GameplayUI)
	{
		m_WitchDetails->LoadWitchDetails(witch);

		m_GameplayUI->GoToMenuPage(E_MenuPage::WITCH_MENU);
	}
}
