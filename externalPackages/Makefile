#
#to add a new package 'pkg'
#1. Add targets  config_pkg, build_pkg, install_pkg, newConfig_pkg, and editConfig_pkg and add those to the *_core_* or *_extensions_* targets
#2. Add the pristine source for a version to the externalPackages directory
#3. Set up the name of the package in versions.txt
#
include versionsConfig/versions.${PROTEUS_ARCH}

REHASH=hash

all: install pip pexpect

pip: easy_install
	${REHASH} && easy_install pip

easy_install:
	${PROTEUS_PYTHON} distribute_setup.py

pexpect:
	${REHASH} && pip install pexpect

install: install_core install_extensions

install_core: install_core_python install_core_libraries install_core_modules

install_extensions: install_extensions_libraries install_extensions_modules

distclean: 
	rm -f *_progress 
	rm -f install_*
	make -k clean_log distclean_core_python distclean_core_libraries distclean_core_modules distclean_extensions_libraries distclean_extensions_modules

newConfig: newConfig_core_python newConfig_core_libraries newConfig_core_modules newConfig_extensions_libraries newConfig_extensions_modules

versionsConfig/versions.${PROTEUS_ARCH}:
	cd versionsConfig && cp versions.${PROTEUS_ARCH_OLD} versions.${PROTEUS_ARCH}

editConfig: editConfig_core_python editConfig_core_libraries editConfig_core_modules editConfig_extensions_libraries editConfig_extensions_modules

#install
install_core_python: install_zlib install_python

install_core_libraries: install_petsc install_daetk install_szip install_hdf5 install_triangle install_tetgen install_superlu 

install_core_modules: install_numpy install_nose install_numexpr install_cython install_pytables install_mpi4py install_petsc4py

install_extensions_libraries:

install_extensions_modules: install_setuptools install_matplotlib install_stwave install_adcirc install_adh install_jasper install_grib_api install_pyproj install_pygrib install_netcdf install_netcdf4-python

#distclean
distclean_core_python: distclean_python

distclean_core_libraries: distclean_petsc distclean_daetk distclean_zlib distclean_szip distclean_hdf5 distclean_triangle distclean_tetgen distclean_superlu 

distclean_core_modules: distclean_numpy distclean_nose distclean_pytables distclean_cython distclean_mpi4py distclean_petsc4py distclean_numexpr

distclean_extensions_libraries: 

distclean_extensions_modules: distclean_setuptools distclean_readline distclean_matplotlib distclean_stwave distclean_adh distclean_adcirc distclean_jasper distclean_grib_api distclean__pyproj distclean_pygrib distclean_netcdf distclean_netcdf4-python

#newConfig
newConfig_core_python: newConfig_python

newConfig_core_libraries: newConfig_petsc newConfig_daetk newConfig_zlib newConfig_szip newConfig_hdf5 newConfig_triangle newConfig_tetgen newConfig_superlu 

newConfig_core_modules: newConfig_numpy newConfig_nose newConfig_pytables newConfig_cython newConfig_mpi4py newConfig_petsc4py

newConfig_extensions_libraries: 

newConfig_extensions_modules: newConfig_setuptools newConfig_readline newConfig_matplotlib newConfig_stwave newConfig_adcirc newConfig_adh newConfig_jasper newConfig_grib_api newConfig_pyproj newConfig_pygrib newConfig_netcdf newConfig_netcdf4-python

#editConfig
editConfig_core_python: editConfig_python
editConfig_core_libraries: editConfig_petsc editConfig_daetk editConfig_zlib editConfig_szip editConfig_hdf5 editConfig_triangle editConfig_tetgen editConfig_superlu 

editConfig_core_modules: editConfig_numpy editConfig_nose editConfig_pytables editConfig_cython editConfig_mpi4py editConfig_petsc4py

editConfig_extensions_libraries:

editConfig_extensions_modules: newConfig_setuptools newConfig_readline editConfig_matplotlib editConfig_stwave editConfig_stwave editConfig_adcirc editConfig_adh editConfig_jasper editConfig_grib_api editConfig_pyproj editConfig_pygrib editConfig_netcdf editConfig_netcdf4-python

#core
#core python
#readline
newConfig_readline:
	echo "no readline customization implemented"

editConfig_readline:
	echo "no readline customization implemented"

config_readline:
	echo "no readline customization implemented" > config_readline_progress 2>&1

