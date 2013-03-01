# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Compiler flags for Garnet - ERDC's HPC syste
#
ifeq ($(PROTEUS_ARCH),garnet)

# NOTE: User must select between various Linux setups
#            by commenting/uncommenting the appropriate compiler
#compiler=intel
#compiler=gnu
compiler=pgi

ifeq ($(compiler),pgi)
  PPFC	        :=  ftn
  FC	        :=  ftn
  PFC	        :=  ftn
  CC		:=  cc
  CCBE		:=  cc
  FFLAGS1	:=  $(INCDIRS) -Mextend -Minform,inform -tp=shanghai-64 -fast
  ifeq ($(DEBUG),full)
     FFLAGS1	:=  $(INCDIRS) -Mextend -g -O0 -traceback -Mbounds -Mchkfpstk -Mchkptr -Mchkstk -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK -tp=shanghai-64
  endif
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1) #-r8 -Mr8 -Mr8intrinsics
  DA  	        :=  -DREAL8 -DLINUX -DCSCA
  DP  	        :=  -DREAL8 -DLINUX -DCMPI -DHAVE_MPI_MOD -DCSCA
  DPRE	        :=  -DREAL8 -DLINUX
  ifeq ($(SWAN),enable)
     DPRE	        :=  -DREAL8 -DLINUX -DADCSWAN
  endif
  CFLAGS	:=  -c89 $(INCDIRS) -DLINUX
  ifeq ($(DEBUG),full)
     CFLAGS	:=  -c89 $(INCDIRS) -DLINUX -g -O0
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
