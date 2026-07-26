function onCreateStage(stage)
    Game.defaultCamera.zoom = 1.1

    local stagePath = "assets/stages/qtStageCityErect/"

    local sky = Sprite.new(-973, -1076)
    sky:loadTexture(stagePath.."signBetterCallSahur.astc")
    stage:add(sky)


    boyfriend.position.x = 700
    boyfriend.position.y = 100
    stage:add(boyfriend)

    dad.position.x = 100
    dad.position.y = 100
    stage:add(dad)
end