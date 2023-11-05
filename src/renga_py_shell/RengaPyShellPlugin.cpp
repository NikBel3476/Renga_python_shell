#include <QProcess>
#include <QDebug>
#include <iostream>

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
//    QStringList libraryPaths = { "./Plugins/renga_py_shell/plugins" };
//    QCoreApplication::setLibraryPaths(libraryPaths);
    QCoreApplication::addLibraryPath("./Plugins/renga_py_shell/plugins");

    int argc = 1;
    char* argv[] = { (char*)"RengaPythonShell" };
    QApplication app(argc, argv);

    proc = new QProcess(this);
    proc->setProcessChannelMode(QProcess::MergedChannels);
    proc->start("RengaPythonShell");
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOut()));

    rengaApp = Renga::CreateApplication();
    if (!rengaApp)
        return false;

        //Загрузка библиотеки QT6 для плагина
//        QString cur_dir = QString::fromStdWString(pluginPath);
//        QApplication::addLibraryPath(cur_dir);

    rengaUi = rengaApp->GetUI();
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

    app.exec();

    return true;
}

void RengaPyShellPlugin::stop() {
    this->m_handlerContainer.clear();
}

void RengaPyShellPlugin::onProjectAboutToClose() {
    if (shellWidget) {
        shellWidget->close();
        shellWidget.reset();
    }
}

void RengaPyShellPlugin::subscribeOnRengaEvents() {
    rengaEventsHandler.reset(new RengaEventsHandler(rengaApp));
    connect(rengaEventsHandler.get(), SIGNAL(projectAboutToClose()), this, SLOT(onProjectAboutToClose));
}

void RengaPyShellPlugin::addPluginButtons(const std::wstring &pluginPath) {
    pluginToolButtons.reset(new PluginToolButtons(rengaUi, pluginPath));
    connect(pluginToolButtons.get(), SIGNAL(rengaPyShellButtonClicked()), this, SLOT(onRengaPyShellButtonClicked()));
}

void RengaPyShellPlugin::onRengaPyShellButtonClicked()
{
//    ShellWidget widget;
//    widget.setMinimumSize(800, 600);
//    widget.show();
////    window.activateWindow();
//    app.exec();

    if (shellWidget)
        shellWidget->close();

    shellWidget.reset(new ShellWidget(rengaApp));
    shellWidget->show();
//    shellWidget->activateWindow();

//    app.exec();
}

void RengaPyShellPlugin::readStdOut() {
//    proc = new QProcess(this);
//    proc->setProcessChannelMode(QProcess::MergedChannels);
//    proc->start("renga_prog");
//    shellWidget->ui->output_space->insertPlainText(QString("readStdOut\n"));
    std::cout << "cout" << std::endl;
    qDebug("debug");
    QByteArray sout = proc->readAllStandardOutput();
    std::cout << "cout" << std::endl;
    qDebug("debug");
//    this->ui->output_space->insertPlainText(QString(sout));
    QString *string_out = new QString(sout);
    shellWidget->insertPlainTextToOutput(string_out);
}

void RengaPyShellPlugin::addHandler(Renga::ActionEventHandler* pHandler)
{
    m_handlerContainer.emplace_back(HandlerPtr(pHandler));
}
