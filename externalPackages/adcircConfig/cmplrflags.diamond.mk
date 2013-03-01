# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Compiler flags for Dimond - ERDC's HPC syste
#
ifeq ($(PROTEUS_ARCH),diamond)

# NOTE: User must select between various Linux setups
#            by commenting/uncommenting the appropriate compiler
compiler=intel
#compiler=gnu
#compiler=pgi

ifeq ($(compiler),intel)
  PPFC          :=  ifort
  FC            :=  ifort
  PFC           :=  ifort
  FFLAGS1       :=  $(INCDIRS) -O3 -xT -132
  ifeq ($(DEBUG),full)
     FFLAGS1	:=  $(INCDIRS) -g -O0 -debug -fpe0 -132 -traceback -check all -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK
  endif
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1)
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCSCA -DCMPI -DHAVE_MPI_MOD
  DPRE          :=  -DREAL8 -DLINUX
  ifeq ($(SWAN),enable)
     DPRE          :=  -DREAL8 -DLINUX -DADCSWAN
  endif
  IMODS         :=  -I
  CC            := icc
  CCBE          := $(CC)
  CFLAGS        := $(INCDIRS) -O3 -xT
  ifeq ($(DEBUG),full)
     CFLAGS        := $(INCDIRS) -g -O0
  endif
  CLIBS         :=
  LIBS          :=
# When compiling with netCDF support, the HDF5 libraries must also
# be linked in, so the user must specify HDF5HOME on the command line.
# jgf20101103: on Diamond, NETCDFHOME=/usr/local/usp/PETtools/CE/pkgs/netcdf-4.0.1-serial
# jgf20101103: on Diamond, HDF5HOME=${PET_HOME}/pkgs/hdf5-1.8.4-serial/lib
  ifeq ($(NETCDF),enable)
     FLIBS          := $(FLIBS) -L$(HDF5HOME) -lhdf5_hl -lhdf5 -lhdf5_fortran -lz
  endif
  MSGLIBS       := -lmpi
  $(warning (INFO) Corresponding machine found in cmplrflags.mk ==> $(PROTEUS_ARCH).)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#

endif

########################################################################
ifneq ($(FOUND), TRUE)
     $(warning (WARNING) None of the archtectures found in cmplrflags.mk match your platform. As a result, the specific compilers and flags that are appropriate for you could not be specified. Please edit the cmplrflags.$(PROTEUS_ARCH).mk file to include your machine and operating system. Continuing with generic selections for compilers.)
  PPFC	        := $(FC)
  FC	        := $(FC)
  PFC	        := mpif90
  FFLAGS1	:=  $(INCDIRS)
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA  	   	:=  -DREAL8 -DCSCA -DLINUX
  DP  	   	:=  -DREAL8 -DCSCA -DLINUX -DCMPI
  DPRE	   	:=  -DREAL8 -DLINUX
  IMODS  	:=  -I
  CC            :=  cc
  CCBE          :=  $(CC)
  CFLAGS        :=  $(INCDIRS) -DLINUX
  LDFLAGS	:=
  FLIBS	        :=
  MSGLIBS	:=
endif
ifeq ($(MULTIPLE),TRUE)
     $(warning (WARNING) More than one match in cmplrflags.mk. This may result in the wrong compilers being selected. Please check the cmplrflags.mk file to ensure that only one set of compiler flags is specified for your platform.)
endif

