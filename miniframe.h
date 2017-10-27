#ifndef MINIFRAME_H
#define MINIFRAME_H

#include "launcherinterface.h"
#include "global_util/constants.h"

#include <QWidget>

#include <DPlatformWindowHandle>
#include <DWindowManagerHelper>
#include <dblureffectwidget.h>
#include <dimagebutton.h>
#include <dboxwidget.h>

#include <memory>

DWIDGET_USE_NAMESPACE

class QScrollArea;
class QListView;
class DBusDock;
class SearchWidget;
class AppsListModel;
class AppsManager;
class MiniCategoryWidget;
class MiniFrameBottomBar;
class SharedEventFilter;
class MenuWorker;
class CalculateUtil;
class MiniFrame : public DBlurEffectWidget, public LauncherInterface
{
    Q_OBJECT

public:
    explicit MiniFrame(QWidget *parent = 0);
    ~MiniFrame();

private:
    void showLauncher() Q_DECL_OVERRIDE;
    void hideLauncher() Q_DECL_OVERRIDE;
    bool visible() Q_DECL_OVERRIDE;

    void moveCurrentSelectApp(const int key) Q_DECL_OVERRIDE;
    void appendToSearchEdit(const char ch) Q_DECL_OVERRIDE;
    void launchCurrentApp() Q_DECL_OVERRIDE;
    void showPopupMenu(const QPoint &pos, const QModelIndex &context);

    void uninstallApp(const QString &appKey) Q_DECL_OVERRIDE;
    void uninstallApp(const QModelIndex &context);

    bool windowDeactiveEvent() Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;

private slots:
    void checkIndex();
    void adjustPosition();
    void reloadAppsView();
    void toggleFullScreen();
    void onToggleViewClicked();
    void onWMCompositeChanged();
    void prepareHideLauncher();
    void focusRightPanel();
    void focusLeftPanel();
    void setCurrentIndex(const QModelIndex &index);
    void searchText(const QString &text);

private:
    const QModelIndex currentIndex() const;

private:
    int m_autoScrollStep = DLauncher::APPS_AREA_AUTO_SCROLL_STEP;
    std::unique_ptr<MenuWorker> m_menuWorker;
    DPlatformWindowHandle m_windowHandle;
    DWindowManagerHelper *m_wmHelper;
    DBusDock *m_dockInter;
    SharedEventFilter *m_eventFilter;
    AppsManager *m_appsManager;
    CalculateUtil *m_calcUtil;

    QTimer *m_delayHideTimer;
    QTimer *m_autoScrollTimer;

    DImageButton *m_viewToggle;
    DImageButton *m_modeToggle;
    SearchWidget *m_searchWidget;

    MiniCategoryWidget *m_categoryWidget;
    MiniFrameBottomBar *m_bottomBar;
    QLabel *m_viewWrapper;
    QScrollArea *m_appsArea;
    DVBoxWidget *m_appsBox;

    QListView *m_appsView;
    AppsListModel *m_appsModel;
    AppsListModel *m_searchModel;
};

#endif // MINIFRAME_H
