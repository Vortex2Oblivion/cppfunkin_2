function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"idle", 24, false, {})
    character.animation:addOffset("idle", -30, -10)

    character.animation:addByPrefix("singLEFT" ,"left", 24, false, {})
    character.animation:addOffset("singLEFT", -16, 23)

    character.animation:addByPrefix("singDOWN" ,"down", 24, false, {})
    character.animation:addOffset("singDOWN", -72, 71)

    character.animation:addByPrefix("singUP" ,"up", 24, false, {})
    character.animation:addOffset("singUP", -51, -37)

    character.animation:addByPrefix("singRIGHT" ,"right", 24, false, {})
    character.animation:addOffset("singRIGHT", -110, 16)

    character.animation:play("idle")
    character:updateHitbox()
end