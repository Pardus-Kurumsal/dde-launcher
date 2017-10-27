#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "gradientlabel.h"
#include "searchwidget.h"
#include "navigationwidget.h"
#include "categorytitlewidget.h"
#include "launcherinterface.h"
#include "delegate/appitemdelegate.h"
#include "global_util/util.h"
#include "global_util/calculate_util.h"
#include "global_util/constants.h"
#include "model/appsmanager.h"
#include "model/appslistmodel.h"
#include "view/appgridview.h"
#include "worker/menuworker.h"
#include "dbusinterface/dbusdisplay.h"
#include "widgets/applistarea.h"
#include "boxframe/boxframe.h"

#include <memory>

#include <QFrame>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QSettings>
#include <QTimer>

#include <dboxwidget.h>

DWIDGET_USE_NAMESPACE

class BackgroundManager;
class DBusLauncherService;
class SharedEventFilter;
class FullScreenFrame : public BoxFrame, public LauncherInterface
{
    Q_OBJECT
    Q_PROPERTY(int dockPosition READ dockPosition DESIGNABLE true)

public:
    explicit FullScreenFrame(QWidget *parent = 0);
    ~FullScreenFrame();

    void exit();
    void showByMode(const qlonglong mode);
    int dockPosition();

signals:
    void categoryAppNumsChanged(const AppsListModel::AppCategory category, const int appNums);
    void displayModeChanged(const int mode);
    void currentVisibleCategoryChanged(const AppsListModel::AppCategory currentVisibleCategory) const;

public slots:
    void scrollToCategory(const AppsListModel::AppCategory &category);
    void showTips(const QString &tips);
    void hideTips();

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;

private:
    void initUI();
    void initConnection();
    void initTimer();

    void uninstallApp(const QString &appKey) Q_DECL_OVERRIDE;
    void uninstallApp(const QModelIndex &context);
    void showLauncher() Q_DECL_OVERRIDE;
    void hideLauncher() Q_DECL_OVERRIDE;
    bool visible() Q_DECL_OVERRIDE;
    void moveCurrentSelectApp(const int key) Q_DECL_OVERRIDE;
    void appendToSearchEdit(const char ch) Q_DECL_OVERRIDE;
    void launchCurrentApp() Q_DECL_OVERRIDE;
    bool windowDeactiveEvent() Q_DECL_OVERRIDE;

    void updateGeometry();
    void checkCategoryVisible();
    void showPopupMenu(const QPoint &pos, const QModelIndex &context);
    void updateDisplayMode(const int mode);
    void updateCurrentVisibleCategory();
    void updatePlaceholderSize();
    void updateDockPosition();


    AppsListModel *nextCategoryModel(const AppsListModel *currentModel);
    AppsListModel *prevCategoryModel(const AppsListModel *currentModel);

private slots:
    void layoutChanged();
    void searchTextChanged(const QString &keywords);
    void ensureScrollToDest(const QVariant &value);
    void ensureItemVisible(const QModelIndex &index);
    void refershCategoryVisible(const AppsListModel::AppCategory category, const int appNums);
    void showGradient();
    void toMiniMode();
    void refreshTitleVisible();
    void refershCategoryTextVisible();
    void refershCurrentFloatTitle();

private:
    CategoryTitleWidget *categoryTitle(const AppsListModel::AppCategory category) const;
    AppGridView *categoryView(const AppsListModel::AppCategory category) const;
    AppGridView *lastVisibleView() const;

private:
    bool m_isConfirmDialogShown = false;
    bool m_refershCategoryTextVisible = false;
    int m_autoScrollStep = DLauncher::APPS_AREA_AUTO_SCROLL_STEP;
    int m_displayMode = SEARCH;
    double rightMarginRation = 1;
    AppsListModel::AppCategory m_currentCategory = AppsListModel::All;
    std::unique_ptr<MenuWorker> m_menuWorker;
    SharedEventFilter *m_eventFilter;

    BackgroundManager *m_backgroundManager;

    DBusDisplay *m_displayInter;

    CalculateUtil *m_calcUtil;
    AppsManager *m_appsManager;
    QPropertyAnimation *m_scrollAnimation;
    QWidget *m_scrollDest;
    QTimer *m_delayHideTimer;
    QTimer *m_autoScrollTimer;

    NavigationWidget *m_navigationWidget;
    QWidget *m_rightSpacing;
    DImageButton *m_miniMode;
    SearchWidget *m_searchWidget;
    AppListArea *m_appsArea;
    DVBoxWidget *m_appsVbox;

    QWidget *m_viewListPlaceholder;
    QLabel *m_tipsLabel;

    AppItemDelegate *m_appItemDelegate;
    GradientLabel* m_topGradient;
    GradientLabel* m_bottomGradient;

    AppGridView *m_allAppsView;
    AppGridView *m_internetView;
    AppGridView * m_chatView;
    AppGridView *m_musicView;
    AppGridView *m_videoView;
    AppGridView *m_graphicsView;
    AppGridView *m_gameView;
    AppGridView *m_officeView;
    AppGridView *m_readingView;
    AppGridView *m_developmentView;
    AppGridView *m_systemView;
    AppGridView *m_othersView;
    AppsListModel *m_allAppsModel;
    AppsListModel *m_searchResultModel;
    AppsListModel *m_internetModel;
    AppsListModel *m_chatModel;
    AppsListModel *m_musicModel;
    AppsListModel *m_videoModel;
    AppsListModel *m_graphicsModel;
    AppsListModel *m_gameModel;
    AppsListModel *m_officeModel;
    AppsListModel *m_readingModel;
    AppsListModel *m_developmentModel;
    AppsListModel *m_systemModel;
    AppsListModel *m_othersModel;

    CategoryTitleWidget* m_floatTitle;
    CategoryTitleWidget *m_internetTitle;
    CategoryTitleWidget *m_chatTitle;
    CategoryTitleWidget *m_musicTitle;
    CategoryTitleWidget *m_videoTitle;
    CategoryTitleWidget *m_graphicsTitle;
    CategoryTitleWidget *m_gameTitle;
    CategoryTitleWidget *m_officeTitle;
    CategoryTitleWidget *m_readingTitle;
    CategoryTitleWidget *m_developmentTitle;
    CategoryTitleWidget *m_systemTitle;
    CategoryTitleWidget *m_othersTitle;

    QVBoxLayout *m_scrollAreaLayout;
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_contentLayout;
    QVBoxLayout *m_rightLayout;
};

#endif // MAINFRAME_H
