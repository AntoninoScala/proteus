# SRCDIR is set in makefile or on the compile line
INCDIRS := -I . -I $(SRCDIR)/prep

########################################################################
# Compiler flags for Linux operating system on 64bit x86 CPU
#
ifeq ($(MACHINE)-$(OS),x86_64-linux-gnu)
#
# ***NOTE*** User must select between various Linux setups
#            by commenting/uncommenting the appropriate compiler
#
compiler=gnu
#compiler=g95
#compiler=intel
#compiler=intel-ND
#compiler=intel-lonestar
#compiler=cray_xt3
#compiler=cray_xt4
#compiler=cray_xt5
#compiler=pgi
#compiler=pgi-ranger
#compiler=diamond
#compiler=kraken
#compiler=utils
#
#
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
  $(warning (INFO) Corresponding compilers and flags found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# jgf45.12 These flags work on the UNC Topsail Cluster.
# jgf: The -i-dynamic flag defers the inclusion of the library with 
# feupdateenv until run time, thus avoiding the error message:
# "feupdateenv is not implemented and will always fail"
ifeq ($(compiler),intel)
  PPFC            :=  ifort
  FC            :=  ifort
  PFC           :=  mpif90
  FFLAGS1       :=  $(INCDIRS) -O3 -FI -assume byterecl -132 -i-dynamic -xSSE4.2 -assume buffered_io
  ifeq ($(DEBUG),full)
     FFLAGS1       :=  $(INCDIRS) -g -O0 -traceback -debug -check all -i-dynamic -FI -assume byterecl -132 -DALL_TRACE -DFULL_STACK -DFLUSH_MESSAGES
  endif
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1)
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCSCA -DCMPI
  DPRE          :=  -DREAL8 -DLINUX
  ifeq ($(SWAN),enable)
     DPRE          := $(DPRE) -DADCSWAN
  endif
  IMODS         :=  -I
  CC            := icc
  CCBE		:= $(CC)
  CFLAGS        := $(INCDIRS) -O3 -xSSE4.2 -m64 -mcmodel=medium -DLINUX
  ifeq ($(DEBUG),full)
     CFLAGS        := $(INCDIRS) -g -O0 -march=k8 -m64 -mcmodel=medium -DLINUX
  endif
  CLIBS         :=
  FLIBS          :=
  MSGLIBS       :=
  ifeq ($(NETCDF),enable)
     ifeq ($(MACHINENAME),blueridge)
        FLIBS       := $(FLIBS) -L$(HDF5HOME) -lhdf5  
#        NETCDFHOME  :=/shared/apps/RHEL-5/x86_64/NetCDF/netcdf-4.1.1-gcc4.1-ifort
        NETCDFHOME  :=/shared/apps/RHEL-5/x86_64/NetCDF/netcdf-4.1.2-gcc4.1-ifort
        FLIBS          := $(FLIBS) -lnetcdff
     else
        FLIBS          := $(FLIBS) -L$(HDF5HOME) -lhdf5 -lhdf5_fortran
     endif
  endif
  #jgf20110519: For netcdf on topsail at UNC, use
  #NETCDFHOME=/ifs1/apps/netcdf/
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# Corbitt 120322:  These flags work on the Notre Dame Athos & Zas
ifeq ($(compiler),intel-ND)
  PPFC            :=  ifort
  FC            :=  ifort
  PFC           :=  mpif90
  FFLAGS1       :=  $(INCDIRS) -w -O3 -xSSE4.2 -assume byterecl -132 -i-dynamic -assume buffered_io
  ifeq ($(DEBUG),full)
     FFLAGS1       :=  $(INCDIRS) -g -O0 -traceback -debug -check all -i-dynamic -FI -assume byterecl -132 -DALL_TRACE -DFULL_STACK -DFLUSH_MESSAGES
  endif
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1)
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCSCA -DCMPI -DPOWELL
  DPRE          :=  -DREAL8 -DLINUX -DADCSWAN
  ifeq ($(SWAN),enable)
     DPRE          := $(DPRE) -DADCSWAN
  endif
  IMODS         :=  -I
  CC            := icc
  CCBE          := $(CC)
  CFLAGS        := $(INCDIRS) -O3 -xSSE4.2 -m64 -mcmodel=medium -DLINUX
  FLIBS          :=
  ifeq ($(DEBUG),full)
     CFLAGS        := $(INCDIRS) -g -O0 -march=k8 -m64 -mcmodel=medium -DLINUX
  endif
  ifeq ($(NETCDF),enable)
     #HDF5HOME=/afs/crc.nd.edu/x86_64_linux/hdf/hdf5-1.8.6-linux-x86_64-static/lib
     FLIBS      := $(FLIBS) -lnetcdff -L$(HDF5HOME) 
  endif   
  CLIBS         :=
  MSGLIBS       :=
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
  #NETCDFHOME=/afs/crc.nd.edu/x86_64_linux/scilib/netcdf/4.1.2/intel-12.0/inst
