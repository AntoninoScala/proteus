# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Compiler flags for Linux-Suse operating system on 64bit x86 CPU
#
# ... Ty Hesser's Machine
#
ifeq ($(PROTEUS_ARCH),linux-suse)
#
# NOTE: User must select between various Linux setups
#        by commenting/uncommenting the appropriate compiler
#
compiler=gnu
#compiler=g95
#compiler=intel ... to be implemented

# Compiler Flags for gfortran and gcc
ifeq ($(compiler),gnu)
  PPFC		:=  gfortran
  FC		:=  gfortran
  PFC		:=  mpif90
  FFLAGS1	:=  $(INCDIRS) -O2 -mcmodel=medium -ffixed-line-length-132 -march=k8 -m64
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA		:=  -DREAL8 -DLINUX -DCSCA
  DP		:=  -DREAL8 -DLINUX -DCSCA -DCMPI -DHAVE_MPI_MOD
  DPRE		:=  -DREAL8 -DLINUX
  IMODS 	:=  -I
  CC		:= gcc
  CCBE		:= $(CC)
  CFLAGS	:= $(INCDIRS) -O2 -mcmodel=medium -DLINUX -march=k8 -m64
  CLIBS	:=
  LIBS		:=
  MSGLIBS	:=
  $(warning (INFO) Corresponding compilers and flags found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif

#
ifeq ($(compiler),g95)
  PPFC		:=  g95
  FC		:=  g95
  PFC		:=  mpif90
  FFLAGS1	:=  $(INCDIRS) -O3 -mcmodel=medium -fstatic -ffixed-line-length-132
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA		:=  -DREAL8 -DLINUX -DCSCA
  DP		:=  -DREAL8 -DLINUX -DCSCA -DCMPI
  DPRE		:=  -DREAL8 -DLINUX
  IMODS 	:=  -I
  CC		:= gcc
  CCBE		:= $(CC)
  CFLAGS	:= $(INCDIRS) -O2 -mcmodel=medium -DLINUX
  CLIBS	:=
  FLIBS		:=
  MSGLIBS	:=
  $(warning (INFO) Corresponding compilers and flags found in cmplrflags.mk ==> $(PROTEUS_ARCH).)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif

endif

ifeq ($(PROTEUS_ARCH),linux)
#
# NOTE: User must select between various Linux setups
#        by commenting/uncommenting the appropriate compiler
#
compiler=gnu
#compiler=g95
#compiler=intel ... to be implemented

# Compiler Flags for gfortran and gcc
ifeq ($(compiler),gnu)
  PPFC		:=  gfortran
  FC		:=  gfortran
  PFC		:=  mpif90
  FFLAGS1	:=  $(INCDIRS) -O2 -mcmodel=medium -ffixed-line-length-132 -march=k8 -m64
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA		:=  -DREAL8 -DLINUX -DCSCA
  DP		:=  -DREAL8 -DLINUX -DCSCA -DCMPI -DHAVE_MPI_MOD
  DPRE		:=  -DREAL8 -DLINUX
  IMODS 	:=  -I
  CC		:= gcc
  CCBE		:= $(CC)
  CFLAGS	:= $(INCDIRS) -O2 -mcmodel=medium -DLINUX -march=k8 -m64
  CLIBS	:=
  LIBS		:=
  MSGLIBS	:=
  $(warning (INFO) Corresponding compilers and flags found in cmplrflags.mk.)
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


