function onCreateStage(stage)
    Game.defaultCamera.backgroundColor = Color.new(34, 32, 38, 255)
    Game.defaultCamera.zoom = 0.85

    local crowd = Sprite.new(682, 290)
    crowd:loadTexture("assets/stages/mainStageErect/crowd.png")
    crowd.animation:loadSparrow("assets/stages/mainStageErect/crowd.xml")
    crowd.animation:addByPrefix("idle" ,"idle", 12, true, {})
    crowd.animation:play("idle", true)
    crowd.scrollFactor.x = 0.8
    crowd.scrollFactor.y = 0.8
    stage:add(crowd)

    local brightLightSmall = Sprite.new(967, -103)
    brightLightSmall:loadTexture("assets/stages/mainStageErect/brightLightSmall.png")
    brightLightSmall.scrollFactor.x = 1.2
    brightLightSmall.scrollFactor.y = 1.2
    brightLightSmall.blend = BlendMode.BLEND_ADDITIVE
    stage:add(brightLightSmall)

    local bg = Sprite.new(-765, -247)
    bg:loadTexture("assets/stages/mainStageErect/bg.png")
    stage:add(bg)

    local server = Sprite.new(-991, 205)
    server:loadTexture("assets/stages/mainStageErect/server.png")
    stage:add(server)

    local lightgreen = Sprite.new(-171, 242)
    lightgreen:loadTexture("assets/stages/mainStageErect/lightgreen.png")
    lightgreen.blend = BlendMode.BLEND_ADDITIVE
    stage:add(lightgreen)

    local lightred = Sprite.new(-101, 560)
    lightred:loadTexture("assets/stages/mainStageErect/lightred.png")
    lightred.blend = BlendMode.BLEND_ADDITIVE
    stage:add(lightred)

    local orangeLight = Sprite.new(189, -500)
    orangeLight:loadTexture("assets/stages/mainStageErect/orangeLight.png")
    orangeLight.scale.y = 1700
    orangeLight.blend = BlendMode.BLEND_ADDITIVE
    stage:add(orangeLight)

    Stage.snapToPosition(girlfriend, 501.5, 815)
    stage:add(girlfriend)

    Stage.snapToPosition(dad, 40, 885)
    stage:add(dad)

    Stage.snapToPosition(boyfriend, 977.5, 905)
    stage:add(boyfriend)

    local gfShader = Shader.new("assets/shaders/adjustColor.fs")
    gfShader:setValue("brightness", -30.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    gfShader:setValue("hue", -9.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    gfShader:setValue("contrast", -4.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    gfShader:setValue("saturation", 0.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    girlfriend.shaders = {gfShader}

    local dadShader = Shader.new("assets/shaders/adjustColor.fs")
    dadShader:setValue("brightness", -33.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("hue", -32.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("contrast", -23.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dadShader:setValue("saturation", 0.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    dad.shaders = {dadShader}

    local bfShader = Shader.new("assets/shaders/adjustColor.fs")
    bfShader:setValue("brightness", -23.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("hue", 12.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("contrast", 7.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    bfShader:setValue("saturation", 0.0, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    boyfriend.shaders = {bfShader}

    local lights = Sprite.new(-847, -245)
    lights:loadTexture("assets/stages/mainStageErect/lights.png")
    stage:add(lights)

    local lightAbove = Sprite.new(804, -117)
    lightAbove:loadTexture("assets/stages/mainStageErect/lightAbove.png")
    lightAbove.blend = BlendMode.BLEND_ADDITIVE
    stage:add(lightAbove)
end