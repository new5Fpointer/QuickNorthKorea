#include "QuickNorthKorea.h"

QuickNorthKorea::QuickNorthKorea(QWidget* parent)
    : QWidget(parent)
{
    desktop = QGuiApplication::primaryScreen()->geometry();
    this->setGeometry(desktop);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowTitle(QString::fromUtf8("一键恩情"));
    this->setWindowIcon(QIcon(":/QuickNorthKorea/img/QuickNorthKorea_icon.png"));
    this->setFont(QFont("Microsoft YaHei Ui", QFont::Bold));
    this->hide();

    // Sounds
    SpeechSoundEffect = new QSoundEffect();
    SpeechSoundEffect->setSource(QUrl::fromLocalFile(":/QuickNorthKorea/sounds/speech.wav"));
    SpeechSoundEffect->setLoopCount(1);
    BgmSoundEffect = new QSoundEffect();
    BgmSoundEffect->setSource(QUrl::fromLocalFile(":/QuickNorthKorea/sounds/bgm.wav"));
    BgmSoundEffect->setLoopCount(QSoundEffect::Infinite);

    // Movies
    SpeechMovie = new QMovie(":/QuickNorthKorea/img/speech.gif");
    SpeechMovie->setSpeed(114);

    // SystemTrayIcon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/QuickNorthKorea/img/QuickNorthKorea_icon.png"));
    trayIcon->setToolTip("一键恩情");
    // Actions
    QAction* ExitAction = new QAction("Stop Kim!", this);
    // Menu
    QMenu* Menu = new QMenu(this);
    Menu->addAction(ExitAction);
    trayIcon->setContextMenu(Menu);
    // Connections
    connect(ExitAction, &QAction::triggered, this, &qApp->quit);
    trayIcon->show();

    // Widgets
    FullScreenWidget = new QWidget(this);
    FullScreenWidget->setGeometry(0, 0, 0, desktop.height());
    FullScreenWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    FullScreenWidget->setAttribute(Qt::WA_TranslucentBackground);
    FullScreenWidget->setWindowTitle(QString::fromUtf8("一键恩情 - 全屏界面"));
    FullScreenWidget->setWindowIcon(QIcon(":/QuickNorthKorea/img/QuickNorthKorea_icon.png"));
    FullScreenWidget->setFont(QFont("Microsoft YaHei Ui", QFont::Bold));
    FullScreenWidget->show();

    // Labels
    FullScreenNationalFlagLabel = new QLabel(FullScreenWidget);
    FullScreenNationalFlagLabel->setPixmap(QPixmap(":/QuickNorthKorea/img/KP.png"));
    FullScreenNationalFlagLabel->setScaledContents(true);
    FullScreenNationalFlagLabel->setAlignment(Qt::AlignCenter);
    FullScreenNationalFlagLabel->show();
    FullScreenSpeechUnderlyingLabel = new QLabel(FullScreenWidget);
    FullScreenSpeechUnderlyingLabel->setGeometry(desktop);
    FullScreenSpeechUnderlyingLabel->show();
    FullScreenSpeechLabel = new QLabel(FullScreenSpeechUnderlyingLabel);
    FullScreenSpeechLabel->setGeometry(desktop);
    FullScreenSpeechLabel->setMovie(SpeechMovie);
    FullScreenSpeechLabel->setAlignment(Qt::AlignCenter);
    FullScreenSpeechLabel->setScaledContents(true);
    FullScreenSpeechLabel->show();
    FullScreenDisclaimerLabel = new QLabel("本软件仅用于娱乐，不代表制作者的任何立场。\n本软件制作者完全支持社会主义，坚持中国共产党的领导。", FullScreenWidget);
    FullScreenDisclaimerLabel->move(0, 0);
    FullScreenDisclaimerLabel->setStyleSheet("color: rgba(255, 255, 255, 0.1); font-size: " + QString::number(desktop.height() * 0.025) + "px;");
    FullScreenDisclaimerLabel->adjustSize();
    FullScreenDisclaimerLabel->show();
    NationalFlagLabel = new QLabel(this);
    NationalFlagLabel->setGeometry(desktop);
    NationalFlagLabel->setPixmap(QPixmap(":/QuickNorthKorea/img/KP.png"));
    NationalFlagLabel->setScaledContents(true);
    NationalFlagLabel->setAlignment(Qt::AlignCenter);
    NationalFlagLabel->hide();
    DisclaimerLabel = new QLabel("本软件仅用于娱乐，不代表制作者的任何立场。\n本软件制作者完全支持社会主义，坚持中国共产党的领导。", this);
    DisclaimerLabel->move(0, 0);
    DisclaimerLabel->setStyleSheet("color: rgba(255, 255, 255, 0.1); font-size: " + QString::number(desktop.height() * 0.025) + "px;");
    DisclaimerLabel->adjustSize();
    DisclaimerLabel->show();

    // PropertyAnimation
    FullScreenWidgetShowAnimation = new QPropertyAnimation(FullScreenWidget, "geometry");
    FullScreenWidgetShowAnimation->setDuration(1000);
    FullScreenWidgetShowAnimation->setStartValue(QRect(0, 0, 0, desktop.height()));
    FullScreenWidgetShowAnimation->setEndValue(desktop);
    FullScreenWidgetShowAnimation->setEasingCurve(QEasingCurve::InCubic);
    FullScreenSpeechLabelShowAnimation = new QPropertyAnimation(FullScreenSpeechUnderlyingLabel, "geometry");
    FullScreenSpeechLabelShowAnimation->setDuration(1000);
    FullScreenSpeechLabelShowAnimation->setStartValue(QRect(0, 0, 0, desktop.height()));
    FullScreenSpeechLabelShowAnimation->setEndValue(desktop);
    FullScreenSpeechLabelShowAnimation->setEasingCurve(QEasingCurve::OutCubic);
    FullScreenWidgetWaitAnimation = new QPropertyAnimation(FullScreenWidget, "windowOpacity");
    FullScreenWidgetWaitAnimation->setDuration(4250);
    FullScreenWidgetWaitAnimation->setStartValue(1);
    FullScreenWidgetWaitAnimation->setEndValue(1);
    FullScreenWidgetHideAnimation = new QPropertyAnimation(FullScreenWidget, "windowOpacity");
    FullScreenWidgetHideAnimation->setDuration(3000);
    FullScreenWidgetHideAnimation->setStartValue(1);
    FullScreenWidgetHideAnimation->setEndValue(0);
    FullScreenWidgetHideAnimation->setEasingCurve(QEasingCurve::InCubic);
    WindowShowAnimation = new QPropertyAnimation(this, "geometry");
    WindowShowAnimation->setDuration(2000);
    WindowShowAnimation->setStartValue(QRect(0, 0, desktop.width(), 0));
    WindowShowAnimation->setEndValue(desktop);
    WindowShowAnimation->setEasingCurve(QEasingCurve::InOutExpo);

    // SequentialAnimationGroup
    FullScreenWidgetShowAnimationGroup = new QSequentialAnimationGroup;
    FullScreenWidgetShowAnimationGroup->addAnimation(FullScreenWidgetShowAnimation);
    FullScreenWidgetShowAnimationGroup->addAnimation(FullScreenSpeechLabelShowAnimation);
    FullScreenWidgetShowAnimationGroup->addAnimation(FullScreenWidgetWaitAnimation);
    FullScreenWidgetShowAnimationGroup->addAnimation(FullScreenWidgetHideAnimation);
    FullScreenWidgetShowAnimationGroup->addAnimation(WindowShowAnimation);
    FullScreenWidgetShowAnimationGroup->start();

    // Connections
    connect(FullScreenWidgetShowAnimation, &QPropertyAnimation::finished, [&] {
        SpeechMovie->start();
        SpeechSoundEffect->play();
        });
    connect(FullScreenWidgetHideAnimation, &QPropertyAnimation::finished, [&] {
        this->raise();
        this->activateWindow();
        this->show();
        NationalFlagLabel->show();

        QMetaObject::invokeMethod(this, [this] {
            QRect r = QGuiApplication::primaryScreen()->geometry();
            NationalFlagLabel->setGeometry(r);
            }, Qt::QueuedConnection);

        BgmSoundEffect->play();
        });
}

QuickNorthKorea::~QuickNorthKorea()
{
}
