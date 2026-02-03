# cub3D - 42 School (MiniLibX)

Raycasting 3D faux Wolfenstein3D. Parsing .cub, textures, map rectangulaire, mouvements souris/clavier. **Collab avec [lisalana](https://github.com/lisalana)**. 

![Screenshot 3D](screenshots/cub3d-raycast.gif) <!-- GIF rotation + walk -->

## Features
- Parsing .cub : map, RGB floor/ceiling, 4 textures (.xpm).
- Validation : map fermée, 1P (NO/SO/EA/WE), pas de chars invalides.
- Raycasting : DDA algo, distance mur, fisheye fix.
- Events : WASD move, souris rotation, ESC/menu.
- Bonus-ready : Collisions, minimap, mouse lock

## Installation
```bash
make
