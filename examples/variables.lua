speaker "narrator"
speaker "monika"

local function changeAnger(character, amount)
    execute(function(state)
        state.characters[monika].anger = state.characters[monika].anger + amount
    end)
end

section "root"
narrator
    "Monika seems unamused with your actions"
options
    "Crack a joke" { jump "badJoke" }
    "Crack a joke" { jump "goodJoke" }

section "badJoke"
monika "..."
narrator "It seems Monika didn't like that joke..."
changeAnger("monika", 10)
jump "root"

section "goodJoke"
monika "Hahaha!"
narrator "It seemed she enjoyed that one."
changeAnger("monika", -10)
jump "root"
