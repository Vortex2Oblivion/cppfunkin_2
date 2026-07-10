function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"Dad idle dance", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN" ,"Dad Sing Note DOWN", 24, false, {})
    character.animation:addOffset("singDOWN", 0, -30)

    character.animation:addByPrefix("singUP" ,"Dad Sing Note UP", 24, false, {})
    character.animation:addOffset("singUP", -6, 50)

    character.animation:addByPrefix("singRIGHT" ,"Dad Sing Note RIGHT", 24, false, {})
    character.animation:addOffset("singRIGHT", 0, 27)

    character.animation:addByPrefix("singLEFT" ,"Dad Sing Note LEFT", 24, false, {})
    character.animation:addOffset("singLEFT", -9, 10)

    character.animation:play("idle")
end