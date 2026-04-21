function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"idle spirit_", 24, false, {})
    character.animation:addOffset("idle", -36.66, -46.66)

    character.animation:addByPrefix("singDOWN" ,"spirit down_", 24, false, {})
    character.animation:addOffset("singDOWN", 28.33, 18.33)

    character.animation:addByPrefix("singUP" ,"up_", 24, false, {})
    character.animation:addOffset("singUP", -36.66, -40.0)

    character.animation:addByPrefix("singRIGHT" ,"right_", 24, false, {})
    character.animation:addOffset("singRIGHT", -36.66, -46.66)

    character.animation:addByPrefix("singLEFT" ,"left_", 24, false, {})
    character.animation:addOffset("singLEFT", -33.33, -46.66)

    character.animation:play("idle")
    character.antialiasing = false
    character.scale.x = 6
    character.scale.y = 6

    character:updateHitbox()
end