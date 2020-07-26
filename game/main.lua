local BOOST = 300
local WIDTH = 1280
local HEIGHT = 720

dofile("game/Pipe.lua");

math.randomseed(os.time())



-- Set up the background layer
local background = newSprite(WIDTH, HEIGHT, 0, 0)
background:setTexture("res/bg.png");

local city = {
	newSprite(WIDTH, 256, 0, HEIGHT - 256),
	newSprite(WIDTH, 256, WIDTH, HEIGHT - 256)
}
for k, v in pairs(city) do
	v:setTexture("res/city.png");
end

-- Set up the foregorund layer
local pipes = {
	Pipe:new(0),
	Pipe:new(1),
	Pipe:new(2),
	Pipe:new(3),
	Pipe:new(4),
}

local grass = {
	newSprite(WIDTH, 64, 0, HEIGHT - 64),
	newSprite(WIDTH, 64, WIDTH, HEIGHT - 64)
}
for k, v in pairs(grass) do
  v:setTexture("res/grass.png");
end

-- Set up the player
local bird = {
	sprite = newSprite(64, 32, 100, 100),
	vx = 0,
	vy = 0
}

bird.sprite:setTexture("res/bird.png");

-- Parallax scrolling
local function parallax(table, speed, dt)
	for _, v in pairs(table) do
	  v:move(-speed * dt, 0)
	  local x, y = v:getPosition()
	  if x < -WIDTH then
		v:move(WIDTH * 2, 0)
	  end
	end
end

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

	for _, pipe in pairs(pipes) do
	  pipe:update(dt)
	end

	parallax(grass, 200, dt)
	parallax(city, 100, dt)
end