endif
#
# sb46.50.02 These flags work on the UT Austin Lonstar cluster.
ifeq ($(compiler),intel-lonestar)
  PPFC            :=  ifort
  FC            :=  ifort
  PFC           :=  mpif90
#  FFLAGS1       :=  $(INCDIRS) -O3 -xT -132 -DNUVMAX -DNPRMAX -DNWVMAX
  FFLAGS1       :=  $(INCDIRS) -O3 -xT -132
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1)
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCSCA -DCMPI
  DPRE          :=  -DREAL8 -DLINUX
  IMODS         :=  -I
  CC            := icc
  CCBE		:= $(CC)
  CFLAGS        := $(INCDIRS) -O3 -xT
  CLIBS         :=
  FLIBS          :=
  MSGLIBS       :=
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# Cray-XT3 using standard compilers, from vjp; added by jgf46.00
ifeq ($(compiler),cray_xt3)
  PPFC	        :=  pgf90
  FC	        :=  ftn
  PFC	        :=  ftn
  CC		:=  pgcc
  CCBE		:=  cc
  FFLAGS1	:=  $(INCDIRS) -fastsse -Mextend
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1) -r8 -Mr8 -Mr8intrinsics
  DA  	        :=  -DREAL8 -DLINUX -DCSCA
  DP  	        :=  -DREAL8 -DLINUX -DCMPI -DHAVE_MPI_MOD -DCSCA -DDEBUG_WARN_ELEV
#  DP  	        :=  -DREAL8 -DLINUX -DCMPI -DHAVE_MPI_MOD -DCSCA
  DPRE	        :=  -DREAL8 -DLINUX
  CFLAGS	:=  -c89 $(INCDIRS) -DLINUX
  IMODS		:=  -module
  FLIBS  	:=
  MSGLIBS	:=
# When compiling with netCDF support, the HDF5 libraries must also
# be linked in, so the user must specify HDF5HOME on the command line.
# jgf20101102: on Sapphire,
#              NETCDFHOME=/usr/local/usp/PETtools/CE/pkgs/netcdf-4.1.1-serial
#              HDF5HOME=${PET_HOME}/pkgs/hdf5-1.8.5-serial/lib
  ifeq ($(NETCDF),enable)
     FLIBS          := $(FLIBS) -L$(HDF5HOME) -lhdf5_fortran -lhdf5_hl -lhdf5 -lz
  endif
  BACKEND_EXEC  := metis_be adcprep_be
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# Cray-XT4 (e.g. Jade@ERDC) using standard compilers, added by jgf48.4607
ifeq ($(compiler),cray_xt4)
  PPFC	        :=  pgf90
  FC	        :=  ftn
  PFC	        :=  ftn
  CC		:=  pgcc
  CCBE		:=  cc
  FFLAGS1	:=  $(INCDIRS) -Mextend -Minform,inform -O2 -fastsse
  ifeq ($(DEBUG),full)
     FFLAGS1	:=  $(INCDIRS) -Mextend -g -O0 -traceback -Mbounds -Mchkfpstk -Mchkptr -Mchkstk -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK
  endif
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1) -r8 -Mr8 -Mr8intrinsics
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
# When compiling with netCDF support, the HDF5 libraries must also
# be linked in, so the user must specify HDF5HOME on the command line.
# On Jade, HDF5 was compiled with szip compression, so this library is
# required as well.
# jgf20101102: on Jade, NETCDFHOME=/usr/local/usp/PETtools/CE/pkgs/netcdf-4.0.1-serial
# jgf20101102: on Jade, HDF5HOME=${PET_HOME}/pkgs/hdf5-1.8.4-serial/lib
# jgf20101103: on Jade, SZIPHOME=/usr/local/usp/PETtools/CE/pkgs/szip-2.1/lib
# jgf20110728: on Garnet, NETCDFHOME=/opt/cray/netcdf/4.1.1.0/netcdf-pgi
  ifeq ($(NETCDF),enable)
     FLIBS          := $(FLIBS) -L$(HDF5HOME) -L$(SZIPHOME) -lhdf5_fortran -lhdf5_hl -lhdf5 -lsz -lz
  endif
  MSGLIBS	:=
  BACKEND_EXEC  := metis_be adcprep_be
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#

