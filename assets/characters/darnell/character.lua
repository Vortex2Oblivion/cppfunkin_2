function onCreateCharacter(character)
    character.animation:addByPrefix("idle", "Idle", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singDOWN", "Pose Down", 24, false, {})
    character.animation:addOffset("singDOWN", 0, -10)

    character.animation:addByPrefix("singUP", "Pose Up", 24, false, {})
    character.animation:addOffset("singUP", 0, 0)

    character.animation:addByPrefix("singRIGHT", "Pose Right", 24, false, {})
    character.animation:addOffset("singRIGHT", 0, 2)

    character.animation:addByPrefix("singLEFT", "Pose Left", 24, false, {})
    character.animation:addOffset("singLEFT", 0, 0)

    character.animation:play("idle", true)
    character:updateHitbox()
end