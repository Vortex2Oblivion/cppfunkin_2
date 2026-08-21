function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.585

    local stagePath = "assets/stages/qtStageCityErect/"

    local sky = Sprite.new(-973, -1076)
    sky:loadTexture(stagePath.."sky.png")
    stage:add(sky)

    local stars = Sprite.new(-685, -600)
    stars:loadTexture(stagePath.."stars.png")
    stars.scrollFactor.x = 0.7
    stars.scrollFactor.y = 0.7
    stars.animation:loadSparrow(stagePath.."poster.xml")
    stars.animation:addByPrefix("stars", "stars", 24, true, {})
    stars.animation:play("stars", true)
    stage:add(stars)

    local bgBuildings2 = Sprite.new(-606, -671)
    bgBuildings2:loadTexture(stagePath.."bgBuildings2.png")
    bgBuildings2.scrollFactor.x = 0.8
    bgBuildings2.scrollFactor.y = 0.8
    stage:add(bgBuildings2)

    local building = Sprite.new(-1075, -835)
    building:loadTexture(stagePath.."bgBuilding.png")
    building.scrollFactor.x = 0.75
    building.scrollFactor.y = 0.75
    stage:add(building)

    local sign = Sprite.new(30, -425)
    sign:loadTexture(stagePath.."signBetterCallSahur.png")
    sign.scrollFactor.x = 0.85
    sign.scrollFactor.y = 0.85
    stage:add(sign)

    local storeBg = Sprite.new(-989, 446)
    storeBg:loadTexture(stagePath.."storeBg.png")
    storeBg.scale.x = 1.0057
    storeBg.scale.y = 1.0057
    stage:add(storeBg)

    local storeInterior = Sprite.new(-985, 437)
    storeInterior:loadTexture(stagePath.."storeInterior.png")
    storeInterior.scrollFactor.x = 0.95
    storeInterior.scrollFactor.y = 0.95
    storeInterior.scale.x = 0.6663
    storeInterior.scale.y = 0.6663
    stage:add(storeInterior)

    local lampAndBuilding = Sprite.new(875, 125)
    lampAndBuilding:loadTexture(stagePath.."lampAndBuilding.png")
    lampAndBuilding.scrollFactor.x = 0.8
    lampAndBuilding.scrollFactor.y = 0.8
    stage:add(lampAndBuilding)

    local mainGround = Sprite.new(-992, -305)
    mainGround:loadTexture(stagePath.."mainGround.png")
    stage:add(mainGround)

    local storeLight_add = Sprite.new(-1249, 161)
    storeLight_add:loadTexture(stagePath.."storeLightAdd.png")
    storeLight_add.alpha = 0.7
    storeLight_add.blend = BlendMode.BLEND_ADDITIVE
    stage:add(storeLight_add)

    local flower = Sprite.new(-56, 1080)
    flower:loadTexture(stagePath.."flower.png")
    flower.animation:loadSparrow(stagePath.."flower.xml")
    flower.animation:addByPrefix("flower", "flower", 24, true, {})
    flower.animation:play("flower", true)
    stage:add(flower)

    local grass = Sprite.new(1598, 1115)
    grass:loadTexture(stagePath.."grass.png")
    grass.animation:loadSparrow(stagePath.."grass.xml")
    grass.animation:addByPrefix("grass", "grass", 24, true, {})
    grass.animation:play("grass", true)
    stage:add(grass)

    local poster = Sprite.new(1665, 846)
    poster:loadTexture(stagePath.."poster.png")
    poster.animation:loadSparrow(stagePath.."poster.xml")
    poster.animation:addByPrefix("poster", "poster", 24, true, {})
    poster.animation:play("poster", true)
    stage:add(poster)

    Stage.snapToPosition(girlfriend, 820, 1164)
    stage:add(girlfriend)

    Stage.snapToPosition(boyfriend, 1330, 1285)
    stage:add(boyfriend)

    Stage.snapToPosition(dad, 305, 1289)
    stage:add(dad)

    local bfShader = Shader.new("assets/shaders/dropShadow.fs")
    print(ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("hue", -25.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("saturation", -20.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("brightness", -40.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("ang", 45.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("dist", 13.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("str", 1.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("thr", 0.1, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("AA_STAGES", 2.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("dropColor", raylib.ColorNormalize(Color.new(225, 157, 151, 255)), ShaderUniformDataType.SHADER_UNIFORM_VEC3)
    bfShader:setValue("textureSize", Vector2.new(boyfriend.texture.width, boyfriend.texture.height), ShaderUniformDataType.SHADER_UNIFORM_VEC2)
    bfShader:setValue("uFrameBounds", Vector4.new(0.0, 0.0, boyfriend.texture.width, boyfriend.texture.height), ShaderUniformDataType.SHADER_UNIFORM_VEC4)
    boyfriend.shaders = {bfShader}

    local dadShader = Shader.new("assets/shaders/dropShadow.fs")
    dadShader:setValue("hue", -25.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("saturation", -20.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("brightness", -40.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("ang", 180.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("dist", 13.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("str", 1.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("thr", 0.1, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("AA_STAGES", 2.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("dropColor", raylib.ColorNormalize(Color.new(200, 99, 185, 255)), ShaderUniformDataType.SHADER_UNIFORM_VEC3)
    dadShader:setValue("textureSize", Vector2.new(dad.texture.width, dad.texture.height), ShaderUniformDataType.SHADER_UNIFORM_VEC2)
    dadShader:setValue("uFrameBounds", Vector4.new(0.0, 0.0, dad.texture.width, dad.texture.height), ShaderUniformDataType.SHADER_UNIFORM_VEC4)
    dad.shaders = {dadShader}

    local gfShader = Shader.new("assets/shaders/dropShadow.fs")
    gfShader:setValue("hue", -25.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    gfShader:setValue("saturation", -20.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    gfShader:setValue("brightness", -40.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    girlfriend.shaders = {gfShader}

    local car = Sprite.new(-1048, 810)
    car:loadTexture(stagePath.."car.png")
    car.scrollFactor.x = 1.03
    car.scrollFactor.y = 1.03
    stage:add(car)

    local overlayAdd = Sprite.new(-1242, -1060)
    overlayAdd:loadTexture(stagePath.."overlayAdd.png")
    overlayAdd.scrollFactor.x = 1.03
    overlayAdd.scrollFactor.y = 0.5
    overlayAdd.blend = BlendMode.BLEND_ADDITIVE
    overlayAdd.alpha = 0.15
    stage:add(overlayAdd)
end