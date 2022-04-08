# lua-string-capitalize

[![test](https://github.com/mah0x211/lua-string-capitalize/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-string-capitalize/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-string-capitalize/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-string-capitalize)


converts the first letter `a-z` of each word to uppercase.

## Installation

```sh
luarocks install string-capitalize
```


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

