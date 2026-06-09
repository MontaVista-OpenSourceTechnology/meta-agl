# Fix Fuchsia clang 21.0.0git SIGSEGV crash (exit code 139) - compiler bug
# The bundled clang randomly segfaults on various C++ files when compiling
# for both host (x86_64) and target (aarch64). Since ninja is incremental,
# retrying picks up from the failed .o and eventually all files compile.
#
# Also remove -g3/-ggdb3 which increases crash probability on complex files.

do_configure:append() {
    sed -i 's/"-g3",/"-g",/' ${S}/engine/src/flutter/third_party/dart/build/config/compiler/BUILD.gn
    sed -i '/-ggdb3/d' ${S}/engine/src/flutter/third_party/dart/build/config/compiler/BUILD.gn
    sed -i 's/"-g3",/"-g",/' ${S}/engine/src/flutter/third_party/dart/runtime/BUILD.gn
    sed -i '/-ggdb3/d' ${S}/engine/src/flutter/third_party/dart/runtime/BUILD.gn
}

do_compile() {
    cd ${S}/engine/src

    export HOME=${WORKDIR}

    FLUTTER_RUNTIME_MODES="${@bb.utils.filter('PACKAGECONFIG', 'debug profile release jit_release', d)}"
    bbnote "FLUTTER_RUNTIME_MODES=${FLUTTER_RUNTIME_MODES}"

    for MODE in $FLUTTER_RUNTIME_MODES; do
        BUILD_DIR="$(echo ${TMP_OUT_DIR} | sed "s/_RUNTIME_/${MODE}/g")"

        RETRY=0
        while ! ninja -C "${BUILD_DIR}" ${PARALLEL_MAKE}; do
            RETRY=$(expr $RETRY + 1)
            if [ $RETRY -ge 5 ]; then
                bberror "ninja failed after 5 retries for mode=$MODE"
                exit 1
            fi
            bbwarn "ninja crashed (attempt $RETRY/5), retrying..."
            sleep 2
        done
    done
}
do_compile[progress] = "outof:^\[(\d+)/(\d+)\]\s+"
