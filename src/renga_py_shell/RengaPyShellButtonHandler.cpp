#include "stdafx.h"
#include "RengaPyShellButtonHandler.h"

RengaPyShellButtonHandler::RengaPyShellButtonHandler(Renga::IActionPtr action) : Renga::ActionEventHandler(action)
{

}

void RengaPyShellButtonHandler::OnTriggered() {
    emit buttonClicked();
}

void RengaPyShellButtonHandler::OnToggled(bool checked)
{

}
