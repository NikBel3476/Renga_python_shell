#include "stdafx.h"
#include "PluginToolButtons.h"
#include "RengaPyShellButtonHandler.h"

PluginToolButtons::PluginToolButtons(Renga::IUIPtr rengaUi, const std::wstring &pluginPath) : rengaUi(rengaUi) {
    auto rengaPyShellDropDownButton = createRengaPyShellButton(pluginPath);
    Renga::IUIPanelExtensionPtr uiPanelExtension = rengaUi->CreateUIPanelExtension();

    uiPanelExtension->AddDropDownButton(rengaPyShellDropDownButton);
    rengaUi->AddExtensionToPrimaryPanel(uiPanelExtension);
}

Renga::IDropDownButtonPtr PluginToolButtons::createRengaPyShellButton(const std::wstring &pluginPath) {
    Renga::IImagePtr icon = rengaUi->CreateImage();
    icon->LoadFromFile((std::wstring(pluginPath) + L"/icons/repa_logo.png").c_str());

    Renga::IDropDownButtonPtr dropDownButton = rengaUi->CreateDropDownButton();
    dropDownButton->PutToolTip("Запустить Renga Python Shell");
    dropDownButton->PutIcon(icon);

    //Создаем кнопки для Py-логики
    //Исполнение из QT формы
    Renga::IActionPtr buttonPyExecute = rengaUi->CreateAction();
    EditAction(pluginPath, buttonPyExecute, L"/icons/py_logo.png", "Запустить основное окно");
    buttonPyExecute->PutDisplayName(L"Run Python shell");

    dropDownButton->AddAction(buttonPyExecute);

//    auto openPyShellActionHandler = new RengaEventsHandler(buttonPyExecute);
//    this->addHandler(openPyShellActionHandler);

    rengaPyShellButtonHandler.reset(new RengaPyShellButtonHandler(buttonPyExecute));

    connect(rengaPyShellButtonHandler.get(), SIGNAL(buttonClicked()), this, SIGNAL(rengaPyShellButtonClicked()));

    return dropDownButton;
}

void PluginToolButtons::EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr)
{
    auto renga_app = Renga::CreateApplication();
    action->ToolTip = tool_descr;
    Renga::IUIPtr renga_ui = renga_app->GetUI();
    Renga::IImagePtr icon = renga_ui->CreateImage();
    icon->LoadFromFile((pluginDir + image_name).c_str());
    action->PutIcon(icon);
}
