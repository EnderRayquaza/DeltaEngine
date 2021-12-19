DeltaEngine
===========
__DeltaEngine is a 2d engine made with [SFML](sfml-dev.org "SFML") (window,render,sound) and [Box2D](box2d.ord "Box2D") (physics).__

```diff
- Warning : the doc is not updated, please wait the update (~01/01/2022)
```

> The doc is [here](doc/annotated.html "Doc").

It uses multiples classes, firstly [Game](doc/class_delta_engine_1_1_game.html), that contains infos about your project (name, version, debug/release mode, etc...) and your [Objects](doc/class_delta_engine_1_1_object.html), [Entities](doc/class_delta_engine_1_1_entity.html), [Lights](doc/class_delta_engine_1_1_light.html) and [Shaders](https://www.sfml-dev.org/documentation/2.5.1-fr/classsf_1_1Shader.php).
This class draws everything on the window too.

[Objects](doc/class_delta_engine_1_1_object.html)(class_delta_engine_1_1_object.html) and [Entities](doc/class_delta_engine_1_1_entity.html) are pretty the same, but [Entities](doc/class_delta_engine_1_1_entity.html) can move and [Objects](doc/class_delta_engine_1_1_object.html) are statics.
They're containers of [Parts](doc/class_delta_engine_1_1_part.html).

[Parts](doc/class_delta_engine_1_1_part.html) are a combination of a texture ([SFML](sfml-dev.org "SFML")) and an hitbox ([Box2D](box2d.ord "Box2D")).
They can be animated and [Shaders](https://www.sfml-dev.org/documentation/2.5.1-fr/classsf_1_1Shader.php) can be applied on.
 
[Lights](doc/class_delta_engine_1_1_light.html) enlight the scene. They can be circular or directional and you can change their color and brightness.
 
[ShaderManagers](doc/class_delta_engine_1_1_shadermanager.html) manage and stock all your [Shaders](https://www.sfml-dev.org/documentation/2.5.1-fr/classsf_1_1Shader.php).
They're accessible by their index.

Made by [EnderRayquaza](https://github.com/EnderRayquaza, "My Github") / Under MIT Licence. <br/>
Copyright DeltaEngine belong to EnderRayquaza. <br/>
You must quote me if your use my work. Thx. <br/>
