# imx-atf_2.12 (walnascar) DEPENDS on virtual/cross-cc, a Yocto 5.2 rename of
# virtual/${TARGET_PREFIX}gcc that does not exist in AGL scarthgap (5.0).
# Replace with the scarthgap-compatible form.
DEPENDS:remove = "virtual/cross-cc"
DEPENDS:append = " gcc-cross-${TARGET_ARCH}"
