# cub3D - 42 School (MiniLibX)

Raycasting 3D faux Wolfenstein3D. Parsing .cub, textures, map rectangulaire, mouvements souris/clavier. **Collab avec [lisalana](https://github.com/lisalana)**. 

![GIF 3D du jeu](cub3d.gif)

## Features
- Parsing .cub : map, RGB floor/ceiling, 4 textures (.xpm).
- Validation : map fermée, 1P (NO/SO/EA/WE), pas de chars invalides.
- Raycasting : DDA algo, distance mur, fisheye fix.
- Events : WASD move, souris rotation, ESC/menu.
- Bonus-ready : Collisions, minimap, mouse lock

## Installation
```bash
make

./cub3D maps/map2.cub       # 🎮 Map principale (recommandée)
