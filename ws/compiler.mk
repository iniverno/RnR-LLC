# -*- makefile -*-
# Select compiler by changing CC for your host type.

ifeq (default,$(origin CC))
  ifeq (x86-linux,$(HOST_TYPE))
    CC=gcc
  endif

  ifeq (v9-sol8-64,$(HOST_TYPE))
    CC=gcc
  endif

  ifeq (amd64-linux,$(HOST_TYPE))
    CC=gcc
  endif

  ifeq (x86-win32,$(HOST_TYPE))
    CC=/cygdrive/c/MinGW/bin/gcc
  endif
endif
