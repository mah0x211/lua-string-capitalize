local assert = require('assert')
local capitalize = require('string.capitalize')

local function test_capitalize()
    -- test that that converts the first letter of each word to uppercase
    for _, v in ipairs({
        {
            arg = 'foo-bar-baz',
            exp = 'Foo-Bar-Baz',
        },
        {
            arg = 'hello_world',
            exp = 'Hello_world',
        },
        {
            arg = 'hello©example',
            exp = 'Hello©Example',
        },
        {
            arg = 'helloࠀexample',
            exp = 'HelloࠀExample',
        },
        {
            arg = 'hello퀀example',
            exp = 'Hello퀀Example',
        },
        {
            arg = 'hello豈example',
            exp = 'Hello豈Example',
        },
        {
            arg = 'hello𐂂example',
            exp = 'Hello𐂂Example',
        },
        {
            arg = ' () _ hello | world  _foo Bar',
            exp = ' () _ Hello | World  _foo Bar',
        },
        {
            arg = "foo'bar",
            exp = "Foo'bar",
        },
        {
            arg = "'foo'bar 'baz b'aa''qux'quux''_hello",
            exp = "'Foo'bar 'Baz B'aa''Qux'quux''_hello",
        },
        {
            arg = 'ハローworld',
            exp = 'ハローWorld',
        },
    }) do
        local s = capitalize(v.arg)
        assert.equal(s, v.exp)
        assert.not_equal(s, v.arg)
    end

    -- test that throws an erorr with invalid argument
    for _, v in ipairs({
        1,
        true,
        false,
        {},
        function()
        end,
    }) do
        local err = assert.throws(function()
            capitalize(v)
        end)
        assert.match(err, '#1 .+ [(]string expected, ', false)
    end
end

test_capitalize()
