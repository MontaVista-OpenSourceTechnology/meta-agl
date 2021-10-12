require af-main_${PV}.inc 

inherit cmake pkgconfig nativesdk

SECTION = "base"

DEPENDS = "nativesdk-openssl nativesdk-libxml2 nativesdk-xmlsec1 nativesdk-libzip nativesdk-json-c"

EXTRA_OECMAKE = "\
	-DUSE_LIBZIP=1 \
	-DUSE_SIMULATION=1 \
	-DUSE_SDK=1 \
	-DAGLVERSION=${AGLVERSION} \
	-Dafm_name=${afm_name} \
	-Dafm_confdir=${afm_confdir} \
	-Dafm_datadir=${afm_datadir} \
"

do_install:append() {
    # remove unused .pc file we don't want to package
	rm -rf ${D}/${libdir}
}

PACKAGES = "${PN}-tools ${PN}-tools-dbg"
FILES:${PN}-tools = "${bindir}/wgtpkg-* ${afm_confdir}/*"
FILES:${PN}-tools:append:agl-sign-wgts = " ${datadir}/afm"
FILES:${PN}-tools-dbg = "${bindir}/.debug/wgtpkg-*"
