function onCreatePost()
    local shader = Shader.new("assets/shaders/glitch.fs")
    shader:setValue("blur", 0.12, ShaderUniformDataType.SHADER_UNIFORM_FLOAT)
    Game.defaultCamera.shaders = {shader};
    camHUD.shaders = {shader};
end