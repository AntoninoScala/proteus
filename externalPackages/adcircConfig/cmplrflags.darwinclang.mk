# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Darwin i386-apple-darwin using intel --- Mountain Lion 
#
# ... changed by Matt M. 2/26/2013
ifeq ($(PROTEUS_ARCH),darwinclang)

# NOTE:  User must select between various setups by commenting/
#        uncommenting the approprite compiler
#compiler=clang
compiler=gnu
#compiler=intel ... to be implemented

ifeq ($(compiler),clang)
  PPFC          := gfortran
  FC            := gfortran
  PFC           := mpif77
  FFLAGS1       :=  $(INCDIRS) -O3 -ffixed-line-length-132 -DLINUX -DNETCDF_DEBUG
  FFLAGS2       :=  $(INCDIRS) -O3 -ffixed-line-length-132
  FFLAGS3       :=  $(INCDIRS) -O3 -ffixed-line-length-132
  DA            :=  -DREAL8 -DCSCA -DLINUX
  DP            :=  -DREAL8 -DCSCA -DLINUX -DCMPI -DNETCDF_DEBUG
  DPRE          :=  -DREAL8 -DLINUX
  IMODS         :=  -I
  CC            :=  clang
  CCBE          :=  $(CC)
  CFLAGS        :=  $(INCDIRS) -O3 -DLINUX
  LDFLAGS       :=
  FLIBS         :=
  MSGLIBS       :=
  $(warning (INFO) Corresponding architecture found in cmplrflags.mk. ==> $(PROTEUS_ARCH))
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif


ifeq ($(compiler),gnu)
  PPFC	        := gfortran
  FC	        := gfortran
  PFC	        := mpif77
  FFLAGS1       :=  $(INCDIRS) -O3 -ffixed-line-length-132 -DLINUX -DNETCDF_DEBUG
  FFLAGS2	:=  $(INCDIRS) -O3 -ffixed-line-length-132
  FFLAGS3	:=  $(INCDIRS) -O3 -ffixed-line-length-132 
  DA  	   	:=  -DREAL8 -DCSCA -DLINUX
  DP  	   	:=  -DREAL8 -DCSCA -DLINUX -DCMPI -DNETCDF_DEBUG
  DPRE	   	:=  -DREAL8 -DLINUX
  IMODS  	:=  -I
  CC            :=  gcc
  CCBE          :=  $(CC)
  CFLAGS        :=  $(INCDIRS) -O3 -DLINUX
  LDFLAGS	:=
  FLIBS	        :=
  MSGLIBS	:=
  $(warning (INFO) Corresponding architecture found in cmplrflags.mk. ==> $(PROTEUS_ARCH))
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