# Portland Group
ifeq ($(compiler),pgi)
  PPFC		:=  pgf90
  FC		:=  pgf90
  PFC		:=  mpif90
  FFLAGS1	:=  $(INCDIRS) -fastsse -mcmodel=medium -Mextend
  FFLAGS2	:=  $(FFLAGS1)
  FFLAGS3	:=  $(FFLAGS1)
  DA		:=  -DREAL8 -DLINUX -DCSCA
  DP		:=  -DREAL8 -DLINUX -DCSCA -DCMPI
  DPRE		:=  -DREAL8 -DLINUX
  IMODS		:=  -I
  CC		:= gcc
  CCBE          := $(CC)
  CFLAGS	:= $(INCDIRS) -O2 -mcmodel=medium -DLINUX
  CLIBS		:=
  FLIBS  	:=
  MSGLIBS	:=
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# Utility Server (e.g. US@ERDC) using standard compilers, added by jgf48.4607
ifeq ($(compiler),utils)
  PPFC          :=  pgf90
  FC            :=  pgf90
  PFC           :=  mpif90
  CC            :=  pgcc
  CCBE          :=  pgcc
  FFLAGS1       :=  $(INCDIRS) -Mextend -Minform,inform -O2 -fastsse
  ifeq ($(DEBUG),full)
     FFLAGS1    :=  $(INCDIRS) -Mextend -g -O0 -traceback -Mbounds -Mchkfpstk -Mchkptr -Mchkstk -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK
  endif
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1) -r8 -Mr8 -Mr8intrinsics
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCMPI -DHAVE_MPI_MOD -DCSCA
  DPRE          :=  -DREAL8 -DLINUX
  ifeq ($(SWAN),enable)
     DPRE               :=  -DREAL8 -DLINUX -DADCSWAN
  endif
  CFLAGS        :=  -c89 $(INCDIRS) -DLINUX
  ifeq ($(DEBUG),full)
     CFLAGS     :=  -c89 $(INCDIRS) -DLINUX -g -O0
  endif
  IMODS         :=  -module
  FLIBS         :=
# When compiling with netCDF support, the HDF5 libraries must also
# be linked in, so the user must specify HDF5HOME on the command line.
# On Jade, HDF5 was compiled with szip compression, so this library is
# required as well.
# jgf20101102: on Jade, NETCDFHOME=/usr/local/usp/PETtools/CE/pkgs/netcdf-4.0.1-serial
# jgf20101102: on Jade, HDF5HOME=${PET_HOME}/pkgs/hdf5-1.8.4-serial/lib
# jgf20101103: on Jade, SZIPHOME=/usr/local/usp/PETtools/CE/pkgs/szip-2.1/lib
# jgf20110728: on Garnet, NETCDFHOME=/opt/cray/netcdf/4.1.1.0/netcdf-pgi
  ifeq ($(NETCDF),enable)
     FLIBS          := $(FLIBS) -L$(HDF5HOME) -L$(SZIPHOME) -lhdf5_fortran -lhdf5_hl -lhdf5 -lsz -lz
  endif
  MSGLIBS       :=
  BACKEND_EXEC  := metis_be adcprep_be
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
# Portland Group on TU Ranger (AMD Opteron 8356, Barcelona Core)  Seizo
ifeq ($(compiler),pgi-ranger)
  PPFC          :=  pgf95
  FC            :=  pgf95
  PFC           :=  mpif90
  FFLAGS1       :=  $(INCDIRS) -fast -tp barcelona-64 -Mextend
  ifeq ($(DEBUG),full)
     FFLAGS1	:=  $(INCDIRS) -Minform,inform -Mextend -g -O0 -traceback -DNETCDF_DEBUG -Mbounds -Mchkfpstk -Mchkptr -Mchkstk -DALL_TRACE -DFLUSH_MESSAGES -DFULL_STACK
  endif
  FFLAGS2       :=  $(FFLAGS1)
  FFLAGS3       :=  $(FFLAGS1)
  DA            :=  -DREAL8 -DLINUX -DCSCA
  DP            :=  -DREAL8 -DLINUX -DCSCA -DCMPI
  DPRE          :=  -DREAL8 -DLINUX
  IMODS         :=  -I
  CC            := gcc
  CCBE          := $(CC)
  CFLAGS        := $(INCDIRS) -DLINUX
  CLIBS         :=
  LIBS          :=
  MSGLIBS       :=
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# ERDC Diamond
ifeq ($(compiler),diamond)
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
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
# Cray-XE6 (e.g., Garnet at ERDC) using standard compilers, added by jgf50.29
ifeq ($(compiler),garnet)
  PPFC	        :=  pgf90
  FC	        :=  ftn
  PFC	        :=  ftn
  CC		:=  pgcc
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
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif
#
#

endif


########################################################################
# Darwin i386-apple-darwin using intel --- Mountain Lion 
#
# ... changed by Matt M. 2/26/2013
ifeq ($(PROTEUS_ARCH),darwinclang)
  PPFC	        := gfortran
  FC	        := gfortran
  PFC	        := mpif77
  FFLAGS1       :=  $(INCDIRS) -O3 -ffixed-line-length-132 -DLINUX -DNETCDF_DEBUG -I .
  FFLAGS2	:=  $(INCDIRS) -O3 -ffixed-line-length-132 -I .
  FFLAGS3	:=  $(INCDIRS) -O3 -ffixed-line-length-132 -I .
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
  $(warning (INFO) Corresponding machine found in cmplrflags.mk.)
  ifneq ($(FOUND),TRUE)
     FOUND := TRUE
  else
     MULTIPLE := TRUE
  endif
endif

