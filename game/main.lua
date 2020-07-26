local BOOST = 500

local wall = newSprite(64, 500, 500, 0)

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
end