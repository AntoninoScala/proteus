# $Id: cmplrflags.mk 943 2010-01-29 15:32:02Z vparr $
########################################################################
#Convert LOCAL_LIBRARY to EXPANDED_LOCAL_LIB
########################################################################

EXPANDED_LOCAL_LIB := $(subst :, ,   $(LOCAL_LIBRARY))
EXPANDED_LOCAL_LIB := $(strip        $(EXPANDED_LOCAL_LIB))
EXPANDED_LOCAL_LIB := $(foreach dir, $(EXPANDED_LOCAL_LIB), -L$(dir))
EXPANDED_LOCAL_LIB := $(subst //,/,  $(EXPANDED_LOCAL_LIB))

########################################################################
#Convert LOCAL_INCLUDE to EXPANDED_LOCAL_INC
########################################################################

EXPANDED_LOCAL_INC := $(subst :, ,      $(LOCAL_INCLUDE))
EXPANDED_LOCAL_INC := $(strip           $(EXPANDED_LOCAL_INC))
EXPANDED_LOCAL_INC := $(foreach dir,    $(EXPANDED_LOCAL_INC), -I$(dir))
EXPANDED_LOCAL_INC := $(subst //,/,     $(EXPANDED_LOCAL_INC))

PRECISION = -DUSE_DOUBLE
DEBUG     = -DDEBUG_PRINTING

ifneq ($(TARG_COMPILER),)
  compiler := $(TARG_COMPILER)
endif

ifeq ($(TARG_METHOD),)
  TARG_METHOD := $(METHOD)
  ifeq ($(TARG_METHOD),)
    TARG_METHOD := opt
  endif
endif

OPTNAME := $(TARG_METHOD)
ifneq (,$(TARGET))
  OPTNAME := $(TARGET)
endif

ifneq (,$(findstring SEPARATE_SWEEPS,$(TARGET)))
  EXTRA_FLAGS := -DSEPARATE_SWEEPS
endif

########################################################################
# Compiler flags for Linux-Suse (Ty Hesser's Machine)
#
INCDIRS := -I . -I ${PROTEUS}/externalpackages/adcirc/prep

ifeq ($(PROTEUS_ARCH),linux-suse)

  # Default compiler if none provided in command line
  ifeq ($(compiler),)
    compiler 	:= gcc
  endif

  ifeq ($(compiler),intel)
    CC	        :=  icc
    FC	        :=  ifort
    PFC	        :=  mpif90

    OPTLVL      := -O2 #-axT
    ifeq ($(TARG_METHOD),dbg)
      OPTLVL    := -g -traceback -DSTW_DEBUG
    endif
    ifeq ($(TARG_METHOD),mdbg)
      OPTLVL    := -g -traceback -CB -check uninit -fpe0 -DSTW_DEBUG
    endif
    COMMON_FLGS := $(OPTLVL) -FR $(PRECISION)  $(EXTRA_FLAGS)
    FFLAGS1	:= $(COMMON_FLGS)
    FFLAGS2	:= $(COMMON_FLGS) -DMPI -DPARALLEL
    FFLAGS3     := $(FFLAGS1) -DMPI
    IMODS	:=  -module
    MSGLIBS	:=
    ifeq ($(USE_PERF),yes)
      PERFLIBS	:= $(EXPANDED_LOCAL_LIB) -lparaperf -lpapi -lperfctr
    endif
  endif

  ifeq ($(compiler),gcc)
    PPFC        := gfortran
    FC          := gfortran
    CC          := gcc
    CCBE        := $(CC)
    CXX		:= g++
    PFC		:= mpif90

    IMODS       := -I
    COMMON_FLGS := ${INCDIRS} -O2 -mcmodel=medium -ffixed-line-length-132 -march=k8 -m64
    FFLAGS1     := $(COMMON_FLGS) 
    FFLAGS2	:= $(COMMON_FLGS)  
    FFLAGS3     := $(FFLAGS1) 
    DA          := -DREAL8 -DLINUX -DCSCA
    DP          := -DREAL8 -DLINUX -DCSCA -DCMPI -DHAVE_MPI_MOD
    DPRE        := -DREAL8 -DLINUX
    CFLAGS      := ${INCDIRS} -O2 -mcmodel=medium -DLINUX -march=k8 -m64
    CLIBS       :=
    LIBS        :=
    MSGLIBS     :=
  endif	
endif
