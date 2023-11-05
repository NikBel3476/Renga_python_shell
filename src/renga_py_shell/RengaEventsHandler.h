#ifndef RENGA_PY_SHELL_RENGAEVENTSHANDLER_H
#define RENGA_PY_SHELL_RENGAEVENTSHANDLER_H

#include <QObject>

#include "stdafx.h"
#include <Renga/ApplicationEventHandler.hpp>

class RengaEventsHandler : public QObject, public Renga::ApplicationEventHandler
{
Q_OBJECT

public:
    RengaEventsHandler(Renga::IApplicationPtr app);

    void OnApplicationClose(Renga::IApplicationCloseEvent *event);
    void OnProjectClose(Renga::IProjectCloseEvent *event);

signals:
    void projectAboutToClose();
};

#endif //RENGA_PY_SHELL_RENGAEVENTSHANDLER_H
