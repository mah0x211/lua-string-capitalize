# lua-string-capitalize

[![test](https://github.com/mah0x211/lua-string-capitalize/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-string-capitalize/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-string-capitalize/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-string-capitalize)


converts the first letter `a-z` of each word to uppercase.

## Installation

```sh
luarocks install string-capitalize
```

this module install the `lua_string_capitalize.h` to `CONFDIR` and creates a symbolic link in `LUA_INCDIR`.


---


## Usage

```lua
local capitalize = require('string.capitalize')

print(capitalize('foo bar hELlO world'))
-- Foo Bar HELlO World
```


## s = capitalize( s )

converts the first letter `a-z` of each word to uppercase.

**Params**

- `s:string`: string

**Returns**

- `s:string`: capitalized string.


## Use from C module

the `string-capitalize` module installs `lua_string_capitalize.h` in the lua include directory.

the following APIs are helper functions to use `string-capitalize` module in C module.

### void lua_string_capitalize( lua_State *L, const char *str )

push a string to `*L` with the first letter of each word in `*str` capitalized.

