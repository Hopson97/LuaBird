local PIPE_GAP = 128
local PIPE_WIDTH = 32
local WIDTH = 1280
local HEIGHT = 720

Pipe = {}
Pipe.__index = Pipe

local function randHeight()
	return math.random(PIPE_GAP, HEIGHT / 2) - HEIGHT
end

local function resetPipe(pipe, index)
	local height = randHeight();
	local x = WIDTH / 2 + PIPE_GAP * 3 * index;
	pipe.top:setPosition(x, height)
	pipe.bottom:setPosition(x, height + PIPE_GAP + HEIGHT)
end

function Pipe:new(index)
	local props = {}
	setmetatable(props, Pipe)

	print("Created pipe")

	local height = randHeight();
	props.top = newSprite(PIPE_WIDTH, HEIGHT, 0, 0)
	props.bottom = newSprite(PIPE_WIDTH, HEIGHT, 0, 0)
	resetPipe(props, index)
	return props
end

function Pipe:update(dt)
	self.top:move(-200 * dt, 0)
	self.bottom:move(-200 * dt, 0)
	local x, y = self.top:getPosition()
	if x < -PIPE_WIDTH then
		resetPipe(self, 3)
	end
end