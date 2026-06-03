/***************************************************************************************************
 * Copyright 2018-2026 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include <QDebug>
#include <QScreen>

#if 0 // X_ENABLE_SINGLE_APPLICATION
#include <singleapplication.h>
#endif

#if X_ENABLE_LOG
#include "x/log/log.h"
#endif

#include "application.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if X_ENABLE_LOG
    qInstallMessageHandler(xLog::Log::messageHandler);
#endif

    Application::setOrganizationName("xTools");
    Application::setApplicationName("xTools");
    Application::setupHdpi();
    Application app(argc, argv);
    app.setCustomSplashScreen(QPixmap(":/res/images/splash_screen.svg"));

#if 0 // X_ENABLE_SINGLE_APPLICATION
    SingleApplication sApp(argc, argv);
    if (sApp.isSecondary()) {
        return 0;
    }
#endif

    app.setupLanguage();
    app.showSplashScreenMessage(QObject::tr("Application is booting..."));
    app.setupAppStyle();
    app.setupColorScheme();

#if defined(Q_OS_ANDROID)
    // Increase base font for touch readability
    QFont mobileFont = app.font();
    mobileFont.setPixelSize(18);
    app.setFont(mobileFont);

    // Global stylesheet for touch-friendly controls
    app.setStyleSheet(QStringLiteral(
        "QWidget { font-size: 18px; }"
        "QPushButton { min-height: 48px; padding: 8px 16px; }"
        "QLineEdit { min-height: 40px; padding: 4px 8px; font-size: 16px; }"
        "QComboBox { min-height: 44px; padding: 4px 8px; }"
        "QSpinBox { min-height: 40px; }"
        "QDoubleSpinBox { min-height: 40px; }"
        "QCheckBox { spacing: 8px; }"
        "QCheckBox::indicator { width: 24px; height: 24px; }"
        "QRadioButton { spacing: 8px; }"
        "QRadioButton::indicator { width: 24px; height: 24px; }"
        "QTabWidget::pane { padding: 4px; }"
        "QTabBar::tab { min-height: 40px; padding: 8px 16px; font-size: 16px; }"
        "QGroupBox { padding: 16px 8px 8px 8px; margin-top: 8px; font-size: 16px; }"
        "QToolButton { min-height: 40px; padding: 4px 12px; }"
        "QMenuBar { font-size: 16px; }"
        "QMenu { font-size: 16px; }"
        "QMenu::item { padding: 8px 24px; }"
        "QLabel { font-size: 16px; }"
        "QTextEdit { font-size: 16px; }"
        "QPlainTextEdit { font-size: 16px; }"
    ));
#endif

    MainWindow window;
    QSplashScreen *splash = app.splashScreen();
    if (splash) {
        splash->finish(&window);
    }

#if defined(Q_OS_ANDROID)
    window.showMaximized();
#else
    const QSize size(1366, 768);
    window.resize(size);
    window.show();
    window.moveToCenter();
#endif
    window.load();

#if 0 // X_ENABLE_SINGLE_APPLICATION
    QObject::connect(&sApp, &SingleApplication::instanceStarted, &window, [&window]() {
        window.show();
        window.raise();
        window.activateWindow();
        QApplication::beep();
    });
#endif

    return Application::exec();
}
