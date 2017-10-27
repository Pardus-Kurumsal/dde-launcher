#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include "../model/appslistmodel.h"
#include "global_util/calculate_util.h"

#include <QAbstractButton>
#include <QLabel>

class CategoryButton : public QAbstractButton
{
    Q_OBJECT

public:
    enum State {
        Normal,
        Hover,
        Checked,
    };

public:
    explicit CategoryButton(const AppsListModel::AppCategory category, QWidget *parent = 0);

    Q_PROPERTY(qreal titleOpacity READ titleOpacity WRITE setTitleOpacity)
    Q_PROPERTY(qreal zoomLevel READ zoomLevel WRITE setZoomLevel)

    QLabel *textLabel();

    qreal titleOpacity() const;
    void setTitleOpacity(const qreal &titleOpacity);

    qreal zoomLevel() const;
    void setZoomLevel(const qreal &zoomLevel);

public slots:
    void setChecked(bool isChecked);
    void setTextVisible(bool visible, const bool animation = false);
    AppsListModel::AppCategory category() const;

protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    void setInfoByCategory();
    void updateState(const State state);
    void updateTextColor();
    void addTextShadow();

private slots:
    void relayout();

private:
    CalculateUtil *m_calcUtil;
    State m_state = Checked;
    AppsListModel::AppCategory m_category;
    QString m_iconName;

    QLabel *m_iconLabel;
    QLabel *m_textLabel;

    QPropertyAnimation *m_opacityAnimation;
    qreal m_titleOpacity = 1;

    qreal m_zoomLevel = 1;
};

#endif // CATEGORYBUTTON_H
