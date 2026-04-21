function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.1

    local sky = Sprite.new(-626, -78)
    sky:loadTexture("assets/stages/schoolEvilRemnants/weebSky.png")
    sky.antialiasing = false
    sky.scrollFactor.x = 0.2
    sky.scrollFactor.y = 0.2
    sky.scale.x = 6.0
    sky.scale.y = 6.0
    stage:add(sky)

    local school = Sprite.new(-816, -38)
    school:loadTexture("assets/stages/schoolEvilRemnants/weebSchool.png")
    school.antialiasing = false
    school.scrollFactor.x = 0.2
    school.scrollFactor.y = 0.2
    school.scale.x = 6.0
    school.scale.y = 6.0
    stage:add(school)

    local backTrees = Sprite.new(-842, -80)
    backTrees:loadTexture("assets/stages/schoolEvilRemnants/weebBackTrees.png")
    backTrees.antialiasing = false
    backTrees.scrollFactor.x = 0.5
    backTrees.scrollFactor.y = 0.5
    backTrees.scale.x = 6.0
    backTrees.scale.y = 6.0
    stage:add(backTrees)

    local street = Sprite.new(-662, 6)
    street:loadTexture("assets/stages/schoolEvilRemnants/weebStreet.png")
    street.antialiasing = false
    street.scale.x = 6.0
    street.scale.y = 6.0
    stage:add(street)

    local trees = Sprite.new(-662, 6)
    trees:loadTexture("assets/stages/schoolEvilRemnants/weebTrees.png")
    trees.antialiasing = false
    trees.scale.x = 6.0
    trees.scale.y = 6.0
    stage:add(trees)

    boyfriend.position.x = 1168
    boyfriend.position.y = 900
    stage:add(boyfriend)
    stage:add(dad)
end