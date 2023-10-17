<p align="center"> 
   <img src="https://github.com/Clmntsnd/42-project-badges/blob/main/badges/cub3de.png" alt="Philosophers Logo">
</p>

# Cub3D

_This project is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way_




leak check

valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=./cub3d.sup ./cub3D ./assets/maps/good_map.cub  





bad_arg_asset_missing.cub   managed
bad_arg_color_missing.cub   managed  
bad_arg_dup.cub             managed  
bad_arg_order_asset.cub     managed
bad_arg_order_colors.cub    managed  
bad_arg_rgb_missing.cub     managed         
bad_arg_wrong_asset_orientation.cub  managed
bad_assest_ext.cub      managed             
bad_color_rgb.cub       managed  
bad_ext.test            managed    
bad_map_char.cub        **Issue**      
bad_map_dup_starting_point.cub   managed                       
bad_map_not_starting_point.cub     **Issues**
bad_map_open.cub          Managed         


./cub3D assets/maps/good_map2.cub      |    doouble free when more than one char in the map
./cub3D assets/maps/good_map2.cub      |    doouble free when exiting


NORM:
srcs/arg_parsing.c: OK!
srcs/colors.c: OK!
srcs/init.c: OK!
srcs/key_binding.c: OK!
srcs/main.c: OK!
srcs/map_check.c: OK!
srcs/raycast.c: OK!
srcs/raycast_utils.c: OK!
srcs/utils.c: OK!

srcs/error_management.c: Error!
Error: WRONG_SCOPE_COMMENT  (line:  26, col:   5):      Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  27, col:   5):      Comment is invalid in this scope
Error: WRONG_SCOPE_COMMENT  (line:  28, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TABS_FUNC   (line:  31, col:   5):      extra tabs before function name
Error: SPACE_REPLACE_TAB    (line:  33, col:   8):      Found space when expecting tab
Error: WRONG_SCOPE_COMMENT  (line:  43, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  44, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  45, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  46, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  47, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  48, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  49, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  50, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  51, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  52, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  53, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  54, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  55, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  56, col:   1):      Extra tabs for indent level
Error: WRONG_SCOPE_COMMENT  (line:  57, col:   5):      Comment is invalid in this scope
Error: TOO_MANY_TAB         (line:  58, col:   1):      Extra tabs for indent level
Error: SPACE_BEFORE_FUNC    (line:  61, col:   4):      space before function name
Error: SPACE_AFTER_KW       (line:  64, col:   5):      Missing space after keyword
Error: SPC_BFR_PAR          (line:  64, col:   7):      Missing space before parenthesis (brace/bracket)
Error: WRONG_SCOPE_COMMENT  (line:  66, col:   5):      Comment is invalid in this scope
Error: SPACE_AFTER_KW       (line:  68, col:   5):      Missing space after keyword
Error: SPC_BFR_PAR          (line:  68, col:  11):      Missing space before parenthesis (brace/bracket)
srcs/map_parsing.c: Error!
Error: LINE_TOO_LONG        (line:  28, col:  83):      line too long
Error: LINE_TOO_LONG        (line:  29, col:  83):      line too long
Error: LINE_TOO_LONG        (line:  30, col:  83):      line too long
Error: LINE_TOO_LONG        (line:  35, col:  83):      line too long
Error: LINE_TOO_LONG        (line:  40, col:  82):      line too long
Error: TOO_MANY_LINES       (line:  49, col:   1):      Function has more than 25 lines
Error: LINE_TOO_LONG        (line:  66, col:  84):      line too long
Error: LINE_TOO_LONG        (line:  67, col:  82):      line too long
Error: LINE_TOO_LONG        (line:  68, col:  83):      line too long
Error: TOO_MANY_LINES       (line:  88, col:   1):      Function has more than 25 lines