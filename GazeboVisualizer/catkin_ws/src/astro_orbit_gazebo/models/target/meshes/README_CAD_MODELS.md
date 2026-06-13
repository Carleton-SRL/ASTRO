# Target CAD Mesh Folder

Place high-detail spacecraft visual meshes here.

Recommended Gazebo Classic workflow:
- Visual mesh: `target_visual.dae` (COLLADA), exported from Blender, FreeCAD, Fusion 360, or SolidWorks through a converter.
- Collision mesh: `target_collision.stl` simplified, or primitive collision shapes in `model.sdf`.

To enable the CAD mesh, edit `../model.sdf` and replace the primitive visual geometry with:

```xml
<mesh>
  <uri>model://target/meshes/target_visual.dae</uri>
  <scale>1 1 1</scale>
</mesh>
```

Keep collision low fidelity. Do not use a complete CAD assembly as collision geometry.
