local lightColors = {
    Color.new(49, 162, 253, 255),
    Color.new(49, 253, 140, 255),
    Color.new(251, 51, 245, 255),
    Color.new(35, 166, 51, 255),
    Color.new(253, 69, 49, 255)
}

local win = nil

function onCreateStage(stage)
    Game.defaultCamera.zoom = 1.1

    local stagePath = "assets/stages/phillyTrain/"

    local sky = Sprite.new(-100, 0)
    sky:loadTexture(stagePath.."sky.png")
    sky.scrollFactor = Vector2.new(0.1, 0.1)
    stage:add(sky)

    local city = Sprite.new(-255, 45)
    city:loadTexture(stagePath.."city.png")
    city.scrollFactor = Vector2.new(0.3, 0.3)
    stage:add(city)

    win = Sprite.new(-184, 155)
    win:loadTexture(stagePath.."win.png")
    win.scrollFactor = Vector2.new(0.3, 0.3)
    stage:add(win)

    local behindTrain = Sprite.new(-299, 144)
    behindTrain:loadTexture(stagePath.."behindTrain.png")
    stage:add(behindTrain)

    local train = Sprite.new(2000, 360)
    train:loadTexture(stagePath.."train.png")
    stage:add(train)

    local street = Sprite.new(-299, 144)
    street:loadTexture(stagePath.."street.png")
    stage:add(street)

    Stage.snapToPosition(girlfriend, 751.5, 787)
    stage:add(girlfriend)

    Stage.snapToPosition(dad, 468, 885)
    stage:add(dad)

    Stage.snapToPosition(boyfriend, 1020.5, 885)
    stage:add(boyfriend)
end

function onBeatHit(beat)
    if beat % 4 == 0 then
        win.color = lightColors[raylib.GetRandomValue(1, #lightColors)]
    end
end