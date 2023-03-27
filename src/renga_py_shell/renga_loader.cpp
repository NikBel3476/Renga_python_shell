#include "renga_loader.hpp"
#include "Renga\CreateApplication.hpp"

#include "shellwindow.h"
#include <QApplication>

class py_open_form :public Renga::ActionEventHandler {
public:
    py_open_form(Renga::IActionPtr action) : Renga::ActionEventHandler(action) {}
    void OnTriggered() override
    {
        QCoreApplication::addLibraryPath("C:/Qt/6.3.2/msvc2019_64/plugins");
        int argc = 1;
        char* args[] = { (char*)"RengaPythonShell" };
        QApplication a(argc, args);
        ShellWindow w;
        w.show();
        a.exec();
    }
    void OnToggled(bool checked) override {}

};

void Renga_loader::addHandler(Renga::ActionEventHandler* pHandler)
{
    m_handlerContainer.emplace_back(HandlerPtr(pHandler));
}
void Renga_loader::EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr)
{
    auto renga_app = Renga::CreateApplication();
    action->ToolTip = tool_descr;
    Renga::IUIPtr renga_ui = renga_app->GetUI();
    Renga::IImagePtr icon = renga_ui->CreateImage();
    std::wstring plugin_dir(pluginDir);
    icon->LoadFromFile((plugin_dir + image_name).c_str());
    action->PutIcon(icon);
}
bool Renga_loader::initialize(const wchar_t* pluginPath)
{
    auto renga_app = Renga::CreateApplication();
    if (renga_app)
    {
        //Check python env
        if (PyInitialize() == false) return false;

        Renga::IUIPtr renga_ui = renga_app->GetUI();
        Renga::IUIPanelExtensionPtr panel = renga_ui->CreateUIPanelExtension();

        Renga::IDropDownButtonPtr down_button = renga_ui->CreateDropDownButton();
        Renga::IImagePtr icon = renga_ui->CreateImage();
        std::wstring plugin_dir(pluginPath);
        icon->LoadFromFile((plugin_dir + L"\\repa_logo.png").c_str());
        down_button->PutIcon(icon);
        down_button->ToolTip = "Запустить Renga Python Shell";

        //Создаем кнопки для Py-логики
        //Исполнение из QT формы
        Renga::IActionPtr button_py_execute = renga_ui->CreateAction();
        EditAction(pluginPath, button_py_execute, L"\\py_logo.png", "Запустить основное окно");
        button_py_execute->DisplayName = "Run Python shell";
        this->addHandler(new py_open_form(button_py_execute));
        down_button->AddAction(button_py_execute);


        panel->AddDropDownButton(down_button);
        renga_ui->AddExtensionToPrimaryPanel(panel);
    }
    else return false;
    return true;
}
void Renga_loader::stop() {
    this->m_handlerContainer.clear();
}
