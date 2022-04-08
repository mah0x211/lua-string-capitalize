package = "string-capitalize"
version = "dev-1"
source = {
   url = "git+https://github.com/mah0x211/lua-string-capitalize.git"
}
description = {
   summary = "converts the first letter a-z of each word to uppercase.",
   homepage = "https://github.com/mah0x211/lua-string-capitalize",
   license = "MIT"
}
dependencies = {
    "lua >= 5.1",
}
build = {
    type = 'make',
    build_variables = {
        LIB_EXTENSION   = "$(LIB_EXTENSION)",
        CFLAGS          = "$(CFLAGS)",
        WARNINGS        = "-Wall -Wno-trigraphs -Wmissing-field-initializers -Wreturn-type -Wmissing-braces -Wparentheses -Wno-switch -Wunused-function -Wunused-label -Wunused-parameter -Wunused-variable -Wunused-value -Wuninitialized -Wunknown-pragmas -Wshadow -Wsign-compare",
        CPPFLAGS        = "-I$(LUA_INCDIR)",
        LDFLAGS         = "$(LIBFLAG)",
        STRING_CAPITALIZE_COVERAGE   = "$(STRING_CAPITALIZE_COVERAGE)",
    },
    install_variables = {
        LIB_EXTENSION   = "$(LIB_EXTENSION)",
        INST_LIBDIR     = "$(LIBDIR)/string/",
    }
}
