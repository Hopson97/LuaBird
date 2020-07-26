local wall = newSprite(100, 300, 500, 100)

local bird = {
	sprite = newSprite(100, 100, 100, 100),
	vx = 0,
	vy = 0
}

bird.sprite:setTexture("res/bird.png");

function update()
	if Keyboard.isKeyPressed("A") then
		bird.vx = bird.vx - 1
	elseif Keyboard.isKeyPressed("D") then
		bird.vx = bird.vx + 1
	end

	if Keyboard.isKeyPressed("W") then
		bird.vy = bird.vy - 1
	elseif Keyboard.isKeyPressed("S") then
		bird.vy = bird.vy + 1
	end

	bird.sprite:move(bird.vx, bird.vy)
	bird.vx = bird.vx * 0.95
	bird.vy = bird.vy * 0.95
end