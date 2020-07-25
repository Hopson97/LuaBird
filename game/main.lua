rects = {}

local function newRect(width, height, x, y)
	local rect = Rectangle.new(width, height, x, y);
	table.insert(rects, rect);
	return rect;
end

local rect = Rectangle.new(100, 100, 10, 10)--newRect(100, 100, 10, 10)


function update()

end
