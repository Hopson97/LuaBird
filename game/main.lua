local BOOST = 300
local WIDTH = 1280
local HEIGHT = 720
local PIPE_GAP = 128

local pipes = {}

math.randomseed(os.time())

local function addPipes(index)
	local height = math.random(PIPE_GAP, HEIGHT / 2) - HEIGHT
	table.insert(pipes, {
		top = {
			sprite = newSprite(32, HEIGHT, WIDTH / 2 + 64 * 8 * index, height),
		},
		bottom = {
			sprite = newSprite(32, HEIGHT,  WIDTH / 2 + 64 * 8 * index, height + PIPE_GAP + HEIGHT),
		}
	})
end		

addPipes(0)
addPipes(1)
addPipes(2)


local bird = {
	sprite = newSprite(64, 64, 100, 100),
	vx = 0,
	vy = 0
}


bird.sprite:setTexture("res/bird.png");

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

	for k, v in pairs(pipes) do
	  v.top.sprite:move(-200 * dt, 0)
	  v.bottom.sprite:move(-200 * dt, 0)

	end

end