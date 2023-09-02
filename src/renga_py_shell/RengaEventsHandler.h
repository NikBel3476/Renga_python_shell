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
};

#endif //RENGA_PY_SHELL_RENGAEVENTSHANDLER_H
