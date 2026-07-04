function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.77

    local stagePath = "assets/stages/phillyStreetsErect/"

    local phillySkyline = Sprite.new(-545, -273)
    phillySkyline.scrollFactor.x = 0.2
    phillySkyline.scrollFactor.y = 0.2
    phillySkyline:loadTexture(stagePath.."phillySkyline.png")
    stage:add(phillySkyline)

    local phillyForegroundCity = Sprite.new(600, 69)
    phillyForegroundCity.scrollFactor.x = 0.3
    phillyForegroundCity.scrollFactor.y = 0.3
    phillyForegroundCity:loadTexture(stagePath.."phillyForegroundCity.png")
    stage:add(phillyForegroundCity)

    local phillyForegroundCity2 = Sprite.new(1860, 185)
    phillyForegroundCity2.scrollFactor.x = 0.3
    phillyForegroundCity2.scrollFactor.y = 0.3
    phillyForegroundCity2.angle = 5
    phillyForegroundCity2:loadTexture(stagePath.."phillyForegroundCity.png")
    stage:add(phillyForegroundCity)

    local phillyConstruction2 = Sprite.new(1795, 360)
    phillyConstruction2.scrollFactor.x = 0.7
    phillyConstruction2.scrollFactor.y = 1
    phillyConstruction2:loadTexture(stagePath.."phillyConstruction.png")
    stage:add(phillyConstruction2)

    local phillyHighwayLights = Sprite.new(122, 201)
    phillyHighwayLights.scrollFactor.x = 0.8
    phillyHighwayLights.scrollFactor.y = 0.8
    phillyHighwayLights:loadTexture(stagePath.."phillyHighwayLights.png")
    stage:add(phillyHighwayLights)

    local phillyHighwayLights_lightmap = Sprite.new(122, 201)
    phillyHighwayLights_lightmap.scrollFactor.x = 0.8
    phillyHighwayLights_lightmap.scrollFactor.y = 0.8
    phillyHighwayLights_lightmap:loadTexture(stagePath.."phillyHighwayLights_lightmap.png")
    stage:add(phillyHighwayLights_lightmap)

    local phillyHighway2 = Sprite.new(-23, 105)
    phillyHighway2.scrollFactor.x = 0.8
    phillyHighway2.scrollFactor.y = 0.8
    phillyHighway2:loadTexture(stagePath.."phillyHighway.png")
    stage:add(phillyHighway2)

    local grey1 = Sprite.new(-388, 7)
    grey1.scale.x = 1.3
    grey1.scale.y = 1.3
    grey1.alpha = 0.3
    grey1:loadTexture(stagePath.."greyGradient.png")
    stage:add(grey1)

    local grey2 = Sprite.new(-388, 7)
    grey2.scale.x = 1.3
    grey2.scale.y = 1.3
    grey2.alpha = 0.8
    grey2:loadTexture(stagePath.."greyGradient.png")
    stage:add(grey2)

    local phillyForeground = Sprite.new(88, 317)
    phillyForeground:loadTexture(stagePath.."phillyForeground.png")
    stage:add(phillyForeground)

    boyfriend.position.x = 1930
    boyfriend.position.y = 450

    dad.position.x = 610
    dad.position.y = 430

    stage:add(boyfriend)
    stage:add(dad)
end