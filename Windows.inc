!ifndef _MAKEFILE_INC_

_MAKEFILE_INC_ = 1

!if ( "$(TARGET_CPU)" == "X86" ) || ( "$(TARGET_CPU)" == "x86" )
CPU = i386
!elseif ( "$(TARGET_CPU)" == "X64" ) || ( "$(TARGET_CPU)" == "x64" )
CPU = AMD64
!else
CPU = $(PROCESSOR_ARCHITECTURE)
!endif

###############################################################################

!if "$(TARGET_OS)" == ""
TARGET_OS = 5.02
!endif

###############################################################################

!if "$(TARGET_OS)" == "5.0"
WINVER = 0x0500
!elseif "$(TARGET_OS)" == "5.01"
WINVER = 0x0501
!elseif "$(TARGET_OS)" == "5.02"
WINVER = 0x0502
!elseif "$(TARGET_OS)" == "6.0"
WINVER = 0x0600
!endif

###############################################################################

CC = icl /nologo /Qstd=c99
LINK = xilink /nologo
AR = xilib /nologo

###############################################################################

CFLAGS = /c /DCRTAPI1=_cdecl /DCRTAPI2=_cdecl /GS /D_WINNT /D_WIN32_WINNT=$(WINVER) /DNTDDI_VERSION=$(WINVER)0000 /DWINVER=$(WINVER) /DWIN32 /D_WIN32
LFLAGS = /INCREMENTAL:NO

!if "$(CPU)" == "i386"
CFLAGS = $(CFLAGS) /D_X86_=1
!elseif "$(CPU)" == "AMD64"
CFLAGS = $(CFLAGS) /D_AMD64_=1 /DWIN64 /D_WIN64
!endif

!ifdef DEBUG
CFLAGS = $(CFLAGS) /Zi /Od /DDEBUG /MDd
LFLAGS = $(LFLAGS) /DEBUG
DLL_LFLAGS = $(LFLAGS) /LDd
!else
CFLAGS = $(CFLAGS) /Ox /DNDEBUG /MD
LFLAGS = $(LFLAGS) /RELEASE
DLL_LFLAGS = $(LFLAGS) /LD

!endif

!endif # _MAKEFILE_INC_

# vim: noexpandtab:ts=4:sw=4:ft=make:
