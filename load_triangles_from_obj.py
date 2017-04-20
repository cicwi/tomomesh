import tomomesh as tm
import numpy as np

def test_mesh():
    mesh = tm.Mesh('data/clock_lowres.obj')
    print(np.array(mesh.triangles()))
    print(np.array(mesh.bounding_box()))

test_mesh()
