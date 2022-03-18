do
speaker "narrator"

section "root"
narrator
    "Hey, you're somehow at a store again."
    "What do?"
options
    "Buy milk" { jump "buyMilk" }
    "Go home" { jump "root" }

section "buyMilk"
narrator
    "Oh no, they're all out of milk."
jump "root"
end
