Her//================================================================================================
//   Copyright (c)   Messerli Informatik AG, CH-8957 Spreitenbach
//================================================================================================
//
//   Versionsinformationen für HerrmannUhr
//
//================================================================================================
// Nachfolgend Dateiformatdefinition für BuildNoExt.exe ! Nicht entfernen !
// BuildNoFileType: 3
//================================================================================================

#pragma once

#include "VersionMajor.h"
#include "BuildCounterUsage.h"

//================================================================================================
// #defines für Versionsinfo-Block              |<
//================================================================================================
#define VERSINFO_HERRMANNUHR_MAJOR VERSINFO_PROGRAM_MAJOR
#define VERSINFO_HERRMANNUHR_MAJOR_STR _MAKESTRING_(VERSINFO_HERRMANNUHR_MAJOR)
#define VERSINFO_HERRMANNUHR_MAJOR_REV VERSINFO_PROGRAM_MAJOR_REV
#define VERSINFO_HERRMANNUHR_MAJOR_REV_STR _MAKESTRING_(VERSINFO_HERRMANNUHR_MAJOR_REV)
#define VERSINFO_HERRMANNUHR_MAJOR_REV_ALIAS VERSINFO_PROGRAM_MAJOR_REV_ALIAS
#define VERSINFO_HERRMANNUHR_MINOR 1
#define VERSINFO_HERRMANNUHR_MINOR_STR _MAKESTRING_(VERSINFO_HERRMANNUHR_MINOR)

#ifndef VERSINFO_BUILD_COUNT
#define VERSINFO_HERRMANNUHR_MINOR_REV 1738
#define VERSINFO_HERRMANNUHR_MINOR_REV_STR _MAKESTRING_(VERSINFO_HERRMANNUHR_MINOR_REV)
#define VERSINFO_HERRMANNUHR_BUILD_DATE 1331307129 // 09.03.2012 16:32
#define VERSINFO_HERRMANNUHR_BUILD_DATE_STR "09.03.2012 16:32"
#else
#define VERSINFO_HERRMANNUHR_MINOR_REV VERSINFO_BUILD_COUNT
#define VERSINFO_HERRMANNUHR_MINOR_REV_STR _MAKESTRING_(VERSINFO_HERRMANNUHR_MINOR_REV)
#define VERSINFO_HERRMANNUHR_BUILD_DATE VERSINFO_BUILD_DATE
#define VERSINFO_HERRMANNUHR_BUILD_DATE_STR VERSINFO_BUILD_DATE_STR
#endif

#define VERSINFO_HERRMANNUHR_FILEDESCRIPTION "Eine Wanduhr mit Linien gezeichnet\0"
#define VERSINFO_HERRMANNUHR_INTERNALNAME "HerrmannUhr\0"
#define VERSINFO_HERRMANNUHR_ORIGINALFILENAME "HerrmannUhr.dll\0"
#define VERSINFO_HERRMANNUHR_PRODUCTNAME "HerrmannUhr\0"
#define VERSINFO_HERRMANNUHR_COMMENTS "HerrmannUhr.dll Version: " VERSINFO_HERRMANNUHR_MAJOR_STR "." VERSINFO_HERRMANNUHR_MAJOR_REV_ALIAS "." VERSINFO_HERRMANNUHR_MINOR_STR " Build: " VERSINFO_HERRMANNUHR_MINOR_REV_STR " (" PROGRAM_VERSION_INTERNALNAME ") vom " VERSINFO_HERRMANNUHR_BUILD_DATE_STR

//================================================================================================
// #defines für Programm aus Kompatibilitätsgründen
//================================================================================================
#ifndef BUILD_NO
#define BUILD_NO VERSINFO_HERRMANNUHR_MINOR_REV
#define BUILD_NO_STR VERSINFO_HERRMANNUHR_MINOR_REV_STR

#define BUILD_DATE VERSINFO_HERRMANNUHR_BUILD_DATE
#define BUILD_DATE_STR VERSINFO_HERRMANNUHR_BUILD_DATE_STR
#define PROGRAM_VERSION VERSINFO_HERRMANNUHR_MAJOR_STR "." VERSINFO_HERRMANNUHR_MAJOR_REV_ALIAS "." VERSINFO_HERRMANNUHR_MINOR_STR
#else
#define HERRMANNUHR_PROGRAM_VERSION VERSINFO_HERRMANNUHR_MAJOR_STR "." VERSINFO_HERRMANNUHR_MAJOR_REV_STR "." VERSINFO_HERRMANNUHR_MINOR_STR "." VERSINFO_HERRMANNUHR_MINOR_REV_STR
#define HERRMANNUHR_PROGRAM_VERSION_MS ((DWORD)MAKELONG(VERSINFO_HERRMANNUHR_MAJOR_REV, VERSINFO_HERRMANNUHR_MAJOR))
#define HERRMANNUHR_PROGRAM_VERSION_LS ((DWORD)MAKELONG(VERSINFO_HERRMANNUHR_MINOR_REV, VERSINFO_HERRMANNUHR_MINOR))
#endif
