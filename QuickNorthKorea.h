#pragma once

#include <QtWidgets/QWidget>
#include "ui_QuickNorthKorea.h"
#include <QLabel>
#include <QSoundEffect>
#include <QMovie>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class QuickNorthKorea : public QWidget
{
    Q_OBJECT

public:
    QuickNorthKorea(QWidget *parent = nullptr);
    ~QuickNorthKorea();

private:
    Ui::QuickNorthKoreaClass ui;

    // Rects
    // 获取屏幕大小
    QRect desktop;

    // PropertyAnimation
    QPropertyAnimation* FullScreenWidgetShowAnimation; // 全屏窗口显示动画
    QPropertyAnimation* FullScreenWidgetWaitAnimation; // 全屏窗口等待动画
    QPropertyAnimation* FullScreenWidgetHideAnimation; // 全屏窗口隐藏动画
    QPropertyAnimation* FullScreenSpeechLabelShowAnimation; // 演讲画面显示动画
    QPropertyAnimation* WindowShowAnimation; // 窗口显示动画

    // SequentialAnimationGroup
    QSequentialAnimationGroup* FullScreenWidgetShowAnimationGroup; // 全屏窗口显示动画组

    // Widgets
    QWidget* FullScreenWidget; // 全屏窗口

    // SystemTrayIcon
    QSystemTrayIcon* trayIcon; // 系统托盘图标

    // Labels
    QLabel* FullScreenNationalFlagLabel; // 全屏国家旗帜
    QLabel* FullScreenSpeechUnderlyingLabel; // 演讲画面背景
    QLabel* FullScreenSpeechLabel; // 演讲画面
    QLabel* FullScreenDisclaimerLabel; // 全屏画面免责声明
    QLabel* NationalFlagLabel; // 国家旗帜
    QLabel* DisclaimerLabel; // 免责声明

    // Sounds
    QSoundEffect* SpeechSoundEffect; // 演讲声音
    QSoundEffect* BgmSoundEffect; // 背景音乐

    // Movies
    QMovie* SpeechMovie; // 演讲画面
};
