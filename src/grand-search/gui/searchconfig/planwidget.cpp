/*
 * Copyright (C) 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     wangchunlin<wangchunlin@uniontech.com>
 *
 * Maintainer: wangchunlin<wangchunlin@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "planwidget.h"
#include "business/config/searchconfig.h"
#include "global/builtinsearch.h"
#include "global/searchconfigdefine.h"
#include "switchwidget/switchwidget.h"

#include <DFontSizeManager>

#include <QLabel>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE
using namespace GrandSearch;

PlanWidget::PlanWidget(QWidget *parent)
    : DWidget(parent)
{
    m_groupLabel = new QLabel(tr("Search experience program"), this);
    DFontSizeManager::instance()->bind(m_groupLabel, DFontSizeManager::T5, QFont::Bold);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_groupLabel);

    QString display = QObject::tr("Join search experience program");
    QString iconName("experienceplan");
    QIcon icon = QIcon(QString(":/icons/%1.svg").arg(iconName));

    bool enable = SearchConfig::instance()->getConfig(GRANDSEARCH_PLAN_GROUP, GRANDSEARCH_PLAN_EXPERIENCE, true).toBool();
    SwitchWidget *switchWidget = new SwitchWidget(this);
    switchWidget->setFixedSize(SWITCHWIDGETWIDTH, SWITCHWIDGETHEIGHT);
    switchWidget->setEnableBackground(true);
    switchWidget->setIcon(icon, QSize(SWITCHWIDGETICONSIZE, SWITCHWIDGETICONSIZE));
    switchWidget->setTitle(display);
    switchWidget->setChecked(enable);
    m_mainLayout->addWidget(switchWidget);
    switchWidget->setProperty(GRANDSEARCH_SEARCH_GROUP, GRANDSEARCH_PLAN_EXPERIENCE);

    QString content = QObject::tr("Joining the search experience program means that "
                                  "you grant and authorize us to collect the information of "
                                  "your device and system, file icons, content and properties, "
                                  "applications and their configurations. If you refuse our collection "
                                  "and use of the aforementioned information, do not join the program.");
    m_contentLabel = new QLabel(content, this);
    m_contentLabel->setWordWrap(true);

    QString tips = QObject::tr("To know more about the management of your data, please refer to the UnionTech "
                               "Software Privacy Policy (https://www.uniontech.com/agreement/privacy-en).");
    m_tipsLabel = new QLabel(tips, this);
    m_tipsLabel->setWordWrap(true);

    m_mainLayout->addWidget(m_contentLabel);
    m_mainLayout->addWidget(m_tipsLabel);

    connect(switchWidget, &SwitchWidget::checkedChanged, this, &PlanWidget::onSwitchStateChanged);
}

PlanWidget::~PlanWidget()
{

}

void PlanWidget::onSwitchStateChanged(const bool checked)
{
    QObject *obj = sender();
    SwitchWidget *switchWidget = static_cast<SwitchWidget *>(obj);

    if (switchWidget) {
        SearchConfig::instance()->setConfig(GRANDSEARCH_PLAN_GROUP, GRANDSEARCH_PLAN_EXPERIENCE, checked);
    }
}
