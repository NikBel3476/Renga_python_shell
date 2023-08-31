#ifndef RENGA_LOADER_HPP
#define RENGA_LOADER_HPP

#import "RengaCOMAPI.tlb"

#include <QApplication>
#include <QString>
#include <QObject>

#include "Renga/CreateApplication.hpp"
#include "Renga/IPlugin.h"
#include "Renga/ActionEventHandler.hpp"
#include "string"
#include "memory"
#include "list"
#include "shellwindow.h"

class RengaPyShellPlugin : public QObject, public plugins::IPlugin
{
    Q_OBJECT

public:
    RengaPyShellPlugin();
    ~RengaPyShellPlugin();

    bool initialize(const wchar_t* pluginPath) override;
    void stop() override;

private:
    void EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr);
    void addHandler(Renga::ActionEventHandler* pHandler);
    bool PyInitialize() { return true; } // for python

    typedef std::unique_ptr<Renga::ActionEventHandler> HandlerPtr;

    std::list<HandlerPtr> m_handlerContainer;
};
EXPORT_PLUGIN(RengaPyShellPlugin);
#endif // RENGA_LOADER_HPP
