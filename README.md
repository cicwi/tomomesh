# TomoMesh

Converts a mesh from a format readable by `assimp`, to a triangle array
compatible with the Astra mesh projector.

## Usage

```bash
# to build
git submodule update --init --remote
mkdir build
cd build
cmake ..
make -j8

# to run
python3 load_triangles_from_obj.py
```
