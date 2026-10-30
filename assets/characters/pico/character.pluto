function onCreateCharacter(character)
    character.flipX = not character.flipX

    character.animation:addByPrefix("idle", "Pico Idle Dance", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN", "Pico Down Note0", 24, false, {})
    character.animation:addOffset("singDOWN", -37, -82)

    character.animation:addByPrefix("singUP", "pico Up note0", 24, false, {})
    character.animation:addOffset("singUP", -21, 28)

    character.animation:addByPrefix("singLEFT", "Pico NOTE LEFT0", 24, false, {})
    character.animation:addOffset("singLEFT", -86, -10)

    character.animation:addByPrefix("singRIGHT", "Pico Note Right0", 24, false, {})
    character.animation:addOffset("singRIGHT", 61, 2)

    character.animation:play("idle", true)

    character.barColor = Color.new(183, 216, 85, 255)
end