#!/bin/bash
#set -x

SCRIPTPATH="$( cd $(dirname $0) >/dev/null 2>&1 ; pwd -P )"
echo $SCRIPTPATH
AGLROOT="$SCRIPTPATH/../../.."
POKYDIR="$AGLROOT/external/poky"
TMPROOT=`mktemp -d`

rm -rf ${TMPROOT}/testbuild-ycl || true
mkdir -p ${TMPROOT}/testbuild-ycl
cd ${TMPROOT}/testbuild-ycl

source $POKYDIR/oe-init-build-env .

cat << EOF >> conf/local.conf
# just define defaults
AGL_FEATURES ?= ""
AGL_EXTRA_IMAGE_FSTYPES ?= ""

# important settings imported from poky-agl.conf
# we cannot import the distro config right away
# as the initial values are poky only till the layer
# is added in

AGL_DEFAULT_DISTRO_FEATURES = "usrmerge largefile opengl wayland pam bluetooth bluez5 3g"
DISTRO_FEATURES:append = " systemd wayland pam \${AGL_DEFAULT_DISTRO_FEATURES}"
DISTRO_FEATURES_BACKFILL_CONSIDERED:append = " sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"

EOF

yocto-check-layer --no-auto-dependency \
	-- \
	$AGLROOT/meta-agl/meta-agl-drm-lease \
	--dependency \
	$AGLROOT/meta-agl/meta-agl-core 

#

[ $? = 0 ] && rm -rf ${TMPROOT}/testbuild-ycl

exit 0
