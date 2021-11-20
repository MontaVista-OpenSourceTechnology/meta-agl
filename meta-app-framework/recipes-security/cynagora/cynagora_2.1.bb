DESCRIPTION = "Cynagora service and client libraries"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://Apache-2.0;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://gerrit.automotivelinux.org/gerrit/src/cynagora;protocol=https;branch=${AGL_BRANCH}"
SRCREV = "7d7907651c42c5c32deabc17b639e0e1765eae60"
PV = "2.1+git${SRCPV}"

S = "${WORKDIR}/git"

DEPENDS = "systemd libcap"

inherit cmake

EXTRA_OECMAKE += " \
	-DSYSTEMD_UNIT_DIR=${systemd_system_unitdir} \
	-DWITH_SYSTEMD=ON \
	-DWITH_CYNARA_COMPAT=OFF \
"

inherit useradd
USERADD_PACKAGES = "${PN}"
GROUPADD_PARAM:${PN} = "-r cynagora"
USERADD_PARAM:${PN} = "\
--system --home ${localstatedir}/lib/empty \
--no-create-home --shell /bin/false \
--gid cynagora cynagora \
"

FILES:${PN} += "${systemd_system_unitdir}"

PACKAGES =+ "${PN}-tools"
FILES:${PN}-tools += "${bindir}/cynagora-admin ${bindir}/cynagora-agent"
RDEPENDS:${PN}:append:agl-devel = " ${PN}-tools"

inherit ptest
SRC_URI:append = " file://run-ptest"
RDEPENDS:${PN}-ptest:append = " ${PN}-tools"
