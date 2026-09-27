function onCreateCharacter(character)
    character.animation:addByPrefix("idle" ,"Mom Idle", 24, false, {})
    character.animation:addOffset("idle", 0, 0)

    character.animation:addByPrefix("singLEFT" ,"Mom Left Pose", 24, false, {})
    character.animation:addOffset("singLEFT", 250, -23)

    character.animation:addByPrefix("singUP" ,"Mom Up Pose", 24, false, {})
    character.animation:addOffset("singUP", 14, 71)

    character.animation:addByPrefix("singRIGHT" ,"Mom Pose Left", 24, false, {})
    character.animation:addOffset("singRIGHT", 10, -60)

    character.animation:addByPrefix("singDOWN" ,"MOM DOWN POSE", 24, false, {})
    character.animation:addOffset("singDOWN", 20, -160)

    character.animation:play("idle")

    character.barColor = Color.new(216, 85, 142, 255)
    character.characterIcon = "mom"
end