#ifndef RENGA_PY_SHELL_PLUGINTOOLBUTTONS_H
#define RENGA_PY_SHELL_PLUGINTOOLBUTTONS_H

#include <QObject>

#include "stdafx.h"
#include "Renga/IPlugin.h"

class RengaPyShellButtonHandler;

class PluginToolButtons : public QObject
{
    Q_OBJECT

public:
    PluginToolButtons(Renga::IUIPtr rengaUi, const std::wstring& pluginPath);

signals:
    void rengaPyShellButtonClicked();

private:
    Renga::IDropDownButtonPtr createRengaPyShellButton(const std::wstring& pluginPath);
    void EditAction(std::wstring pluginDir, Renga::IActionPtr action, std::wstring image_name, const char* tool_descr);

    std::unique_ptr<RengaPyShellButtonHandler> rengaPyShellButtonHandler;
    Renga::IUIPtr rengaUi;
};

#endif //RENGA_PY_SHELL_PLUGINTOOLBUTTONS_H
