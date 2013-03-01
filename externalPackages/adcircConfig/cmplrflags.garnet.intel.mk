# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Compiler flags for Garnet - ERDC's HPC syste
#
ifeq ($(PROTEUS_ARCH),garnet)

# NOTE: User must select between various Linux setups
#            by commenting/uncommenting the appropriate compiler
compiler=intel
#compiler=gnu
#compiler=pgi

ifeq ($(compiler),intel)
  PPFC	        :=  ftn
  FC	        :=  ftn
  PFC	        :=  ftn
  CC		:=  cc
  CCBE		:=  cc

  ifeq ($(DEBUG),full)
     FFLAGS1	:=  $(INCDIRS) -g -O0 -debug -fpe0 -132 -traceback -check all -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK
  else
     FFLAGS1	:=  $(INCDIRS) -O3 -xT -132
  endif
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA  	        :=  -DREAL8 -DLINUX -DCSCA
  DP  	        :=  -DREAL8 -DLINUX -DCMPI -DHAVE_MPI_MOD -DCSCA

  ifeq ($(SWAN),enable)
     DPRE	:=  -DREAL8 -DLINUX -DADCSWAN
  else
     DPRE	:=  -DREAL8 -DLINUX
  endif

  ifeq ($(DEBUG),full)
     CFLAGS	:=  $(INCDIRS) -g -O0
  else
    CFLAGS	:=  $(INCDIRS) -O3 -xT
  endif
  IMODS		:=  -module
  FLIBS  	:=
# jgf20110728: on Garnet, NETCDFHOME=/opt/cray/netcdf/4.1.1.0/netcdf-pgi
# jgf20110815: on Garnet, HDF5HOME=/opt/cray/hdf5/default/hdf5-pgi
  ifeq ($(NETCDF),enable)
     NETCDFHOME=/opt/cray/netcdf/4.1.1.0/netcdf-pgi
     HDF5HOME=/opt/cray/hdf5/1.8.5.0/hdf5-pgi
     FLIBS          := $(FLIBS) -lnetcdff -L$(HDF5HOME)/lib -L$(NETCDFHOME) -lnetcdf -lhdf5_hl -lhdf5 -lhdf5_fortran -lz
  endif
  MSGLIBS	:=
  BACKEND_EXEC  := metis_be adcprep_be
  $(warning (INFO) Corresponding machine found in cmplrflags.mk ==> $(PROTEUS_ARCH).)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif

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
