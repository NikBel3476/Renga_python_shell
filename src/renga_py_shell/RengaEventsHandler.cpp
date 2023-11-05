#include "RengaEventsHandler.h"
#include "ShellWidget.h"

RengaEventsHandler::RengaEventsHandler(Renga::IApplicationPtr app) :
    Renga::ApplicationEventHandler(app) {

}

void RengaEventsHandler::OnApplicationClose(Renga::IApplicationCloseEvent *event) {

}

void RengaEventsHandler::OnProjectClose(Renga::IProjectCloseEvent *event) {
    emit projectAboutToClose();
}
