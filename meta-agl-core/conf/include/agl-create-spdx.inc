INHERIT += " create-spdx "

# do_create_runtime_spdx has a race condition on qemuarm builders
# SPEC-4956
LTTNGMODULES:qemuarm = ""
LTTNGUST:qemuarm = ""
LTTNGTOOLS:qemuarm = ""