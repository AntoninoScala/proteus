#! /usr/bin/env python
import os

#set convenience variables for proteus
prefix           = os.getenv('PROTEUS_PREFIX')
proteus          = os.getenv('PROTEUS')
proteus_arch     = os.getenv('PROTEUS_ARCH')
externalPackages = os.path.join(proteus,'externalPackages')
#define adh-specific variables that are needed
adh_dir          = os.path.join(externalPackages,'adh')
#adh requires parmetis 3.2
parmetis_dir     = os.path.join(externalPackages,'adh-externals/ParMetis')
#adh requires UMFPACK 3.2
umfpack_dir      = os.path.join(externalPackages,'adh-externals/UMFPACK')

CMAKE = os.path.join(proteus,proteus_arch,'bin','cmake')

adh_config_variables = {'BUILD_PRE_ADH':'ON',
                        'CMAKE_BUILD_TYPE':'Debug',
                        'CMAKE_OSX_ARCHITECTURES':'x86_64',
                        'CMAKE_OSX_DEPLOYMENT_TARGET':'10.6',
                        'DEBUG_LEVEL':'1',
                        'OUTPUT_FILE_FORMAT':'XMS',
                        'USE_PACKAGE_MPI':'OFF',
                        'USE_PACKAGE_PARMETIS':'OFF',
                        'USE_PACKAGE_UMFPACK':'OFF',
                        '_ADH_SEDIMENT':'OFF',
                        'UMFPACK_INCLUDE_DIR':os.path.join(umfpack_dir),
                        'UMFPACK_LIBRARY':os.path.join(umfpack_dir,'umfpack.a'),
                        'UMFPACK_VERSION':3,
                        'UMFPACK_INT_SIZE':32,
                        'METIS_INCLUDE_DIR':os.path.join(parmetis_dir,'METISLib'),
                        'METIS_LIBRARY':os.path.join(parmetis_dir,'libmetis.a'),
                        'PARMETIS_LIBRARY':os.path.join(parmetis_dir,'libparmetis.a'),
                        'PARMETIS_INCLUDE_DIR':os.path.join(parmetis_dir),
                        }

def configure_preadh():

    adh_config_variables['BUILD_PRE_ADH']       ='ON'
    adh_config_variables['USE_PACKAGE_MPI']     ='OFF'
    adh_config_variables['USE_PACKAGE_PARMETIS']='OFF'

    from string import Template
    temp = "{cmake} ".format(cmake=CMAKE)
    for key,val in adh_config_variables.iteritems():
        temp += " -D{name}=${name} ".format(name=key)
    #
    temp += " .."
    command_temp = Template(temp)

    command = command_temp.substitute(adh_config_variables)

    return command

def configure_adh():

    adh_config_variables['BUILD_PRE_ADH']       ='OFF'
    adh_config_variables['USE_PACKAGE_MPI']     ='ON'
    adh_config_variables['USE_PACKAGE_PARMETIS']='ON'
    adh_config_variables['USE_PACKAGE_UMFPACK'] ='ON'

    from string import Template
    temp = "{cmake} ".format(cmake=CMAKE)
    for key,val in adh_config_variables.iteritems():
        temp += " -D{name}=${name} ".format(name=key)
    #
    temp += " .."
    command_temp = Template(temp)

    command = command_temp.substitute(adh_config_variables)

    return command

if __name__ == '__main__':
    import optparse,sys

    usage = "usage: %prog [options]"
    parser = optparse.OptionParser(usage=usage)
    parser.add_option("--pre-adh",
                      help="configure pre-adh",
                      action="store_true",
                      dest="pre_adh",
                      default=False)
    parser.add_option("-V","--verbose",
                      help="print out some information about what's being attempted",
                      action="store_true",
                      default=False)

    (opts,args) =parser.parse_args()

    import subprocess

    echo = opts.verbose

    if opts.pre_adh:
        #first build pre_adh
        command = configure_preadh()
        build_dir = os.path.join(adh_dir,'build_preadh')
        if echo:
            print "Trying to configure pre_adh with {command} ".format(command=command)
    else:
        command = configure_adh()
        build_dir = os.path.join(adh_dir,'build')
        if echo:
            print "Trying to configure adh with {command} ".format(command=command)

    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    os.chdir(build_dir)


    fail = subprocess.call(command.split())

    if echo:
        print "configure returned fail = {0} ".format(fail)

    if not opts.pre_adh and fail: #looks like it can fail with just one iteration through
        print "retrying ..."
        fail = subprocess.call(command.split())
        if not fail:
            print "looks like did not fail second time"
        else:
            print "failed again"
    if fail:
        sys.exit(1)
    sys.exit(0)
