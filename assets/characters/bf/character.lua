function onCreateCharacter(character)
    character.flipX = not character.flipX

    character.animation:addByPrefix("idle" ,"BF idle dance", 24, false, {})
    character.animation:addOffset("idle", -5, 0)

    character.animation:addByPrefix("singDOWN" ,"BF NOTE DOWN0", 24, false, {})
    character.animation:addOffset("singDOWN", -20, -51)

    character.animation:addByPrefix("singUP" ,"BF NOTE UP0", 24, false, {})
    character.animation:addOffset("singUP", -46, 27)

    local right = flipX and "singLEFT" or "singRIGHT"
    character.animation:addByPrefix(right ,"BF NOTE RIGHT0", 24, false, {})
    character.animation:addOffset(right, -48, -7)

    local left = flipX and "singRIGHT" or "singLEFT"
    character.animation:addByPrefix(left ,"BF NOTE LEFT0", 24, false, {})
    character.animation:addOffset(left, 5, -6)

    character.animation:play("idle", true)


    character.barColor = Color.new(49, 176, 209, 255)
end