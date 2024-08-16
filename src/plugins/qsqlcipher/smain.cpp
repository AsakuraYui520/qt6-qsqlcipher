// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <qsqldriverplugin.h>
#include <qstringlist.h>
#include "qsql_sqlite_p.h"

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

#ifdef USE_SQLITE_PLUGIN_NAME
#define PLUGIN_CLASS_NAME QSQLiteDriverPlugin
#else
#define PLUGIN_CLASS_NAME QSQLCipherDriverPlugin
#endif

class PLUGIN_CLASS_NAME : public QSqlDriverPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QSqlDriverFactoryInterface" FILE "sqlcipher.json")

public:
    PLUGIN_CLASS_NAME();

    QSqlDriver* create(const QString &) override;
};

PLUGIN_CLASS_NAME::PLUGIN_CLASS_NAME()
    : QSqlDriverPlugin()
{
}

QSqlDriver* PLUGIN_CLASS_NAME::create(const QString &name)
{
    if (name == "QSQLCIPHER"_L1 || name == "QSQLITE"_L1) {
        QSQLiteDriver* driver = new QSQLiteDriver();
        return driver;
    }

    return nullptr;
}

QT_END_NAMESPACE

#include "smain.moc"
