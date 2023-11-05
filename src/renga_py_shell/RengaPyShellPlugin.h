#ifndef RENGA_LOADER_HPP
#define RENGA_LOADER_HPP

#include <string>
#include <list>
#include <QString>
#include <QObject>
#include <QProcess>

#include <Renga/ActionEventHandler.hpp>
#include <Renga/IPlugin.h>

class ShellWidget;
class RengaEventsHandler;
class PluginToolButtons;

class RengaPyShellPlugin : public QObject, public plugins::IPlugin
{
Q_OBJECT

public:
    RengaPyShellPlugin();
    ~RengaPyShellPlugin();

    bool initialize(const wchar_t* pluginPath) override;
    void stop() override;

private slots:
    void onRengaPyShellButtonClicked();
    void onProjectAboutToClose();
    void readStdOut();

private:
    void addHandler(Renga::ActionEventHandler* pHandler);
    bool PyInitialize() { return true; } // for python
    void subscribeOnRengaEvents();
    void addPluginButtons(const std::wstring& pluginPath);

    Renga::IApplicationPtr rengaApp;
    Renga::IUIPtr rengaUi;

    typedef std::unique_ptr<Renga::ActionEventHandler> HandlerPtr;

    std::list<HandlerPtr> m_handlerContainer;
    std::unique_ptr<RengaEventsHandler> rengaEventsHandler;
    std::unique_ptr<PluginToolButtons> pluginToolButtons;
    std::unique_ptr<ShellWidget> shellWidget;
    QProcess *proc;
};
//EXPORT_PLUGIN(RengaPyShellPlugin);
#endif // RENGA_LOADER_HPP
