#include "stdafx.h"
#include "RengaPyShellPlugin.h"
#include "RengaEventsHandler.h"
#include "PluginToolButtons.h"
#include "ShellWidget.h"

RengaPyShellPlugin::RengaPyShellPlugin() {
    ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

RengaPyShellPlugin::~RengaPyShellPlugin() {
    ::CoUninitialize();
}

bool RengaPyShellPlugin::initialize(const wchar_t* pluginPath)
{
    auto rengaApplication = Renga::CreateApplication();
    if (!rengaApplication)
        return false;

        //Загрузка библиотеки QT6 для плагина
//        QString cur_dir = QString::fromStdWString(pluginPath);
//        QApplication::addLibraryPath(cur_dir);

    rengaApp = rengaApplication;
    rengaUi = rengaApplication->GetUI();
    /*Renga::IUIPanelExtensionPtr panel = rengaUi->CreateUIPanelExtension();

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

    auto openPyShellActionHandler = new RengaEventsHandler(buttonPyExecute);
    this->addHandler(openPyShellActionHandler);

    panel->AddDropDownButton(dropDownButton);
    rengaUi->AddExtensionToPrimaryPanel(panel);*/

    subscribeOnRengaEvents();
    addPluginButtons(pluginPath);

    return true;
}

void RengaPyShellPlugin::stop() {
    this->m_handlerContainer.clear();
}

void RengaPyShellPlugin::subscribeOnRengaEvents() {
    rengaEventsHandler.reset(new RengaEventsHandler(rengaApp));
}

void RengaPyShellPlugin::addPluginButtons(const std::wstring &pluginPath) {
    pluginToolButtons.reset(new PluginToolButtons(rengaUi, pluginPath));
    connect(pluginToolButtons.get(), SIGNAL(rengaPyShellButtonClicked()), this, SLOT(onRengaPyShellButtonClicked()));
}

void RengaPyShellPlugin::onRengaPyShellButtonClicked()
{
    //        int argc = 1;
//        char* argv[] = { (char*)"RengaPythonShell" };
//        QApplication app(argc, argv);

//    ShellWidget window;
//    window.setMinimumSize(800, 600);
//
//    window.show();
//    window.activateWindow();
//        app.exec();

    if (shellWidget)
        shellWidget->close();

    shellWidget.reset(new ShellWidget(rengaApp));
    shellWidget->show();
    shellWidget->activateWindow();
}

void RengaPyShellPlugin::addHandler(Renga::ActionEventHandler* pHandler)
{
    m_handlerContainer.emplace_back(HandlerPtr(pHandler));
}
