DeltaEngine
===========
__DeltaEngine is a 2d engine made with [SFML](sfml-dev.org "SFML") (window,render,sound) and [Box2D](box2d.ord "Box2D") (physics).__

> The doc is [here](doc/annotated.html "Doc").

It uses multiples classes, firstly [Game](class_delta_engine_1_1_game.html), that contains infos about your project (name, version, debug/release mode, etc...) and your [Objects](class_delta_engine_1_1_object.html), [Entities](class_delta_engine_1_1_entity.html), [Lights](class_delta_engine_1_1_light.html) and [Shaders](class_delta_engine_1_1_shadermanager.html).
This class draws everything on the window too.

[Objects](class_delta_engine_1_1_object.html)(class_delta_engine_1_1_object.html) and [Entities](class_delta_engine_1_1_entity.html) are pretty the same, but [Entities](class_delta_engine_1_1_entity.html) can move and [Objects](class_delta_engine_1_1_object.html) are statics.
They're containers of [Parts](class_delta_engine_1_1_part.html).

[Parts](class_delta_engine_1_1_part.html) are a combination of a texture ([SFML](sfml-dev.org "SFML")) and an hitbox ([Box2D](box2d.ord "Box2D")).
They can be animated and [Shaders](class_delta_engine_1_1_shadermanager.html) can be applied on.
 
[Lights](class_delta_engine_1_1_light.html) enlight the scene. They can be circular or directional and you can change their color and brightness.
 
[ShaderManagers](class_delta_engine_1_1_shadermanager.html) manage and stock all your [Shaders](class_delta_engine_1_1_shadermanager.html).
They're accessible by their index.

Made by [EnderRayquaza](https://github.com/EnderRayquaza, "My Github") / Under MIT Licence. <br/>
Copyright DeltaEngine belong to EnderRayquaza. <br/>
You must quote me if your use my work. Thx. <br/>
