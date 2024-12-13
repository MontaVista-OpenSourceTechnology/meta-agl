FILESEXTRAPATHS:prepend := "${THISDIR}/agl-compositor-init:"

SUMMARY = "Startup systemd unit for the AGL Wayland compositor with starting in the same time the DRM and PipeWire backends"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

inherit systemd

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "file://agl-compositor-pipewire.conf \
           file://agl-compositor-stream-pipewire.service \
"

S = "${WORKDIR}"

AGL_KVM_REMOTE_OUTPUT_IP ?= "172.16.10.3"
AGL_KVM_REMOTE_OUTPUT_PORT ?= "5005"

do_install() {
    sed -i -e "s,@REMOTE_OUTPUT_IP@,${AGL_KVM_REMOTE_OUTPUT_IP},g" \
	${WORKDIR}/agl-compositor-stream-pipewire.service

    sed -i -e "s,@REMOTE_OUTPUT_PORT@,${AGL_KVM_REMOTE_OUTPUT_PORT},g" \
	${WORKDIR}/agl-compositor-stream-pipewire.service

    install -D -p -m0644 ${WORKDIR}/agl-compositor-stream-pipewire.service ${D}${systemd_system_unitdir}/agl-compositor-stream-pipewire.service

    install -d ${D}${systemd_system_unitdir}/agl-compositor.service.d
    install -m644 ${WORKDIR}/agl-compositor-pipewire.conf ${D}/${systemd_system_unitdir}/agl-compositor.service.d/02-agl-compositor.conf
}

FILES:${PN} += "\
    ${systemd_system_unitdir}/agl-compositor.service.d \
    ${systemd_system_unitdir}/agl-compositor.service.d/02-agl-compositor.conf \
    ${systemd_system_unitdir}/agl-compositor-stream-pipewire.service \
    "

RDEPENDS:${PN} = "agl-compositor-init weston-ini"
RCONFLICTS:${PN} = "weston-init"

SYSTEMD_SERVICE:${PN} = "agl-compositor-stream-pipewire.service"
