function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"BF idle dance", 24, false, {})
    character.animation:addOffset("idle", -5, 0)

    character.animation:addByPrefix("singDOWN" ,"BF NOTE DOWN0", 24, false, {})
    character.animation:addOffset("singDOWN", -20, -51)

    character.animation:addByPrefix("singUP" ,"BF NOTE UP0", 24, false, {})
    character.animation:addOffset("singUP", -46, 27)

    character.animation:addByPrefix("singRIGHT" ,"BF NOTE RIGHT0", 24, false, {})
    character.animation:addOffset("singRIGHT", -48, -7)

    character.animation:addByPrefix("singLEFT" ,"BF NOTE LEFT0", 24, false, {})
    character.animation:addOffset("singLEFT", 5, -6)

    character.animation:play("idle", true)
    character.offset.y = 350
end