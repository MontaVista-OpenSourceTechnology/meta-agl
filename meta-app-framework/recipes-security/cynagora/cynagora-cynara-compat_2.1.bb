DESCRIPTION = "Cynara service with client libraries"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://Apache-2.0;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/src/cynagora;protocol=https;branch=${AGL_BRANCH}"
SRCREV = "7d7907651c42c5c32deabc17b639e0e1765eae60"
PV = "2.1+git${SRCPV}"

S = "${WORKDIR}/git"

inherit cmake

PROVIDES = "cynara"
RPROVIDES:${PN} = "cynara"
DEPENDS = "libcap"
RDEPENDS:${PN} = "cynagora"

EXTRA_OECMAKE += " \
	-DWITH_SYSTEMD=OFF \
	-DWITH_CYNARA_COMPAT=ON \
	-DDIRECT_CYNARA_COMPAT=ON \
"

do_install:append() {
	# remove cynagora stuff
	rm $(find ${D} -name '*cynagora*')
	# remove stupid test
	rm -r ${D}${bindir}
}

