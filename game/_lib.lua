
-- Globals to be accessed via the C++ code
sprites = {}

-- Util functions
function newSprite(width, height, x, y)
	local sprite = Sprite.new(width, height, x, y);
	table.insert(sprites, sprite);
	return sprite;
end