# Octree27
Octree27 is a variant of the octree volumetric mesh generation technique, in which the hexahedron is divided into 27 sub-hexahedrons.

    usage: 
      ./mesher -i <input.mdl> -o <output> <refinement_options> [<options>]
    
    refinement_options:
      -s <rl>  Refine surface elements to <rl> (refinement level).
      -a <rl>  Refine all elements to level <rl>.
      -r <file.reg>  Refine regions to rl, both specified in <file.reg>.
      -u <surface> <rl>  Refine mesh element inside <surface> to level <rl>.
    
    options:
      -t <table_name> Selects association table of refinement patterns and 
                      transition templates.
      

There are ten association tables between refinement patterns and transition templates implemented:

| <table_name> | Description                               |
|--------------|-------------------------------------------|
| `table_all`  | All template table                        |
| `ito2009_a`  | Table 1 in [[Ito et al 2009a]](#ito2009a) |
| `ito2009_b`  | Table 2 in [[Ito et al 2009a]](#ito2009a) |
| `ito2009_c`  | Table in [[Ito et al 2009b]](#ito2009b)   |
| `table_t7t5` | `ito2009_c` + templates T7 and T5         |
| `table_t7`   | `ito2009_c` + template T7                 |
| `table_t6b`  | `ito2009_c` + template T6B                |
| `table_t5`   | `ito2009_c` + template T5                 |
| `table_t4c`  | `ito2009_c` + template T4C                |
| `table_t4b`  | `ito2009_c` + template T4B                |


### References
<a id="ito2009a"></a>
* [Ito et al 2009a] Ito, Y., Shih, A. M., & Soni, B. K. (2009). Octree‐based reasonable‐quality hexahedral mesh generation using a new set of refinement templates. International Journal for Numerical Methods in Engineering, 77(13), 1809-1833.
<a id="ito2009b"></a>
* [Ito et al 2009b] Ito, Y., Shih, A. M., & Soni, B. K. (2009). Efficient hexahedral mesh generation for complex geometries using an improved set of refinement templates. In Proceedings of the 18th International Meshing Roundtable (pp. 103-115). Springer, Berlin, Heidelberg.
