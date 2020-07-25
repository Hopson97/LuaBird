#include <SFML/Graphics.hpp>

#include <iostream>

extern "C" {
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
}

bool luaOk(lua_State* L, int result)
{
    if (!result == LUA_OK) {
        auto message = lua_tostring(L, -1);
        std::cout << "Error: " << message << std::endl;
        return false;
    }
    return true;
}

// Rectangle.new(width, height, x, y)
int lua_Rectangle_new(lua_State* L) 
{
    sf::RectangleShape* s = new sf::RectangleShape();
    *(void **)lua_newuserdata(L, sizeof(void *)) = s;

    float w = (float)luaL_checknumber(L, -1);
    float h = (float)luaL_checknumber(L, -1);
    float x = (float)luaL_checknumber(L, -1);
    float y = (float)luaL_checknumber(L, -1);
    std::cout << x << " " << y << " " << w << " " << h << std::endl;
    sf::RectangleShape* test =
        (sf::RectangleShape*)(lua_newuserdata(L, sizeof(sf::RectangleShape)));
    new (test) sf::RectangleShape();
    test->setPosition({x, y});
    test->setSize({x, y});


    luaL_getmetatable(L, "Rectangle");
    lua_setmetatable(L, -2);
    return 1;
}

const luaL_Reg lua_rectLib[] = {
    {"new", lua_Rectangle_new},
    {NULL, NULL},
};

const luaL_Reg lua_rectMethods[] = {
   // {"print", lua_MetaTest_print},
    {NULL, NULL},
};

void openLibRectangle(lua_State* L)
{
    luaL_newmetatable(L, "Rectangle");
    lua_pushvalue(L, -1);



    
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, lua_rectMethods, 0);
    luaL_newlib(L, lua_rectLib);
    lua_setglobal(L, "Rectangle");
}

struct Printer {
    void print(int a, int b)
    {
    std::cout << "Meta test: " << a << " " << b << std::endl;

    }
};

struct MetaTest {
    int a = 0;
    int b = 0;
    Printer printer;
};

int lua_MetaTest_new(lua_State* L)
{
    int a = (int)luaL_checkinteger(L, -1);
    int b = (int)luaL_checkinteger(L, -1);
    MetaTest* test = (MetaTest*)(lua_newuserdata(L, sizeof(MetaTest)));
    test->a = a;
    test->b = b;

    luaL_getmetatable(L, "MetaTest");
    lua_setmetatable(L, -2);

    return 1;
}

int lua_MetaTest_print(lua_State* L)
{
    MetaTest* metaTest = (MetaTest*)luaL_checkudata(L, 1, "MetaTest");
    metaTest->printer.print(metaTest->a, metaTest->b);
    return 0;
}

const luaL_Reg metaTestLib[] = {
    {"new", lua_MetaTest_new},
    {NULL, NULL},
};

const luaL_Reg metaTestMethods[] = {
    {"print", lua_MetaTest_print},
    {NULL, NULL},
};

void open_MetaTest(lua_State* L)
{
    luaL_newmetatable(L, "MetaTest");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, metaTestMethods, 0);
    luaL_newlib(L, metaTestLib);
    lua_setglobal(L, "MetaTest");
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // lua_register(L, "functionInCPP", lua_functionInCPP);

    open_MetaTest(L);
    openLibRectangle(L);

    sf::RectangleShape* test =
        (sf::RectangleShape*)(malloc(sizeof(sf::RectangleShape)));
    *new (test) sf::RectangleShape();
    test->setPosition({5, 5});
    test->setSize({5, 5});
    free(test);

    if (luaOk(L, luaL_dofile(L, "game/main.lua"))) {
        /*
        lua_getglobal(L, "doStuff");
        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, 10);
            lua_pushnumber(L, 5);

            if (luaOk(L, lua_pcall(L, 2, 1, 0))) {
                std::cout << "C++ Called" << lua_tonumber(L, -1) << "\n";
            }
        }

        lua_getglobal(L, "test");
        if (lua_istable(L, -1)) {
            lua_pushstring(L, "name");
            lua_gettable(L, -2);
            test.name = lua_tostring(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "by");
            lua_gettable(L, -2);
            test.by = lua_tostring(L, -1);
            lua_pop(L, 1);

            std::cout << test.name << ", by " << test.by <<  std::endl;
        }
        */
    }

    // Cleanup
    lua_close(L);

    /*
    sf::RenderWindow window({ 1280, 720 }, "Lua Bird");

    if (luaOk(L, luaL_dofile(L, "game/main.lua"))) {
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
    */
    return 0;
}