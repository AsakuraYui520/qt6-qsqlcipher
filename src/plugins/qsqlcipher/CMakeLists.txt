# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QSQLCipherDriverPlugin Plugin:
#####################################################################

if(QT_FEATURE_static)
    set(qsqlcipher_plugin_name "QSQLiteDriverPlugin")
    set(qsqlcipher_output_name "qsqlite")
    add_definitions(-DUSE_SQLITE_PLUGIN_NAME)
else()
    set(qsqlcipher_plugin_name "QSQLCipherDriverPlugin")
    set(qsqlcipher_output_name "qsqlcipher")
endif()

qt_internal_add_plugin(${qsqlcipher_plugin_name}
    OUTPUT_NAME ${qsqlcipher_output_name}
    PLUGIN_TYPE sqldrivers
    SOURCES
        qsql_sqlite.cpp qsql_sqlite_p.h
        smain.cpp
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::SqlPrivate
)

## Scopes:
#####################################################################

qt_internal_extend_target(${qsqlcipher_plugin_name}
    LIBRARIES
        OpenSSL::SSL
        OpenSSL::Crypto
)

qt_disable_warnings(${qsqlcipher_plugin_name})


qt_internal_extend_target(${qsqlcipher_plugin_name}
    SOURCES
        ./sqlite3.c
    DEFINES
        SQLCIPHER_CRYPTO_OPENSSL
        SQLITE_TEMP_STORE=2
        SQLITE_HAS_CODEC
        SQLITE_ENABLE_COLUMN_METADATA
        SQLITE_ENABLE_FTS3
        SQLITE_ENABLE_FTS3_PARENTHESIS
        SQLITE_ENABLE_FTS4
        SQLITE_ENABLE_FTS5
        SQLITE_ENABLE_GEOPOLY
        SQLITE_ENABLE_JSON1
        SQLITE_ENABLE_MATH_FUNCTIONS
        SQLITE_ENABLE_RTREE
        SQLITE_OMIT_COMPLETE
    INCLUDE_DIRECTORIES
        ./
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION CMAKE_BUILD_TYPE STREQUAL Release
    DEFINES
        NDEBUG
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION NOT QT_FEATURE_largefile
    DEFINES
        SQLITE_DISABLE_LFS
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION QT_FEATURE_posix_fallocate
    DEFINES
        HAVE_POSIX_FALLOCATE=1
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION QNX
    DEFINES
        _QNX_SOURCE
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION UNIX
    DEFINES
        HAVE_USLEEP=1
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION INTEGRITY
    COMPILE_OPTIONS -include qplatformdefs.h
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION QT_FEATURE_dlopen
    LIBRARIES
        ${CMAKE_DL_LIBS}
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION NOT QT_FEATURE_dlopen
    DEFINES
        SQLITE_OMIT_LOAD_EXTENSION
)

qt_internal_extend_target(${qsqlcipher_plugin_name} CONDITION NOT QT_FEATURE_thread
    DEFINES
        SQLITE_THREADSAFE=0
)
