function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"idle", 13, false, {})

    character.animation:addByPrefix("singUP", "up", 13, false, {})
    character.animation:addByPrefix("singDOWN", "down", 13, false, {})
    character.animation:addByPrefix("singLEFT", "left", 13, false, {})
    character.animation:addByPrefix("singRIGHT", "right", 13, false, {})

    character.scale = Vector2.new(6, 6)
    character.antialiasing = false
    character:updateHitbox()

    character.cameraOffset = Vector2.new(210, 180)
    character.animation:play("idle")
end