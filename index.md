DeltaEngine
===========
__DeltaEngine is a 2d engine made with [SFML](sfml-dev.org "SFML") (window,render,sound) and [Box2D](box2d.ord "Box2D") (physics).__

> The doc is [here](doc/annotated.html).

It uses multiples classes, firstly [Game](), that contains infos about your project (name, version, debug/release mode, etc...) and your [Objects](),
[Entities](), [Lights]() and [Shaders]().
This class draws everything on the window too.

[Objects]() and [Entities]() are pretty the same, but [Entities]() can move and [Objects]() are statics.
They're containers of [Parts]().

[Parts]() are a combination of a texture ([SFML](sfml-dev.org "SFML")) and an hitbox ([Box2D](box2d.ord "Box2D")).
They can be animated and [Shaders]() can be applied on.
 
[Lights]() enlight the scene. They can be circular or directional and you can change their color and brightness.
 
[ShaderManagers]() manage and stock all your [Shaders]().
They're accessible by their index.

Made by [EnderRayquaza](https://github.com/EnderRayquaza, "My Github") / Under MIT Licence. <br/>
Copyright DeltaEngine belong to EnderRayquaza. <br/>
You must quote me if your use my work. Thx. <br/>
