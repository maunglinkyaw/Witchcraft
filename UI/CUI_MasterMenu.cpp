// Lin & Yin 2021


#include "CUI_MasterMenu.h"
#include "CUI_Menu.h"

#include "Witchcraft/Player/C_BaseController.h"

void UCUI_MasterMenu::ShowMenu(FName menuName)
{
	UCUI_Menu* newMenu = BlueprintShowMenu(menuName);

	if (!newMenu || !m_Controller)
	{
		return;
	}

	if (m_ActiveMenu)
	{
		m_ActiveMenu->ExitPage();
	}

	m_Controller->SetCurrentInput(this);
	m_ActiveMenu = newMenu;
	m_ActiveMenu->EnterPage(0);
}

void UCUI_MasterMenu::ShowOverrideMenu(FName menuName)
{
	UCUI_Menu* newMenu = BlueprintShowOverrideMenu(menuName);

	if (!newMenu || !m_Controller)
	{
		return;
	}
	if (m_OverrideMenu)
	{
		m_OverrideMenu->ExitPage();
	}

	m_Controller->SetCurrentInput(this);
	m_OverrideMenu = newMenu;
	m_OverrideMenu->EnterPage(1);
}

void UCUI_MasterMenu::OnMoveUp(float value)
{

}

void UCUI_MasterMenu::OnMoveRight(float value)
{

}

void UCUI_MasterMenu::OnPressConfirm()
{

}

void UCUI_MasterMenu::OnPressCancel()
{

}
