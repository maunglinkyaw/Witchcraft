// Lin & Yin's Witchcraft 2020


#include "CUI_RosterCard.h"
#include "CUI_RosterMenu.h"

#include "Roster/C_Witch.h"

#include "TextBlock.h"
#include "Image.h"

#include "Witchcraft.h"

void UCUI_RosterCard::InitRosterCard(AC_Witch* inWitch)
{
	UE_LOG(LogSystem, Display, TEXT("%s - InitRosterCard - inWitch: %s"), *GetName(), *GetNameSafe(inWitch));

	if (inWitch)
	{
		m_Witch = inWitch;
		m_WitchName = inWitch->m_StaticData.witchName;

		NameText->SetText(inWitch->m_StaticData.displayName.ToUpper());
		PortraitImage->SetBrushFromSoftTexture(inWitch->m_StaticData.smallPortrait);
	}
}

void UCUI_RosterCard::OnButtonPressed()
{
	if (m_RosterMenu)
	{
		m_RosterMenu->ShowWitchDetails(m_Witch);
	}
}
