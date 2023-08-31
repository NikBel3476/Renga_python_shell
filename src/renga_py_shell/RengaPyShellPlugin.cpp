#include "RengaPyShellPlugin.hpp"

class PyForm : public Renga::ActionEventHandler {
public:
    PyForm(Renga::IActionPtr action) : Renga::ActionEventHandler(action) {}

    void OnTriggered() override
    {
        int argc = 1;
        char* args[] = { (char*)"RengaPythonShell" };
        QApplication app(argc, args);

        ShellWindow window;
        window.setMinimumSize(800, 600);

        window.show();
        app.exec();
    }

    void OnToggled(bool checked) override {}
};

RengaPyShellPlugin::RengaPyShellPlugin() {
    ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

RengaPyShellPlugin::~RengaPyShellPlugin() {
    ::CoUninitialize();
}

void RengaPyShellPlugin::addHandler(Renga::ActionEventHandler* pHandler)
{
    m_handlerContainer.emplace_back(HandlerPtr(pHandler));
}

void RengaPyShellPlugin::EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr)
{
    auto renga_app = Renga::CreateApplication();
    action->ToolTip = tool_descr;
    Renga::IUIPtr renga_ui = renga_app->GetUI();
    Renga::IImagePtr icon = renga_ui->CreateImage();
    std::wstring plugin_dir(pluginDir);
    icon->LoadFromFile((plugin_dir + image_name).c_str());
    action->PutIcon(icon);
}

bool RengaPyShellPlugin::initialize(const wchar_t* pluginPath)
{
    auto rengaApplication = Renga::CreateApplication();

    if (!rengaApplication)
        return false;

        //Загрузка библиотеки QT6 для плагина
//        QString cur_dir = QString::fromStdWString(pluginPath);
//        QApplication::addLibraryPath(cur_dir);

    Renga::IUIPtr renga_ui = rengaApplication->GetUI();
    Renga::IUIPanelExtensionPtr panel = renga_ui->CreateUIPanelExtension();

    Renga::IDropDownButtonPtr down_button = renga_ui->CreateDropDownButton();
    Renga::IImagePtr icon = renga_ui->CreateImage();
    std::wstring plugin_dir(pluginPath);
    icon->LoadFromFile((plugin_dir + L":/icons/repa_logo.png").c_str());
    down_button->PutIcon(icon);
    down_button->ToolTip = "Запустить Renga Python Shell";

    //Создаем кнопки для Py-логики
    //Исполнение из QT формы
    Renga::IActionPtr button_py_execute = renga_ui->CreateAction();
    EditAction(pluginPath, button_py_execute, L":/icons/py_logo.png", "Запустить основное окно");
    button_py_execute->DisplayName = "Run Python shell";
    this->addHandler(new PyForm(button_py_execute));
    down_button->AddAction(button_py_execute);

    panel->AddDropDownButton(down_button);
    renga_ui->AddExtensionToPrimaryPanel(panel);

    return true;
}

void RengaPyShellPlugin::stop() {
    this->m_handlerContainer.clear();
}
