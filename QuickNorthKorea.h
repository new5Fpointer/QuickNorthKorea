#pragma once

#include <QWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QLabel>
#include <QSoundEffect>
#include <QMovie>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class QuickNorthKorea : public QWidget
{
    Q_OBJECT

public:
    explicit QuickNorthKorea(QWidget* parent = nullptr);
    ~QuickNorthKorea();

private:
    // Rects
    QRect desktop;

    // PropertyAnimation
    QPropertyAnimation* FullScreenWidgetShowAnimation;
    QPropertyAnimation* FullScreenWidgetWaitAnimation;
    QPropertyAnimation* FullScreenWidgetHideAnimation;
    QPropertyAnimation* FullScreenSpeechLabelShowAnimation;
    QPropertyAnimation* WindowShowAnimation;

    // SequentialAnimationGroup
    QSequentialAnimationGroup* FullScreenWidgetShowAnimationGroup;

    // Widgets
    QWidget* FullScreenWidget;

    // SystemTrayIcon
    QSystemTrayIcon* trayIcon;

    // Labels
    QLabel* FullScreenNationalFlagLabel;
    QLabel* FullScreenSpeechUnderlyingLabel;
    QLabel* FullScreenSpeechLabel;
    QLabel* FullScreenDisclaimerLabel;
    QLabel* NationalFlagLabel;
    QLabel* DisclaimerLabel;

    // Sounds
    QSoundEffect* SpeechSoundEffect;
    QSoundEffect* BgmSoundEffect;

    // Movies
    QMovie* SpeechMovie;
};
