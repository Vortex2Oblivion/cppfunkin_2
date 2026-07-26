function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"qt idle", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN", "qt down", 24, false, {})
    character.animation:addOffset("singDOWN", 55, -85)

    character.animation:addByPrefix("singUP" ,"qt up", 24, false, {})
    character.animation:addOffset("singUP", -17, 31)

    character.animation:addByPrefix("singRIGHT" ,"qt rightt", 24, false, {})
    character.animation:addOffset("singRIGHT", 39, -29)

    character.animation:addByPrefix("singLEFT" ,"qt left", 24, false, {})
    character.animation:addOffset("singLEFT", 46, -4)

    character.animation:play("idle", true)

    character.barColor = Color.new(255, 140, 181, 255)

    character.offset.x = 30
    character.offset.y = -80
end