build_readline:
	cd ${READLINE_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_readline_progress 2>&1

install_readline: 
	cd ${READLINE_VERSION} &&  ${PROTEUS_PYTHON} setup.py install > ../install_readline_progress 2>&1
	cat config_readline_progress build_readline_progress install_readline_progress > install_readline

distclean_readline:
	touch install_readline
	mv -f install_readline install_readline_last
	cd ${READLINE_VERSION} && make distclean

#python
newConfig_python:
	cd pythonConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_python:
	cd pythonConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_python:
	cd ${PYTHON_VERSION} && ../pythonConfig/configure.${PROTEUS_ARCH} > ../config_python_progress 2>&1

build_python:
	cd ${PYTHON_VERSION} && make > ../build_python_progress 2>&1

install_python:
	make config_python build_python
	cd ${PYTHON_VERSION} && PREFIXAPPS=${PROTEUS_PREFIX} make install > ../install_python_progress 2>&1
	cat config_python_progress build_python_progress install_python_progress > install_python
	cd ${PYTHON_VERSION} && PREFIXAPPS=${PROTEUS_PREFIX} make frameworkinstall > ../install_python_progress 2>&1

distclean_python:
	touch install_python
	mv -f install_python install_python_last
	cd ${PYTHON_VERSION} && make distclean

#core libraries
#zlib
newConfig_zlib:
	cd zlibConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_zlib:
	cd zlibConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_zlib:
	cd ${ZLIB_VERSION} && ../zlibConfig/configure.${PROTEUS_ARCH} > ../config_zlib_progress 2>&1

build_zlib:
	cd ${ZLIB_VERSION} && make > ../build_zlib_progress 2>&1

install_zlib:
	make config_zlib build_zlib
	cd ${ZLIB_VERSION} && make install > ../install_zlib_progress 2>&1
	cat config_zlib_progress build_zlib_progress install_zlib_progress > install_zlib

distclean_zlib:
	touch install_zlib
	mv -f install_zlib install_zlib_last
	cd ${ZLIB_VERSION} && make distclean

#szip
newConfig_szip:
	cd szipConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_szip:
	cd szipConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_szip:
	cd ${SZIP_VERSION} && ../szipConfig/configure.${PROTEUS_ARCH} > ../config_szip_progress 2>&1

build_szip:
	cd ${SZIP_VERSION} && make > ../build_szip_progress 2>&1

install_szip:
	make config_szip build_szip
	cd ${SZIP_VERSION} && make install > ../install_szip_progress 2>&1
	cat config_szip_progress build_szip_progress install_szip_progress > install_szip

distclean_szip:
	touch install_szip
	mv -f install_szip install_szip_last
	cd ${SZIP_VERSION} && make -k distclean

#hdf5
newConfig_hdf5:
	cd hdf5Config && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_hdf5:
	cd hdf5Config && ${EDITOR} configure.${PROTEUS_ARCH}

config_hdf5: install_zlib install_szip
	cd ${HDF5_VERSION} && ../hdf5Config/configure.${PROTEUS_ARCH} > ../config_hdf5_progress 2>&1

build_hdf5:
	cd ${HDF5_VERSION} && make > ../build_hdf5_progress 2>&1

install_hdf5:
	make config_hdf5 build_hdf5
	cd ${HDF5_VERSION} && make install > ../install_hdf5_progress 2>&1
	cat config_hdf5_progress build_hdf5_progress install_hdf5_progress > install_hdf5

distclean_hdf5:
	touch install_hdf5
	mv -f install_hdf5 install_hdf5_last
	cd ${HDF5_VERSION} && make -k distclean

#triangle
newConfig_triangle:
	cd triangleConfig && cp makefile.${PROTEUS_ARCH_OLD} makefile.${PROTEUS_ARCH}

editConfig_triangle:
	cd triangleConfig && ${EDITOR} makefile.${PROTEUS_ARCH}

config_triangle:
	echo "triangle has no config step; run 'make editConfig_triangle'" > config_triangle_progress 2>&1

build_triangle:
	cd ${TRIANGLE_VERSION}/src && make -f ../../triangleConfig/makefile.${PROTEUS_ARCH} trilibrary all > ../../build_triangle_progress 2>&1

install_triangle:
	make config_triangle build_triangle
	cd ${TRIANGLE_VERSION}/src && make -f ../../triangleConfig/makefile.${PROTEUS_ARCH} install > ../../install_triangle_progress 2>&1
	cat config_triangle_progress build_triangle_progress install_triangle_progress > install_triangle

distclean_triangle:
	touch install_triangle
	mv -f install_triangle install_triangle_last
	cd ${TRIANGLE_VERSION}/src && make -f ../../triangleConfig/makefile.${PROTEUS_ARCH} -k distclean

#tetgen
newConfig_tetgen:
	cd tetgenConfig && cp makefile.${PROTEUS_ARCH_OLD} makefile.${PROTEUS_ARCH}

editConfig_tetgen:
	cd tetgenConfig && ${EDITOR} makefile.${PROTEUS_ARCH}

config_tetgen:
	echo "tetgen has no configure step; run 'make editConfig_tetgen'" > config_tetgen_progress 2>&1

build_tetgen:
	cd ${TETGEN_VERSION} && make -f ../tetgenConfig/makefile.${PROTEUS_ARCH} > ../build_tetgen_progress 2>&1

install_tetgen:
	make config_tetgen build_tetgen
	cd ${TETGEN_VERSION} && make -f ../tetgenConfig/makefile.${PROTEUS_ARCH} install > ../install_tetgen_progress 2>&1
	cat config_tetgen_progress build_tetgen_progress install_tetgen_progress > install_tetgen

distclean_tetgen:
	touch install_tetgen
	mv -f install_tetgen install_tetgen_last
	cd ${TETGEN_VERSION} && make -f ../tetgenConfig/makefile.${PROTEUS_ARCH} -k clean

#superlu
newConfig_superlu:
	cd superluConfig && cp make.${PROTEUS_ARCH_OLD} make.${PROTEUS_ARCH}

editConfig_superlu:
	cd superluConfig && ${EDITOR} make.${PROTEUS_ARCH}

config_superlu:
	cp superluConfig/make.${PROTEUS_ARCH} ${SUPERLU_VERSION}/make.inc > config_superlu_progress 2>&1

build_superlu:
	cd ${SUPERLU_VERSION} && make superlulib > ../build_superlu_progress 2>&1

install_superlu:
	make config_superlu build_superlu
	cd ${SUPERLU_VERSION} && make install > ../install_superlu_progress 2>&1
	cat config_superlu_progress build_superlu_progress install_superlu_progress > install_superlu

distclean_superlu:
	touch install_superlu
	mv -f install_superlu install_superlu_last
	cd ${SUPERLU_VERSION} && make -k clean

#petsc
get_petsc:
	hg clone http://petsc.cs.iit.edu/petsc/petsc-dev
	cd petsc-dev/config && hg clone http://petsc.cs.iit.edu/petsc/BuildSystem BuildSystem

update_petsc:
	cd petsc-dev && hg pull -u
	cd petsc-dev/config/BuildSystem && hg pull -u

newConfig_petsc:
	cd petscConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_petsc:
	cd petscConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_petsc:
	cd ${PETSC_VERSION} && ../petscConfig/configure.${PROTEUS_ARCH}  > ../config_petsc_progress 2>&1

build_petsc:
	cd ${PETSC_VERSION} && make PETSC_DIR=${PROTEUS}/externalPackages/${PETSC_VERSION} PETSC_ARCH=${PROTEUS_ARCH} all > ../build_petsc_progress 2>&1

install_petsc:
	make config_petsc build_petsc
	cd ${PETSC_VERSION} && make PETSC_DIR=${PROTEUS}/externalPackages/${PETSC_VERSION} PETSC_ARCH=${PROTEUS_ARCH} install > ../install_petsc_progress 2>&1
	cat config_petsc_progress build_petsc_progress install_petsc_progress > install_petsc

distclean_petsc:
	touch install_petsc
	mv -f install_petsc install_petsc_last
	cd ${PETSC_VERSION} && make PETSC_DIR=${PROTEUS}/externalPackages/${PETSC_VERSION} PETSC_ARCH=${PROTEUS_ARCH}  -k clean && rm -rf externalpackages ${PROTEUS_ARCH}

#daetk
newConfig_daetk:
	cd daetkConfig && cp ${PROTEUS_ARCH_OLD} ${PROTEUS_ARCH} && cp ${PROTEUS_ARCH_OLD}.archive ${PROTEUS_ARCH}.archive && cp ${PROTEUS_ARCH_OLD}.sources ${PROTEUS_ARCH}.sources

editConfig_daetk:
	cd daetkConfig && ${EDITOR} ${PROTEUS_ARCH} ${PROTEUS_ARCH}.sources ${PROTEUS_ARCH}.archive 

config_daetk:
	cp -f daetkConfig/${PROTEUS_ARCH} ${DAETK_VERSION}/config/
	cp -f daetkConfig/${PROTEUS_ARCH}.sources ${DAETK_VERSION}/config/
	cp -f daetkConfig/${PROTEUS_ARCH}.archive ${DAETK_VERSION}/config/
	cd ${DAETK_VERSION} && touch dep.txt > ../config_daetk_progress 2>&1

build_daetk:
	cd ${DAETK_VERSION} && PETSC_DIR=${PROTEUS_PREFIX} PETSC_ARCH='' DAETK_ARCH=${PROTEUS_ARCH} DAETK_DIR=${PWD}/${DAETK_VERSION} make > ../build_daetk_progress 2>&1

install_daetk:
	make config_daetk build_daetk
	cd ${DAETK_VERSION} && PETSC_DIR=${PROTEUS_PREFIX} PETSC_ARCH='' DAETK_ARCH=${PROTEUS_ARCH} DAETK_DIR=${PWD}/${DAETK_VERSION}  make install > ../install_daetk_progress 2>&1
	cat config_daetk_progress build_daetk_progress install_daetk_progress > install_daetk

distclean_daetk:
	touch install_daetk
	mv -f install_daetk install_daetk_last	
	cd ${DAETK_VERSION} && PETSC_DIR=${PROTEUS_PREFIX} PETSC_ARCH='' DAETK_ARCH=${PROTEUS_ARCH} DAETK_DIR=${PWD}/${DAETK_VERSION}  make -k clobber

#numpy
newConfig_numpy:
	cd numpyConfig && cp site.cfg.${PROTEUS_ARCH_OLD} site.cfg.${PROTEUS_ARCH} && cp build.numpy.${PROTEUS_ARCH_OLD} build.numpy.${PROTEUS_ARCH} 

editConfig_numpy:
	cd numpyConfig && ${EDITOR} site.cfg.${PROTEUS_ARCH} build.numpy.${PROTEUS_ARCH}

config_numpy:
	echo "numpy has no config step run 'make editConfig_numpy'" > config_numpy_progress 2>&1
	cp -f numpyConfig/site.cfg.${PROTEUS_ARCH} ${NUMPY_VERSION}/site.cfg

build_numpy:
	cd ${NUMPY_VERSION} && ${PROTEUS}/externalPackages/numpyConfig/build.numpy.${PROTEUS_ARCH} > ../build_numpy_progress 2>&1

install_numpy:
	make config_numpy build_numpy
	cat config_numpy_progress build_numpy_progress > install_numpy

distclean_numpy:
	touch install_numpy
	mv -f install_numpy install_numpy_last
	cd ${NUMPY_VERSION} && rm -rf build

#numexpr
newConfig_numexpr:
	echo "numexpr has no customization"

editConfig_numexpr:
	echo "numexpr has no customization"

config_numexpr:
	echo "numexpr has no customization" > config_numexpr_progress 2>&1

build_numexpr:
	cd ${NUMEXPR_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_numexpr_progress 2>&1

install_numexpr:
	make config_numexpr build_numexpr
	cd ${NUMEXPR_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_numexpr_progress 2>&1
	cat config_numexpr_progress build_numexpr_progress install_numexpr_progress > install_numexpr

distclean_numexpr:
	touch install_numexpr
	mv -f install_numexpr install_numexpr_last
	cd ${NUMEXPR_VERSION} && rm -rf build

#pytables
newConfig_pytables:
	cd pytablesConfig && cp build.${PROTEUS_ARCH_OLD} build.${PROTEUS_ARCH} && cp install.${PROTEUS_ARCH_OLD} install.${PROTEUS_ARCH}

editConfig_pytables:
	cd pytablesConfig && ${EDITOR} build.${PROTEUS_ARCH} install.${PROTEUS_ARCH}

config_pytables:
	echo "pytables has no config step; run make 'make editConfig_pytables'" > config_pytables_progress 2>&1

build_pytables:
	cd ${PYTABLES_VERSION} && ../pytablesConfig/build.${PROTEUS_ARCH} > ../build_pytables_progress 2>&1

install_pytables: install_szip install_zlib install_hdf5
	make config_pytables build_pytables
	cd ${PYTABLES_VERSION} && ../pytablesConfig/install.${PROTEUS_ARCH} > ../install_pytables_progress 2>&1
	cat config_pytables_progress build_pytables_progress install_pytables_progress > install_pytables

distclean_pytables:
	touch install_pytables
	mv -f install_pytables install_pytables_last
	cd ${PYTABLES_VERSION} && rm -rf build

#nose
newConfig_nose:
	echo "no nose customization implemented"

editConfig_nose:
	echo "no nose customization implemented"

config_nose:
	echo "no nose customization implemented" > config_nose_progress 2>&1

build_nose:
	cd ${NOSE_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_nose_progress 2>&1

install_nose:
	make config_nose build_nose
	cd ${NOSE_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_nose_progress 2>&1
	cat config_nose_progress build_nose_progress install_nose_progress > install_nose

distclean_nose:
	touch install_nose
	mv -f install_nose install_nose_last
	cd ${NOSE_VERSION} && rm -rf build

#setuptools
newConfig_setuptools:
	echo "no setuptools customization implemented"

editConfig_setuptools:
	echo "no setuptools customization implemented"

config_setuptools:
	echo "no setuptools customization implemented" > config_setuptools_progress 2>&1

build_setuptools:
	cd ${SETUPTOOLS_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_setuptools_progress 2>&1

install_setuptools:
	echo "mwf hack already installed"
	#make config_setuptools build_setuptools
	#cd ${SETUPTOOLS_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_setuptools_progress 2>&1
	#cat config_setuptools_progress build_setuptools_progress install_setuptools_progress > install_setuptools

distclean_setuptools:
	touch install_setuptools
	mv -f install_setuptools install_setuptools_last
	cd ${SETUPTOOLS_VERSION} && rm -rf build

#mpi4py
newConfig_mpi4py:
	cd mpi4pyConfig && cp config.${PROTEUS_ARCH_OLD} config.${PROTEUS_ARCH}  && cp build.${PROTEUS_ARCH_OLD} build.${PROTEUS_ARCH} && cp install.${PROTEUS_ARCH_OLD} install.${PROTEUS_ARCH} && cp mpi.cfg.${PROTEUS_ARCH_OLD} mpi.cfg.${PROTEUS_ARCH}

editConfig_mpi4py:
	cd mpi4pyConfig && ${EDITOR} config.${PROTEUS_ARCH} build.${PROTEUS_ARCH} install.${PROTEUS_ARCH} mpi.cfg.${PROTEUS_ARCH}

config_mpi4py:
	cd ${MPI4PY_VERSION} && cp ../mpi4pyConfig/mpi.cfg.${PROTEUS_ARCH} mpi.cfg && ../mpi4pyConfig/config.${PROTEUS_ARCH} > ../config_mpi4py_progress 2>&1

build_mpi4py:
	cd ${MPI4PY_VERSION} && ../mpi4pyConfig/build.${PROTEUS_ARCH} > ../build_mpi4py_progress 2>&1

install_mpi4py:
	make config_mpi4py build_mpi4py
	cd ${MPI4PY_VERSION} && ../mpi4pyConfig/install.${PROTEUS_ARCH} > ../install_mpi4py_progress 2>&1
	cat config_mpi4py_progress build_mpi4py_progress install_mpi4py_progress > install_mpi4py

distclean_mpi4py:
	touch install_mpi4py
	mv -f install_mpi4py install_mpi4py_last
	cd ${MPI4PY_VERSION} && make -k fullclean && rm -rf build

get_petsc4py:
	hg clone https://petsc4py.googlecode.com/hg/ petsc4py-dev

update_petsc4py:
	cd petsc4py-dev && hg pull -u

newConfig_petsc4py:
	cd petsc4pyConfig && cp config.petsc4py.${PROTEUS_ARCH_OLD} config.petsc4py.${PROTEUS_ARCH} && cp build.petsc4py.${PROTEUS_ARCH_OLD} build.petsc4py.${PROTEUS_ARCH} 

editConfig_petsc4py:
	cd petsc4pyConfig && ${EDITOR} config.petsc4py.${PROTEUS_ARCH} build.petsc4py.${PROTEUS_ARCH}

config_petsc4py:
	cd ${PETSC4PY_VERSION} && ${PROTEUS}/externalPackages/petsc4pyConfig/config.petsc4py.${PROTEUS_ARCH} > ../config_petsc4py_progress  2>&1

build_petsc4py:
	cd ${PETSC4PY_VERSION} && ${PROTEUS}/externalPackages/petsc4pyConfig/build.petsc4py.${PROTEUS_ARCH} > ../build_petsc4py_progress  2>&1

install_petsc4py: install_petsc
	make config_petsc4py build_petsc4py
	cd ${PETSC4PY_VERSION} && PETSC_DIR=${PROTEUS_PREFIX} ${PROTEUS_PYTHON} setup.py install > ../install_petsc4py_progress 2>&1
	cat config_petsc4py_progress build_petsc4py_progress install_petsc4py_progress > install_petsc4py

distclean_petsc4py:
	touch install_petsc4py
	mv -f install_petsc4py install_petsc4py_last
	cd ${PETSC4PY_VERSION} && make fullclean && rm -rf build

#cython
newConfig_cython:
	echo "no cython customization implemented"

editConfig_cython:
	echo "no cython customization implemented"

config_cython:
	cd ${CYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py config > ../config_cython_progress 2>&1

build_cython:
	cd ${CYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_cython_progress 2>&1

install_cython:
	make config_cython build_cython
	cd ${CYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_cython_progress 2>&1
	cat config_cython_progress build_cython_progress install_cython_progress > install_cython

distclean_cython:
	touch install_cython
	mv -f install_cython install_cython_last
	cd ${CYTHON_VERSION} && make -k clean

#extensions
#extensionsModules
#matplotlib
newConfig_matplotlib:
	cd matplotlibConfig && cp setup.cfg.${PROTEUS_ARCH_OLD} setup.cfg.${PROTEUS_ARCH}

editConfig_matplotlib:
	cd matplotlibConfig && ${EDITOR} setup.cfg.${PROTEUS_ARCH}

config_matplotlib:
	cp matplotlibConfig/setup.cfg.${PROTEUS_ARCH} ${MATPLOTLIB_VERSION}/setup.cfg
	cd ${MATPLOTLIB_VERSION} && ${PROTEUS_PYTHON} setup.py config > ../config_matplotlib_progress 2>&1

build_matplotlib:
	cd ${MATPLOTLIB_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_matplotlib_progress 2>&1

install_matplotlib:
	make config_matplotlib build_matplotlib
	cd ${MATPLOTLIB_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_matplotlib_progress 2>&1
	cat config_matplotlib_progress build_matplotlib_progress install_matplotlib_progress > install_matplotlib

distclean_matplotlib:
	touch install_matplotlib
	mv -f install_matplotlib install_matplotlib_last
	cd ${MATPLOTLIB_VERSION} && make -k clean && rm -rf build

#stwave
newConfig_stwave:
	cd stwaveConfig && cp Makefile.${PROTEUS_ARCH_OLD} Makefile.${PROTEUS_ARCH}
	cd stwaveConfig && cp cmplrflags.${PROTEUS_ARCH_OLD}.mk cmplrflags.${PROTEUS.ARCH}.mk 

editConfig_stwave:
	cd stwaveConfig && ${EDITOR} Makefile.${PROTEUS_ARCH} && ${EDITOR} cmplrflags.${PROTEUS_ARCH}.mk

config_stwave:
	cp stwaveConfig/Makefile.${PROTEUS_ARCH} ${STWAVE_VERSION}/Makefile
	cp stwaveConfig/cmplrflags.${PROTEUS_ARCH}.mk ${STWAVE_VERSION}/cmplrflags.mk
	@echo "Makfile and cmplrflags.mk configured ... OK"  > config_stwave_progress 2>&1

build_stwave:
	cd ${STWAVE_VERSION} && make BUILDTYPE=stwave stwave > ../../build_stwave_serial_progress 2>&1
	cd ${STWAVE_VERSION} && make BUILDTYPE=stwave_ep stwave_ep > ../../build_stwave_ep_progress 2>&1	
	cd ${STWAVE_VERSION} && make BUILDTYPE=stwave_p stwave_p > ../../build_stwave_p_progress 2>&1
	cd ${STWAVE_VERSION} && make BUILDTYPE=libstw.a libstw.a > ../../build_libstw.a_progress 2>&1
	cat build_stwave_serial_progress build_stwave_ep_progress build_stwave_p_progress build_libstw.a_progress > build_stwave_progress
	rm -f build_stwave_serial_progress build_stwave_ep_progress build_stwave_p_progress build_libstw.a_progress
	@echo "Build of STWAVE ... OK" 

install_stwave:
	make config_stwave build_stwave
	@echo "STWAVE installed (sort of) ... OK" > install_stwave_progress 2>&1
	cat config_stwave_progress build_stwave_progress install_stwave_progress > install_stwave

test_stwave:
	cd stwaveConfig/test/test_idd && ${PROTEUS}/externalPackages/${STWAVE_VERSION}/stwave test_idd.sim 
	@echo "STWAVE serial TEST ... OK"
#	cd stwaveConfig/test/test_idd && mpirun -np 2 ${PROTEUS}/externalPackages/${STWAVE_VERSION}/stwave_ep test_idd_parallel.sim 
#	@echo "STWAVE embar-parallel TEST ... OK"
#	cd stwaveConfig/test/test_idd && mpiexec -np 2 ${PROTEUS}/externalPackages/${STWAVE_VERSION}/stwave_p test_idd_parallel.sim 
#	@echo "STWAVE full parallel  TEST ... OK"

distclean_stwave:
	touch install_stwave
	mv -f install_stwave install_stwave_last
	cd ${STWAVE_VERSION} && make -k clean && rm -f Makefile cmplrflags.mk stwave stwave_ep stwave_p libstw.a

#sip
newConfig_sip:
	echo "no sip customization implemented"

editConfig_sip:
	echo "no sip customization implemented"

config_sip:
	cd ${SIP_VERSION} && ${PROTEUS_PYTHON} configure.py > ../config_sip_progress 2>&1

build_sip:
	cd ${SIP_VERSION} && make > ../build_sip_progress 2>&1

install_sip:
	make config_sip build_sip
	cd ${SIP_VERSION} && make install > ../install_sip_progress 2>&1
	cat config_sip_progress build_sip_progress install_sip_progress > install_sip

distclean_sip:
	touch install_sip
	mv -f install_sip install_sip_last
	cd ${SIP_VERSION} && make -k clean

#qt
newConfig_qt:
	echo "no qt customization implemented"

editConfig_qt:
	echo "no qt customization implemented"

config_qt:
	cd ${QT_VERSION} && echo "yes\n" > yes.txt && echo "yes\n" | ${PROTEUS_PYTHON} configure.py --assume-shared > ../config_qt_progress 2>&1

build_qt:
	cd ${QT_VERSION} && make > ../build_qt_progress 2>&1

install_qt: install_sip
	make config_qt build_qt
	cd ${QT_VERSION} && make install > ../install_qt_progress 2>&1
	cat config_qt_progress build_qt_progress install_qt_progress > install_qt

distclean_qt:
	touch install_qt
	mv -f install_qt install_qt_last
	cd ${QT_VERSION} && make -k clean

#ipython
newConfig_ipython:
	echo "no ipython customization implemented"

editConfig_ipython:
	echo "no ipython customization implemented"

config_ipython:
	pip install --upgrade pyzmq pygments tornado pexpect Sphinx
	cd ${IPYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py config > ../config_ipython_progress 2>&1

build_ipython:
	cd ${IPYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_ipython_progress 2>&1

install_ipython: install_qt install_matplotlib
	make config_ipython build_ipython
	cd ${IPYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_ipython_progress 2>&1
	cat config_ipython_progress build_ipython_progress install_ipython_progress > install_ipython

distclean_ipython:
	touch install_ipython
	mv -f install_ipython install_ipython_last
	cd ${IPYTHON_VERSION} && make -k clean

#adh
newConfig_adh:
	echo "no adh customization implemented"

editConfig_adh:
	echo "no adh customization implemented"

config_preadh:
	cd adhConfig && configure.py.${PROTEUS_ARCH} -V --pre-adh  > ../config_preadh_progress 2>&1

config_adh: config_preadh
	cd adhConfig && configure.py.${PROTEUS_ARCH} -V  &&  > ../config_adh_progress 2>&1

build_preadh:
	cd adh/build_preadh && make  > ../../build_preadh_progress 2>&1

build_adh:
	cd adh/build && make  > ../../build_adh_progress 2>&1

install_adh:
	make config_adh build_adh
	echo "no adh install target" > install_adh_progress 2>&1
	cat config_preadh_progress config_adh_progress  build_preadh_progress build_adh_progress install_adh_progress > install_adh

distclean_adh:
	touch install_adh
	mv -f install_adh install_adh_last
	cd adh && make clean

#Parmetis-3.2 for adh
newConfig_adh-ParMetis-3.2:
	echo "no adh customization implemented"

editConfig_adh-ParMetis-3.2.0:
	echo "no adh customization implemented"

config_adh-ParMetis-3.2.0:
	cp adh-ParMetis-3.2.0Config/Makefile.in.${PROTEUS_ARCH} adh-ParMetis-3.2.0 > config_adh-ParMetis-3.2.0_progress  2>&1

build_adh-ParMetis-3.2.0:
	cd adh-ParMetis-3.2.0/METISLib && make > ../../build_adh-ParMetis-3.2.0_progress  2>&1 
	cd adh-ParMetis-3.2.0/ParMETISLib && make  >> ../../build_adh-ParMetis-3.2.0_progress  2>&1

install_adh-ParMetis-3.2.0:
	make config_adh-ParMetis-3.2.0 build_adh-ParMetis-3.2.0
	echo "no adh-ParMetis-3.2 install target" > install_adh-ParMetis-3.2.0_progress 2>&1
	cat config_adh-ParMetis-3.2.0_progress  build_adh-ParMetis-3.2.0_progress install_adh-ParMetis-3.2.0_progress > install_adh-ParMetis-3.2

distclean_adh-ParMetis-3.2.0:
	touch install_adh-ParMetis-3.2.0
	mv -f install_adh-ParMetis-3.2.0 install_adh-ParMetis-3.2.0_last
	cd adh-ParMetis-3.2.0/METISLib && make clean
	cd adh-ParMetis-3.2.0/ParMETISLib && make clean

#adcirc
newConfig_adcirc:
	cd adcircConfig && cp Makefile.${PROTEUS_ARCH_OLD} Makefile.${PROTEUS_ARCH}
	cd adcircConfig && cp cmplrflags.${PROTEUS_ARCH_OLD}.mk cmplrflags.${PROTEUS.ARCH}.mk

editConfig_adcirc:
	cd adcircConfig && ${EDITOR} Makefile.${PROTEUS_ARCH} && ${EDITOR} cmplrflags.${PROTEUS_ARCH}.mk

config_adcirc:
	cp adcircConfig/Makefile.${PROTEUS_ARCH} ${ADCIRC_VERSION}/makefile
	cp adcircConfig/cmplrflags.${PROTEUS_ARCH}.mk ${ADCIRC_VERSION}/cmplrflags.mk
	@echo "Makefile and cmplrflags.mk configured ... OK" > config_adcirc_progress 2>&1

build_adcirc:
	cd $(ADCIRC_VERSION) && make metis > ../../build_adcirc_metis_progress 2>&1
	cd ${ADCIRC_VERSION} && make BUILDTYPE=adcprep adcprep > ../../build_adcprep_progress 2>&1
	cd ${ADCIRC_VERSION} && make BUILDTYPE=adcirc adcirc > ../../build_adcirc_serial_progress 2>&1
	cd ${ADCIRC_VERSION} && make BUILDTYPE=padcirc padcirc > ../../build_padcirc_progress 2>&1
	cat build_adcirc_metis_progress build_adcprep_progress build_adcirc_serial_progress build_padcirc_progress > build_adcirc_progress
	rm -f build_adcirc_metis_progress build_adcprep_progress build_adcirc_serial_progress build_padcirc_progress
	@echo "Build of ADCIRC ... OK"

install_adcirc:
	make config_adcirc build_adcirc
	@echo "Adcirc installed (sort of) ... OK" > install_adcirc_progress 2>&1
	cat config_adcirc_progress build_adcirc_progress install_adcirc_progress > install_adcirc

distclean_adcirc:
	touch install_adcirc
	mv -f install_adcirc install_adcirc_last
	cd ${ADCIRC_VERSION} && make -k clean && rm -f makefile cmplrflags.mk adcprep adcirc padcirc

#jasper
newConfig_jasper:
	cd jasperConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_jasper:
	cd jasperConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_jasper:
	cd ${JASPER_VERSION} && ../jasperConfig/configure.${PROTEUS_ARCH} > ../config_jasper_progress 2>&1

build_jasper:
	cd ${JASPER_VERSION} && make > ../build_jasper_progress 2>&1

install_jasper:
	make config_jasper build_jasper
	cd ${JASPER_VERSION} && make install > ../install_jasper_progress 2>&1
	cat config_jasper_progress build_jasper_progress install_jasper_progress > install_jasper

distclean_jasper:
	touch install_jasper
	mv -f install_jasper install_jasper_last
	cd ${JASPER_VERSION} && make distclean


#grib_api                                                                                                                                 
newConfig_grib_api:
	cd grib_apiConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_grib_api:
	cd grib_apiConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_grib_api:
	cd ${GRIB_API_VERSION} && ../grib_apiConfig/configure.${PROTEUS_ARCH} > ../config_grib_api_progress 2>&1

build_grib_api:
	cd ${GRIB_API_VERSION} && make > ../build_grib_api_progress 2>&1

install_grib_api:
	make config_grib_api build_grib_api
	cd ${GRIB_API_VERSION} && make install > ../install_grib_api_progress 2>&1
	cat config_grib_api_progress build_grib_api_progress install_grib_api_progress > install_grib_api

distclean_grib_api:
	touch install_grib_api
	mv -f install_grib_api install_grib_api_last
	cd ${GRIB_API_VERSION} && make distclean


#pyproj                                                                                                                                     
newConfig_pyproj:
	echo "no pyproj customization implemented"

editConfig_pyproj:
	echo "no pyproj customization implemented"

config_pyproj:
	echo "no pyproj customization implemented" > config_pyproj_progress 2>&1

build_pyproj:
	cd ${PYPROJ_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_pyproj_progress 2>&1

install_pyproj:
	make config_pyproj build_pyproj
	cd ${PYPROJ_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_pyproj_progress 2>&1
	cat config_pyproj_progress build_pyproj_progress install_pyproj_progress > install_pyproj

distclean_pyproj:
	touch install_pyproj
	mv -f install_pyproj install_pyproj_last
	cd ${PYPROJ_VERSION} && ${PROTEUS_PYTHON} setup.py clean


#pygrib
newConfig_pygrib:
	echo "no pygrib customization implemented"

editConfig_pygrib:
	echo "no pygrib customization implemented"

config_pygrib:
	cd ${PYGRIB_VERSION} && ${PROTEUS_PYTHON} generate_setup-cfg.py
	echo "setup.cfg for pygrib created" > config_pygrib_progress 2>&1

build_pygrib:
	cd ${PYGRIB_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_pygrib_progress 2>&1

install_pygrib:
	make config_pygrib build_pygrib
	cd ${PYGRIB_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_pygrib_progress 2>&1
	cat config_pygrib_progress build_pygrib_progress install_pygrib_progress > install_pygrib

test_pygrib:
	cd ${PYGRIB_VERSION} && ${PROTEUS_PYTHON} test.py 

distclean_pygrib:
	touch install_pygrib
	mv -f install_pygrib install_pygrib_last
	cd ${PYGRIB_VERSION} && ${PROTEUS_PYTHON} setup.py clean


#netCDF-4
newConfig_netcdf:
	cd netcdfConfig && cp configure.${PROTEUS_ARCH_OLD} configure.${PROTEUS_ARCH}

editConfig_netcdf:
	cd netcdfConfig && ${EDITOR} configure.${PROTEUS_ARCH}

config_netcdf:
	cd ${NETCDF_VERSION} && ../netcdfConfig/configure.${PROTEUS_ARCH} > ../config_netcdf_progress 2>&1

build_netcdf:
	cd ${NETCDF_VERSION} && make > ../build_netcdf_progress 2>&1

check_netcdf:
	cd ${NETCDF_VERSION} && make check > ../check_netcdf_progress 2>&1

install_netcdf:
	make config_netcdf build_netcdf
	cd ${NETCDF_VERSION} && make install > ../install_netcdf_progress 2>&1
	cat config_netcdf_progress build_netcdf_progress install_netcdf_progress > install_netcdf

distclean_netcdf:
	touch install_netcdf
	mv -f install_netcdf install_netcdf_last
	cd ${NETCDF_VERSION} && make distclean


#netCDF4-Python        
newConfig_netcdf4-python:
	echo "no netcdf4-python customization implemented"

editConfig_netcdf4-python:
	echo "no netcdf4-python customization implemented"

config_netcdf4-python:
	cd ${NETCDF4-PYTHON_VERSION} && ${PROTEUS_PYTHON} generate_setup-cfg.py  
	echo "setup.cfg for netcdf4-python created" > config_netcdf4-python_progress 2>&1

build_netcdf4-python:
	cd ${NETCDF4-PYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py build > ../build_netcdf4-python_progress 2>&1

install_netcdf4-python:
	make config_netcdf4-python build_netcdf4-python
	cd ${NETCDF4-PYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py install > ../install_netcdf4-python_progress 2>&1
	cat config_netcdf4-python_progress build_netcdf4-python_progress install_netcdf4-python_progress > install_netcdf4-python

test_netcdf4-python:
	cd ${NETCDF4-PYTHON_VERSION}/test && ${PROTEUS_PYTHON} run_all.py 

distclean_netcdf4-python:
	touch install_netcdf4-python
	mv -f install_netcdf4-python install_netcdf4-python_last
	cd ${NETCDF4-PYTHON_VERSION} && ${PROTEUS_PYTHON} setup.py clean

