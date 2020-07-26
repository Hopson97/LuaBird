
-- Globals to be accessed via the C++ code
sprites = {}

-- Util functions
local function newSprite(width, height, x, y)
	local sprite = Sprite.new(width, height, x, y);
	table.insert(sprites, sprite);
	return sprite;
end






local sprite = newSprite(100, 100, 100, 100)
local sprite2 = newSprite(100, 300, 500, 100)


function update()
	sprite:move(1, 0);

	if sprite:intersects(sprite2) then
		print("Intersecting...");
	end
end