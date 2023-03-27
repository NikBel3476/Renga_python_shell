#ifndef RENGA_LOADER_HPP
#define RENGA_LOADER_HPP

#include "rengacomapi.tlh"

#include "Renga/CreateApplication.hpp"
#include "Renga/IPlugin.h"
#include "Renga/ActionEventHandler.hpp"

#include "string"
#include "memory"
#include "list"

class Renga_loader : public plugins::IPlugin
{
public:
    bool initialize(const wchar_t* pluginPath);
    void stop();
private:
    void EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr);
    void addHandler(Renga::ActionEventHandler* pHandler);
    typedef std::unique_ptr<Renga::ActionEventHandler> HandlerPtr;
    std::list<HandlerPtr> m_handlerContainer;
    //for python
    bool PyInitialize() { return true; }
};
EXPORT_PLUGIN(Renga_loader);
#endif // RENGA_LOADER_HPP
