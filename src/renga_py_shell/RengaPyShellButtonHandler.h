#ifndef RENGA_PY_SHELL_RENGAPYSHELLBUTTONHANDLER_H
#define RENGA_PY_SHELL_RENGAPYSHELLBUTTONHANDLER_H

#include <QObject>

#include "Renga/ActionEventHandler.hpp"

class RengaPyShellButtonHandler : public QObject, public Renga::ActionEventHandler {
    Q_OBJECT

public:
    RengaPyShellButtonHandler(Renga::IActionPtr action);

    void OnTriggered() override;
    void OnToggled(bool checked) override;

signals:
    void buttonClicked();
};

#endif //RENGA_PY_SHELL_RENGAPYSHELLBUTTONHANDLER_H
