function onCreatePost()
    local parsedSong = parseSong("bonedoggle-sans", "hard")
    local extraField = PlayField.new(0, 50, 4, 2.6, parsedSong.opponentNotes, conductor)
    extraField.camera = camHUD
    extraField.botplay = true
    extraField.scale = Vector2.new(0.9, 0.9)
    add(extraField)

    playerField.scale = extraField.scale
    opponentField.scale = extraField.scale

    opponentField.position.x = 450
    playerField.position.x = 875
end