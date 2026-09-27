local dancers = {}

function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.9

    local stagePath = "assets/stages/limoRide/"

    local limoSunset = Sprite.new(-120, -50)
    limoSunset:loadTexture(stagePath.."limoSunset.png")
    limoSunset.scrollFactor = Vector2.new(0.1, 0.1)
    stage:add(limoSunset)

    local bgLimo = Sprite.new(-200, 480)
    bgLimo:loadTexture(stagePath.."bgLimo.png")
    bgLimo.animation:loadSparrow(stagePath.."bgLimo.xml")
    bgLimo.animation:addByPrefix("drive", "background limo pink", 24, true, {})
    bgLimo.animation:play("drive", true)
    bgLimo.scrollFactor = Vector2.new(0.4, 0.4)
    stage:add(bgLimo)

    local maxDancers = 5

    for i = 0, maxDancers - 1 do
        local limoDancer = Sprite.new(100 + ((300 / maxDancers) * 5) * i, 100)
        limoDancer:loadTexture(stagePath.."henchmen.png")
        limoDancer.animation:loadSparrow(stagePath.."henchmen.xml")
        limoDancer.animation:addByPrefix("danceLeft", "hench dancing", 24, false, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14})
        limoDancer.animation:addByPrefix("danceRight", "hench dancing", 24, false, {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29})
        limoDancer.animation:play("danceLeft", true)
        limoDancer.scrollFactor = Vector2.new(0.4, 0.4)
        stage:add(limoDancer)
        table.insert(dancers, limoDancer)
    end

    Stage.snapToPosition(girlfriend, 787, 779)
    stage:add(girlfriend)

    local limoDrive = Sprite.new(-120, 528)
    limoDrive:loadTexture(stagePath.."limoDrive.png")
    limoDrive.animation:loadSparrow(stagePath.."limoDrive.xml")
    limoDrive.animation:addByPrefix("drive", "background stage", 24, true, {})
    limoDrive.animation:play("drive", true)
    stage:add(limoDrive)


    Stage.snapToPosition(dad, 329.5, 913)
    stage:add(dad)

    Stage.snapToPosition(boyfriend, 1217.5, 592)
    stage:add(boyfriend)

    local limoOverlay = Sprite.new(-720, -720)
    limoOverlay:loadTexture(stagePath.."limoOverlay.png")
    limoOverlay.blend = BlendMode.BLEND_MULTIPLIED
    stage:add(limoOverlay)
end

function onBeatHit(beat)
    for i, dancer in ipairs(dancers) do
        if beat % 2 == 0 then
            dancer.animation:play("danceLeft", true)
        else
            dancer.animation:play("danceRight", true)
        end
    end
end