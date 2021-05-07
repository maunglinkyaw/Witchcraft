// Lin & Yin's Witchcraft 2020


#include "CUI_WitchDetails.h"
#include "CUI_NumberedStat.h"


#include "Roster/C_RosterManager.h"

#include "TextBlock.h"
#include "Image.h"

void UCUI_WitchDetails::InitWidget()
{

	m_SkillsMap.Add(E_WitchSkill::BREWING, BrewingStat);
	m_SkillsMap.Add(E_WitchSkill::ARCANOLOGY, ArcanologyStat);
	m_SkillsMap.Add(E_WitchSkill::LORE, LoreStat);
	m_SkillsMap.Add(E_WitchSkill::DIPLOMACY, DiplomacyStat);
	m_SkillsMap.Add(E_WitchSkill::MANAGEMENT, ManagementStat);
	m_SkillsMap.Add(E_WitchSkill::COMBAT, CombatStat);
	m_SkillsMap.Add(E_WitchSkill::SURVIVAL, SurvivalStat);

}

void UCUI_WitchDetails::LoadWitchDetails(AC_Witch* inWitch)
{
	if (inWitch)
	{
		m_CurrentWitch = inWitch;

		PortraitImage->SetBrushFromSoftTexture(m_CurrentWitch->m_StaticData.largePortrait);

		WitchNameText->SetText(m_CurrentWitch->m_StaticData.displayName.ToUpper());

		m_SkillsMap[E_WitchSkill::BREWING]->SetStat(m_CurrentWitch->m_WitchStats.brewing.rank);
		m_SkillsMap[E_WitchSkill::ARCANOLOGY]->SetStat(m_CurrentWitch->m_WitchStats.arcanology.rank);
		m_SkillsMap[E_WitchSkill::LORE]->SetStat(m_CurrentWitch->m_WitchStats.lore.rank);
		m_SkillsMap[E_WitchSkill::DIPLOMACY]->SetStat(m_CurrentWitch->m_WitchStats.diplomacy.rank);
		m_SkillsMap[E_WitchSkill::MANAGEMENT]->SetStat(m_CurrentWitch->m_WitchStats.combat.rank);
		m_SkillsMap[E_WitchSkill::COMBAT]->SetStat(m_CurrentWitch->m_WitchStats.management.rank);
		m_SkillsMap[E_WitchSkill::SURVIVAL]->SetStat(m_CurrentWitch->m_WitchStats.survival.rank);
	}
}

void UCUI_WitchDetails::ShowWitchDetails()
{
// 	if (!IsVisible())
// 		SetVisibility(ESlateVisibility::SelfHitTestInvisible);


}
