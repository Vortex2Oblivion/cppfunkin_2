function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.8

    local sky = Sprite.new(-600, -200)
    sky:loadTexture("assets/stages/alley/sky.png")
    sky.scrollFactor.x = 00
    sky.scrollFactor.y = 0
    stage:add(sky)

    boyfriend.position.x = 1600
    boyfriend.position.y = 525
    stage:add(boyfriend)

    dad.position.x = 600
    dad.position.y = 525
    stage:add(dad)
end