# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

find_package(OpenSSL REQUIRED)

include(.cmake.conf)
project(QSQLCipherDriverPlugins
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt SQLCipher driver Plugin"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C ASM
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Sql)

qt_internal_project_setup()

if(NOT TARGET Qt::Sql)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Sql\" is not met.")
    return()
endif()
qt_build_repo()
