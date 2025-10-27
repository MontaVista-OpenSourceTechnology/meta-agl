SUMMARY = "Powerful and Lightweight Python Tree Data Structure"
HOMEPAGE = "https://github.com/c0fec0de/anytree"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

DEPENDS = "python3-pdm-native python3-pdm-backend-native"

SRC_URI[sha256sum] = "c9d3aa6825fdd06af7ebb05b4ef291d2db63e62bb1f9b7d9b71354be9d362714"

PYPI_PACKAGE = "anytree"

inherit pypi python_setuptools_build_meta

BBCLASSEXTEND += "native nativesdk"
