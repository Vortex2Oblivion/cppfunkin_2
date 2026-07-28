function onCreatePost()
    local parsedSong = parseSong("bonedoggle-sans", "hard")
    local extraField = PlayField.new(100, 100, 4, 2.6, parsedSong.opponentNotes, conductor)
    extraField.camera = camHUD
    extraField.botplay = true
    extraField.scale = Vector2.new(0.899553571429, 0.899553571429)
    add(extraField)
    playerField.scale = extraField.scale
    opponentField.scale = extraField.scale
end