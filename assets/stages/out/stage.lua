function onCreateStage(stage)
    Game.defaultCamera.zoom = 0.7

    local stagePath = "assets/stages/out/"

    local sky = Sprite.new(400, 300)
    sky:loadTexture(stagePath.."sky.png")
    sky.antialiasing = false
    sky.scale = Vector2.new(6, 6)
    sky.scrollFactor = Vector2.new(0.1, 0.1)
    sky:updateHitbox()
    stage:add(sky)

    local city = Sprite.new(400, 390)
    city:loadTexture(stagePath.."mount.png")
    city.antialiasing = false
    city.scale = Vector2.new(6, 6)
    city.scrollFactor = Vector2.new(0.4, 0.4)
    city:updateHitbox()
    stage:add(city)

    local tree_b = Sprite.new(400, 480)
    tree_b:loadTexture(stagePath.."tree_b.png")
    tree_b.antialiasing = false
    tree_b.scale = Vector2.new(6, 6)
    tree_b.scrollFactor = Vector2.new(0.6, 0.6)
    tree_b:updateHitbox()
    stage:add(tree_b)

    local tree_a = Sprite.new(400, 520)
    tree_a:loadTexture(stagePath.."tree_a.png")
    tree_a.antialiasing = false
    tree_a.scale = Vector2.new(6, 6)
    tree_a.scrollFactor = Vector2.new(0.8, 0.8)
    tree_a:updateHitbox()
    stage:add(tree_a)

    local gr = Sprite.new(200, 498)
    gr:loadTexture(stagePath.."ground.png")
    gr.antialiasing = false
    gr.scale = Vector2.new(6, 6)
    gr:updateHitbox()
    stage:add(gr)


    Stage.snapToPosition(boyfriend, 1700, 1500)
    stage:add(boyfriend)

    Stage.snapToPosition(dad, 1700, 1500)
    dad.drawHitbox = true
    stage:add(dad)
end

function onUpdatePost(delta)
    dad.angle = dad.angle + delta * 10
end