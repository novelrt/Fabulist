local sections = { }
local currentSection
local function section(name)
    currentSection = { name = name }
    sections[#sections + 1] = currentSection
end

local currentOption
local function options(labelOrAction)
    if type(labelOrAction) == "string" then
        currentOption = { type = "option", name = labelOrAction }
        currentSection[#currentSection + 1] = currentOption
    elseif type(labelOrAction) == "table" then
        currentOption.action = labelOrAction
    else
        error("unknown parameter")
    end
    return options
end

local function jump(sectionName)
    return { type = "action", action = "jump", section = sectionName }
end

local speakers = { }
local function speaker(speakerName)
    local function speech(line)
        currentSection[#currentSection + 1] = { type = "line", speaker = speakerName, text = line }
        return speech
    end

    speakers[speakerName] = speech

    return speech
end

local base64 = require("base64")
local function execute(fn)
    assert(type(fn) == "function", "expected function")

    local bitcode = base64.encode(string.dump(fn))
    local variables = { }
    for i = 1, math.huge do
        local name, value = debug.getupvalue(fn, i)
        if not name then break end

        assert(type(value) ~= "function",
            ("cannot serialize upvalue %s as it is a function"):format(name))

        variables[i] = value
    end

    currentSection[#currentSection + 1] = { type = "command", bitcode = bitcode, upvalues = variables }
end

local fenv = { section = section, options = options, jump = jump, speaker = speaker, execute = execute }
setmetatable(fenv, { __index = speakers })
setfenv(
    assert(
        loadfile(
            assert(..., "expected file"))),
    fenv)()

local sectionsByName = { }
for _, v in ipairs(sections) do
    sectionsByName[v.name] = v
    v.name = nil
end

local json = require("json")
print(json.encode(sectionsByName))
