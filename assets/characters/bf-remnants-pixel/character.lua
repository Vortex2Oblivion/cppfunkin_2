function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"Idle", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN" ,"D0", 24, false, {})
    character.animation:addOffset("singDOWN", 0, 0)

    character.animation:addByPrefix("singUP" ,"U0", 24, false, {})
    character.animation:addOffset("singUP", 0, 0)

    character.animation:addByPrefix("singRIGHT" ,"R0", 24, false, {})
    character.animation:addOffset("singRIGHT", 0, 0)

    character.animation:addByPrefix("singLEFT" ,"L0", 24, false, {})
    character.animation:addOffset("singLEFT", 0, 0)

    character.animation:play("idle")
    character.antialiasing = false
    character.scale.x = 6
    character.scale.y = 6

    character:updateHitbox()
end