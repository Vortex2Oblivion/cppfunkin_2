function onCreateCharacter(character)
    character.flipX = not character.flipX

    character.animation:addByPrefix("idle", "Pico Idle Dance", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN", "Pico Down Note0", 24, false, {})
    character.animation:addOffset("singDOWN", 200, -70)

    character.animation:addByPrefix("singUP", "pico Up note0", 24, false, {})
    character.animation:addOffset("singUP", -29, 27)

    character.animation:addByPrefix("singLEFT", "Pico NOTE LEFT0", 24, false, {})
    character.animation:addOffset("singLEFT", -68, -7)

    character.animation:addByPrefix("singRIGHT", "Pico Note Right0", 24, false, {})
    character.animation:addOffset("singRIGHT", 65, 9)

    character.animation:addByPrefix("singDOWNmiss", "Pico Down Note MISS", 24, false, {})
    character.animation:addOffset("singDOWNmiss", 210, -28)

    character.animation:addByPrefix("singUPmiss", "pico Up note miss", 24, false, {})
    character.animation:addOffset("singUPmiss", -19, 67)

    character.animation:addByPrefix("singRIGHTmiss", "Pico NOTE LEFT miss", 24, false, {})
    character.animation:addOffset("singRIGHTmiss", -60, 41)

    character.animation:addByPrefix("singLEFTmiss", "Pico Note Right Miss", 24, false, {})
    character.animation:addOffset("singLEFTmiss", 62, 64)

    character.animation:play("idle", true)

    character.barColor = Color.new(183, 216, 85, 255)
end