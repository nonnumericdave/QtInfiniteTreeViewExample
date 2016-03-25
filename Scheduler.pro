TEMPLATE = app
CONFIG += precompile_header
QT += widgets
PRECOMPILED_HEADER = stdafx.h

HEADERS += \
    CalendarWidget.h \
    CalendarWidgetDelegate.h \
    InfiniteController.h \
    InfiniteModel.h \
    InfiniteModelIndex.h \
    InfiniteTreeView.h \
    MainWindow.h \
    SchedulerController.h \
    SchedulerModel.h \
    SchedulerModelIndex.h \
    stdafx.h \

SOURCES += \
    CalendarWidget.cpp \
    InfiniteTreeView.cpp \
    main.cpp \
    MainWindow.cpp \
    SchedulerController.cpp \
    SchedulerModel.cpp \
    SchedulerModelIndex.cpp \
    stdafx.cpp \

FORMS += \
    MainWindow.ui \

RESOURCES +=
