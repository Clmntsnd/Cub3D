<p align="center"> 
   <img src="https://github.com/Clmntsnd/42-project-badges/blob/main/badges/cub3de.png" alt="Philosophers Logo">
</p>

# Cub3D

_This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way_




leak check

valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=./cub3d.sup ./cub3D ./assets/maps/good_map.cub  

BAD MAPS
                                       Display ERR    LEAKS (atExit)
bad_arg_asset_missing.cub              managed        managed
bad_arg_color_missing.cub              managed        managed

bad_arg_order_asset.cub                managed        managed
bad_arg_order_colors.cub               managed        managed
bad_arg_rgb_missing.cub                managed        managed
bad_arg_wrong_asset_orientation.cub    managed        managed
bad_assest_ext.cub                     managed        managed
bad_color_rgb.cub                      managed        managed
bad_ext.test                           managed        managed
bad_map_char.cub                       managed        managed
bad_map_dup_starting_point.cub         managed        managed
bad_map_not_starting_point.cub         managed        managed
bad_map_open.cub                       managed        managed   

<!-- TODO -->
bad_arg_dup.cub                        managed        to double check (SEE BELOW)
cub3D(84086,0x1126bedc0) malloc: *** error for object 0x7f9b3340e7d2: pointer being freed was not allocated
cub3D(84086,0x1126bedc0) malloc: *** set a breakpoint in malloc_error_break to debug


*Removing the free paths in free_exit solves this issue

<!-- TODO -->
bad_map_six_text_no_color.cub          **ISSUES**     **ISSUES** (map works but it should'nt)

<!-- TODO -->
GOOD MAPS
./cub3D assets/maps/good_map2.cub                     4 leaks
./cub3D assets/maps/good_map.cub      **ISSUES with tabs in texture path**