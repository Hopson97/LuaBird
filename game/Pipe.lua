local PIPE_GAP = 150
local PIPE_WIDTH = 50
local WIDTH = 1280
local HEIGHT = 720

Pipe = {}
Pipe.__index = Pipe

local function randHeight()
	return math.random(PIPE_GAP, HEIGHT / 2) - HEIGHT
end

function Pipe:new(index)
	local pipe = {}
	setmetatable(pipe, Pipe)

	local height = randHeight();
	pipe.top = newSprite(PIPE_WIDTH, HEIGHT, 0, 0)
	pipe.bottom = newSprite(PIPE_WIDTH, HEIGHT, 0, 0)
	pipe.dirty = false

	pipe.top:setTexture("res/pipe.png")
	pipe.bottom:setTexture("res/pipe.png")

	pipe:reset(index)
	return pipe
end

function Pipe:xPos()
	local x, y = self.top:getPosition()
	return x
end

function Pipe:update(dt)
	self.top:move(-200 * dt, 0)
	self.bottom:move(-200 * dt, 0)
	if self:xPos() < -PIPE_WIDTH then
		self.reset(self, 3)
	end
end

function Pipe:reset(index)
	local height = randHeight();
	local x = WIDTH + PIPE_GAP * 3 * index;
	self.top:setPosition(x, height)
	self.bottom:setPosition(x, height + PIPE_GAP + HEIGHT)
	self.dirty = false
end