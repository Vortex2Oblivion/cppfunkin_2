function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"idle", 24, false, {})
    character.animation:addOffset("idle", 30, 10)

    character.animation:addByPrefix("singLEFT" ,"leftalt0", 24, false, {})
    character.animation:addOffset("singLEFT", 16, -23)

    character.animation:addByPrefix("singDOWN" ,"downalt0", 24, false, {})
    character.animation:addOffset("singDOWN", 72, -71)

    character.animation:addByPrefix("singUP" ,"upalt0", 24, false, {})
    character.animation:addOffset("singUP", 51, 37)

    character.animation:addByPrefix("singRIGHT" ,"rightalt0", 24, false, {})
    character.animation:addOffset("singRIGHT", 110, -16)

    character.animation:play("idle")
end