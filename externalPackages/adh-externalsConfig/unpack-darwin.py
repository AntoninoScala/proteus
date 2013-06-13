#! /usr/bin/env python
import os

#set convenience variables for proteus
prefix           = os.getenv('PROTEUS_PREFIX')
proteus          = os.getenv('PROTEUS')
proteus_arch     = os.getenv('PROTEUS_ARCH')
externalPackages = os.path.join(proteus,'externalPackages')

#define adh-specific variables that are needed
adh_externals_dir          = os.path.join(externalPackages,'adh-externals')
parmetis_archive = 'ParMetis-3.2.0.tar.gz' #adh requires ParMetis version 3.2
umfpack_archive  = 'UMFPACK-3.2.0.tar.gz'  #adh requires UMFPACK version 3.2
#what the tarballs unpack to
unpacked_name = {'ParMetis':'ParMetis-3.2.0',
                 'UMFPACK':'UMFPACK3.2'}

def unpack(archive,local_name):
    """
    Unpack tarball in archive and rename directory to local_name
    if subdirectory local_name exists then skip unpacking
    """
    import subprocess
    assert os.path.exists(adh_externals_dir)

    os.chdir(adh_externals_dir)

    tarball = os.path.join('dist',archive)
    assert os.path.exists(tarball)

    if not os.path.exists(local_name): 
        command = "tar -zxvf {tarball}".format(tarball=tarball)
        fail = subprocess.call(command.split())
        if fail:
            return fail
        os.rename(unpacked_name[local_name],local_name)
    
    return False

if __name__ == '__main__':

    import sys
    failed = unpack(parmetis_archive,'ParMetis')
    if failed:
        sys.exit(failed)

    failed = unpack(umfpack_archive,'UMFPACK')
    if failed:
        sys.exit(failed)


