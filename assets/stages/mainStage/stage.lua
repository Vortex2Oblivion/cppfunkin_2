function onCreateStage(stage)
    Game.defaultCamera.zoom = 1.1

    local stageback = Sprite.new(-600, -200)
    stageback:loadTexture("assets/stages/mainStage/stageback.png")
    stageback.scrollFactor.x = 0.9
    stageback.scrollFactor.y = 0.9
    stage:add(stageback)

    local stagefront = Sprite.new(-650, 600)
    stagefront:loadTexture("assets/stages/mainStage/stagefront.png")
    stagefront.scrollFactor.x = 0.9
    stagefront.scrollFactor.y = 0.9
    stagefront.scale.x = 1.1
    stagefront.scale.y = 1.1
    stage:add(stagefront)

    Stage.snapToPosition(girlfriend, 751.5, 787)
    stage:add(girlfriend)

    Stage.snapToPosition(dad, 335, 885)
    stage:add(dad)

    Stage.snapToPosition(boyfriend, 989.5, 885)
    stage:add(boyfriend)

    local stagecurtains = Sprite.new(-500, -300)
    stagecurtains:loadTexture("assets/stages/mainStage/stagecurtains.png")
    stagecurtains.scrollFactor.x = 1.3
    stagecurtains.scrollFactor.y = 1.3
    stagecurtains.scale.x = 0.9
    stagecurtains.scale.y = 0.9
    stage:add(stagecurtains)

end