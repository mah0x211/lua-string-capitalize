SRCS=$(wildcard src/*.c)
SOBJ=$(SRCS:.c=.$(LIB_EXTENSION))
INSTALL?=install

ifdef STRING_CAPITALIZE_COVERAGE
COVFLAGS=--coverage
endif

.PHONY: all install

all: $(SOBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) $(COVFLAGS) $(CPPFLAGS) -o $@ -c $<

%.$(LIB_EXTENSION): %.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) $(PLATFORM_LDFLAGS) $(COVFLAGS)

install: $(SOBJ)
	$(INSTALL) -d $(INST_LIBDIR)
	$(INSTALL) $(SOBJ) $(INST_LIBDIR)
	$(INSTALL) src/lua_string_capitalize.h $(CONFDIR)
	rm -f $(LUA_INCDIR)/lua_string_capitalize.h
	ln -s $(CONFDIR)/lua_string_capitalize.h $(LUA_INCDIR)
	rm -f ./src/*.o
	rm -f ./src/*.so

