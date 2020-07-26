local BOOST = 300
local WIDTH = 1280
local HEIGHT = 720

dofile("game/Pipe.lua");

math.randomseed(os.time())

local background = newSprite(WIDTH, HEIGHT, 0, 0)
background:setTexture("res/bg.png");

local pipes = {
	Pipe:new(0),
	Pipe:new(1),
	Pipe:new(2),
	Pipe:new(3),
	Pipe:new(4),
}

local grassForeground = {
	newSprite(WIDTH, 64, 0, HEIGHT - 64),
	newSprite(WIDTH, 64, WIDTH, HEIGHT - 64)
}
for k, grass in pairs(grassForeground) do
  grass:setTexture("res/grass.png");
end

local bird = {
	sprite = newSprite(64, 32, 100, 100),
	vx = 0,
	vy = 0
}

bird.sprite:setTexture("res/bird.png");

-- Function called once per frame from C++ side
function update(dt)
	if Keyboard.isKeyPressed("W") and bird.vy > 0 then
		bird.vy = -BOOST * dt
	end

	local x, y = bird.sprite:getPosition()
	if y < 0 then
		bird.sprite:move(0, -y)
		bird.vy = 0
	end

	bird.vy = bird.vy + 10 * dt

	bird.sprite:move(bird.vx, bird.vy)
	bird.vx = bird.vx * 0.99 
	bird.vy = bird.vy * 0.99

	for k, pipe in pairs(pipes) do
	  pipe:update(dt)
	end

	for k, pipe in pairs(foreground) do
	  v:move(-200 * dt, 0)
	  local x, y = v:getPosition()
	  if x < -WIDTH then
		v:move(WIDTH * 2, 0)
	  end
	end
end